#include <stdint.h>
#include <string>
#include <iostream>

#include <v8.h>
#include <node.h>
#include "./BigIntegerLibrary.hh"

using namespace v8;
using namespace node;
using namespace std;

#define EXCEPTION(message) ThrowException(Exception::TypeError(String::New(message)))

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

BigInteger GetBigIntegerFromInput(const Arguments& args) {
	Local<Array> argv_handle = Local<Array>::Cast(args[0]);
	int argc = argv_handle->Length();
	BigInteger::Sign sign = BigInteger::positive;
	return arrayToBigInteger( argv_handle, argc, sign );
};

string ToBase(const Arguments& args, int base, const char * list) {
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

Handle<Value> To36(const Arguments& args) {
	HandleScope scope;
	if(args.Length() < 2 || !args[0]->IsArray() || !args[1]->NumberValue()) {
		return ThrowException(Exception::Error(String::New("Argument 0 must be an array and Argument 1 must be an Integer")));
	}
	string result = ToBase(args, 36, base36_vals);
	const char * carray = result.c_str();
	return scope.Close(String::New(carray));
};

Handle<Value> To62(const Arguments& args) {
	HandleScope scope;
	if(args.Length() < 2 || !args[0]->IsArray() || !args[1]->NumberValue()) {
		return ThrowException(Exception::Error(String::New("Argument 0 must be an array and Argument 1 must be an Integer")));
	}
	string result = ToBase(args, 62, base62_vals);
	const char * carray = result.c_str();
	return scope.Close(String::New(carray));
};

void init(Handle<Object> exports) {
  exports->Set(String::NewSymbol("to62"),
	  FunctionTemplate::New(To62)->GetFunction());
  exports->Set(String::NewSymbol("to36"),
	  FunctionTemplate::New(To36)->GetFunction());
};

NODE_MODULE(baseJump, init)