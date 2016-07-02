//
// Copyright 2015-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include "lex_stream.h"

using namespace orange::parser;

Token* LexStream::peek() {
	if (mBuffer.size() == 0) {
		mBuffer.push_back(mLexer.readToken());
	}

	return mBuffer[0];
}

std::vector<Token*> LexStream::peek(int n) {
	std::vector<Token*> lookahead;

	if (n > mBuffer.size()) {
		unsigned long need = n - mBuffer.size();
		for (unsigned long i = 0; i < need; i++) {
			mBuffer.push_back(mLexer.readToken());
		}
	}

	for (int i = 0; i < n; i++) {
		lookahead.push_back(mBuffer[i]);
	}

	return lookahead;
}

Token* LexStream::get() {
	if (mBuffer.size() > 0) {
		auto tok = mBuffer[0];
		mBuffer.erase(mBuffer.begin());
		return tok;
	}

	return mLexer.readToken();
}

std::vector<Token*> LexStream::get(int n) {
	std::vector<Token*> next;

	int remaining = n;
	while (remaining > 0 && mBuffer.size() > 0) {
		next.push_back(mBuffer.front());
		mBuffer.erase(mBuffer.begin());
		remaining--;
	}

	for (int i = 0; i < remaining; i++) {
		next.push_back(mLexer.readToken());
	}

	return next;
}

LexStream::LexStream(std::istream& stream) : mLexer(stream) { }