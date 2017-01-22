/*
** Copyright 2014-2017 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

namespace orange { namespace parse {
	enum Token {
		TOKEN_EOF, // End of file 

		// Values 
		INT_VAL, INT8_VAL, INT16_VAL, INT32_VAL, INT64_VAL,
		UINT_VAL, UINT8_VAL, UINT16_VAL, UINT32_VAL, UINT64_VAL,
		FLOAT_VAL, DOUBLE_VAL, STRING_VAL, CHAR_VAL, BOOL_VAL,

		// Type names 
		INT, INT8, INT16, INT32, INT64,
		UINT, UINT8, UINT16, UINT32, UINT64,
		FLOAT, DOUBLE, STRING, CHAR, BOOL, VOID,

		// Statement endings 
		NEWLINE, SEMICOLON,

		// Keywords 
		VAR, ENUM, CLASS, PUBLIC, PROTECTED, PRIVATE, IF, ELIF, ELSE, FOR, 
		WHILE, DO, BREAK, CONTINUE, DEF, EXTERN, INTERFACE, PACKAGE, IMPORT, 
		NEW, DELETE, GET, SET, VIRTUAL, FINAL, WHERE, DATA, EXTEND, CONST, TRY,
		CATCH, FINALLY, THROW, OF, AS, PROPERTY, THIS,

		// Operators 
		OPEN_PAREN, CLOSE_PAREN, OPEN_CURLY, CLOSE_CURLY, OPEN_BRACKET,
		CLOSE_BRACKET, DOT, COMMA, COLON, ARROW, 

		// Comparison operators 
		LOGICAL_OR, LOGICAL_AND, LOGICAL_NOT, QUESTION, 
		EQ, NEQ, LE, GE, LT, GT, 

		// Mathematical operators 
		PLUS, MINUS, DIVIDE, TIMES, MOD, BIT_OR, BIT_AND,
		BIT_XOR, BIT_NOT, SHIFT_LEFT, SHIFT_RIGHT, 

		ASSIGN, PLUS_ASSIGN, MINUS_ASSIGN, DIVIDE_ASSIGN, TIMES_ASSIGN, 
		MOD_ASSIGN, BIT_OR_ASSIGN, BIT_AND_ASSIGN, BIT_XOR_ASSIGN, 
		SHIFT_LEFT_ASSIGN, SHIFT_RIGHT_ASSIGN, 

		INCREMENT, DECREMENT,

		// Other 
		IDENTIFIER, 
	};
}}