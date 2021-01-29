#include <stdint.h>
#include <string>
#include <iostream>

#include <v8.h>
#include <node.h>
#include "./BigIntegerLibrary.hh"
#include "nan.h"

// using namespace v8;
using v8::Function;
using v8::MaybeLocal;
using v8::Maybe;
using v8::Local;
using v8::Array;
using v8::Integer;
using v8::Number;
using v8::Value;
using v8::Local;
using v8::String;
using v8::Object;
using v8::FunctionTemplate;

using namespace node;
using namespace std;

using Nan::HandleScope;
using Nan::ThrowError;
using Nan::TryCatch;
using Nan::New;
using Nan::ReturnValue;
using Nan::Set;

#define ARGUMENTS_TYPE v8::internal::Arguments&

static const char base62_vals[] = "0123456789"
								  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
								  "abcdefghijklmnopqrstuvwxyz";

static const char base36_vals[] = "0123456789"
								  "ABCDEFGHIJKLMNOPQRSTUVWXYZ";


BigInteger arrayToBigInteger(MaybeLocal<Array> maybe_data, BigInteger::Index length, BigInteger::Sign sign) {
	unsigned int pieceSizeInBits = 8;
	unsigned int piecesPerBlock = sizeof(BigInteger::Blk);
	unsigned int numBlocks = (length + piecesPerBlock - 1) / piecesPerBlock;

	// Allocate our block array
	BigInteger::Blk *blocks = new BigInteger::Blk[numBlocks];
	BigInteger::Index blockNum, pieceNum, pieceNumHere;
	int piece;
	Local<Array> data;
	Local<Value> val;
	
	if (!maybe_data.ToLocal(&data)) {
		Nan::ThrowTypeError("failed to access byte array for conversion to big integer");
	}
	// Convert
	for (blockNum = 0, pieceNum = 0; blockNum < numBlocks; blockNum++) {
		BigInteger::Blk curBlock = 0;
		for (pieceNumHere = 0; pieceNumHere < piecesPerBlock && pieceNum < length;
			pieceNumHere++, pieceNum++) {
				val = Nan::Get(data, pieceNum).ToLocalChecked();
				piece = Nan::To<int32_t>(val).ToChecked();
				curBlock |= (BigInteger::Blk( piece ) << (pieceSizeInBits * pieceNumHere));
			}
		blocks[blockNum] = curBlock;
	}

	BigInteger x(blocks, numBlocks, sign);
	delete [] blocks;
	return x;
}

BigInteger GetBigIntegerFromInput(Nan::NAN_METHOD_ARGS_TYPE args) {
	Local<Array> argv_handle = Local<Array>::Cast(args[0]);
	int argc = argv_handle->Length();
	BigInteger::Sign sign = BigInteger::positive;
	return arrayToBigInteger( argv_handle, argc, sign );
};

string ToBase(Nan::NAN_METHOD_ARGS_TYPE args, int base, const char * list) {
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
	HandleScope();
	if(info.Length() < 2 || !info[0]->IsArray() || !info[1]->IsInt32()) {
		ThrowError("Argument 0 must be an array and Argument 1 must be an Integer");
	}
	string result = ToBase(info, 36, base36_vals);
	const char * carray = result.c_str();
	info.GetReturnValue().Set(New<String>(carray).ToLocalChecked());
};

NAN_METHOD(To62) {
	HandleScope();
	if(info.Length() < 2 || !info[0]->IsArray() || !info[1]->IsInt32()) {
		ThrowError("Argument 0 must be an array and Argument 1 must be an Integer");
	}
	string result = ToBase(info, 62, base62_vals);
	const char * carray = result.c_str();
	info.GetReturnValue().Set(New<String>(carray).ToLocalChecked());
};

void init(v8::Local<v8::Object> exports) {
	v8::Local<v8::Context> context = exports->CreationContext();
	Set(
		exports,
		New("to62").ToLocalChecked(),
		New<FunctionTemplate>(To62)
			->GetFunction(context)
			.ToLocalChecked()
	);
	Set(
		exports,
		New("to36").ToLocalChecked(),
		New<FunctionTemplate>(To36)
			->GetFunction(context)
			.ToLocalChecked()
	);
};

NODE_MODULE(baseJump, init)
