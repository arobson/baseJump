#include <stdint.h>
#include <string>
#include <iostream>

#include <v8.h>
#include <node.h>
#include "./BigIntegerLibrary.hh"
#include "nan.h"

using namespace v8;
using namespace node;
using namespace std;

#define ARGUMENTS_TYPE v8::internal::Arguments&

static const char base62_vals[] = "0123456789"
								  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
								  "abcdefghijklmnopqrstuvwxyz";

static const char base36_vals[] = "0123456789"
								  "ABCDEFGHIJKLMNOPQRSTUVWXYZ";


BigInteger arrayToBigInteger(Local<Array> data, BigInteger::Index length, BigInteger::Sign sign) {
	unsigned int pieceSizeInBits = 8;
	unsigned int piecesPerBlock = 4;
	unsigned int numBlocks = (length + piecesPerBlock - 1) / piecesPerBlock;

	// Allocate our block array
	BigInteger::Blk *blocks = new BigInteger::Blk[numBlocks];
	BigInteger::Index blockNum, pieceNum, pieceNumHere;
	int piece;

	// Convert
	for (blockNum = 0, pieceNum = 0; blockNum < numBlocks; blockNum++) {
		BigInteger::Blk curBlock = 0;
		for (pieceNumHere = 0; pieceNumHere < piecesPerBlock && pieceNum < length;
			pieceNumHere++, pieceNum++) {
				piece = BigInteger::Blk( data->Get(pieceNum)->Int32Value() );
				curBlock |= (BigInteger::Blk( piece ) << (pieceSizeInBits * pieceNumHere));
			}
		blocks[blockNum] = curBlock;
	}
	// Create the BigInteger.
	BigInteger x(blocks, numBlocks, sign);
	delete [] blocks;
	return x;
}

BigInteger GetBigIntegerFromInput(_NAN_METHOD_ARGS_TYPE args) {
	Local<Array> argv_handle = Local<Array>::Cast(args[0]);
	int argc = argv_handle->Length();
	BigInteger::Sign sign = BigInteger::positive;
	return arrayToBigInteger( argv_handle, argc, sign );
};

string ToBase(_NAN_METHOD_ARGS_TYPE args, int base, const char * list) {
	BigInteger bigInt = GetBigIntegerFromInput( args );
	int total = Local<Integer>::Cast(args[1])->Value();
	int i = total - 1;
	BigInteger v;
	string str = string(total + 1, '0');
	do {
		v = bigInt % base;
		str[i] = list[v.toInt()];
		bigInt = bigInt / base;
		i--;
	} while(bigInt > 0 && i >= 0);

	str[total] = '\0';
	return str;
};

NAN_METHOD(To36) {
	NanScope();
	if(args.Length() < 2 || !args[0]->IsArray() || !args[1]->NumberValue()) {
		NanThrowError("Argument 0 must be an array and Argument 1 must be an Integer");
	}
	string result = ToBase(args, 36, base36_vals);
	const char * carray = result.c_str();
	NanReturnValue(NanNew<String>(carray));
};

NAN_METHOD(To62) {
	NanScope();
	if(args.Length() < 2 || !args[0]->IsArray() || !args[1]->NumberValue()) {
		NanThrowError("Argument 0 must be an array and Argument 1 must be an Integer");
	}
	string result = ToBase(args, 62, base62_vals);
	const char * carray = result.c_str();
	NanReturnValue(NanNew<String>(carray));
};

void init(Handle<Object> exports) {
	exports->Set(NanNew<String>("to62"),
		NanNew<FunctionTemplate>(To62)->GetFunction());
	exports->Set(NanNew<String>("to36"),
		NanNew<FunctionTemplate>(To36)->GetFunction());
};

NODE_MODULE(baseJump, init)
