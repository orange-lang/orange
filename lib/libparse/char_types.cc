//
// Copyright 2015-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include "char_types.h"

bool isnumber(char c) {
	return c == '0' || c == '1' || c == '2' || c == '3' || c == '4' ||
	       c == '5' || c == '6' || c == '7' || c == '8' || c == '9';
}

bool ishexnumber(char c) {
	return isnumber(c) ||
	       c == 'a' || c == 'b' || c == 'c' || c == 'd' || c == 'e' || c == 'f' ||
	       c == 'A' || c == 'B' || c == 'C' || c == 'D' || c == 'E' || c == 'F';
}

bool isoctnumber(char c) {
	return c == '0' || c == '1' || c == '2' || c == '3' || c == '4' ||
	       c == '5' || c == '6' || c == '7';
}
