//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#pragma once

#include <istream>

template <typename T = char>
T peekChar(std::istream& s);

template <typename T = char>
T getChar(std::istream& s);

template <>
char peekChar(std::istream& s) {
	return std::istream::traits_type::to_char_type(s.peek());
}

template <>
char getChar(std::istream& s) {
	return std::istream::traits_type::to_char_type(s.get());
}

template <>
std::string peekChar(std::istream& s) {
	return std::string(1, peekChar<char>(s));
}

template <>
std::string getChar(std::istream& s) {
	return std::string(1, getChar<char>(s));
}

template <typename T = char>
std::string toString(T c);

template <>
std::string toString(char c) { return std::string(1, c); }

bool streamEOF(std::istream& stream) {
	return stream.eof() || stream.peek() == std::istream::traits_type::eof();
}