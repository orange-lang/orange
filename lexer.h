#ifndef __LEXER_H__
#define __LEXER_H__

#include <vector>
#include <string>

typedef enum LexemeType {
	ID,												// [a-zA-Z][0-9a-zA-Z_]*

	// Keywords 
	KEYWORD_DEF,						
	KEYWORD_END,
	KEYWORD_CLASS,
	KEYWORD_USING,
	KEYWORD_PUBLIC,
	KEYWORD_PRIVATE,
	KEYWORD_SHARED,
	KEYWORD_INT,
	KEYWORD_FLOAT,
	KEYWORD_DOUBLE,
	KEYWORD_INT8,
	KEYWORD_UINT8,
	KEYWORD_INT16,
	KEYWORD_UINT16,
	KEYWORD_INT32,
	KEYWORD_UINT32,
	KEYWORD_INT64,
	KEYWORD_UINT64,

	// Operators 
	OPEN_PAREN,
	CLOSE_PAREN,
	OPEN_BRACE,
	CLOSE_BRACE,
	OPEN_BRACKET,
	CLOSE_BRACKET,

	PLUS,
	MINUS,
	TIMES,
	DIVIDE,
	MODULUS,
	ARROW, 										// ->
	DOT, 											// . 
	INCREMENT,								// ++
	DECREMENT,								// --
	ASSIGN,										// =
	EQUALS,										// ==		
	PLUS_ASSIGN, 							// += 
	MINUS_ASSIGN, 						// -=
	TIMES_ASSIGN,							// *=
	DIVIDE_ASSIGN,						// /=
	MODULUS_ASSIGN,						// %=
	SEMICOLON,								// ;
	COMMA,

	// COMPARISONS 
	LESS_THAN,
	LESS_OR_EQUAL,
	GREATER_THAN,
	GREATER_OR_EQUAL,

	// Types 
	TYPE_FLOAT,
	TYPE_DOUBLE,
	TYPE_INT8,
	TYPE_UINT8,
	TYPE_INT16,
	TYPE_UINT16,
	TYPE_INT32,
	TYPE_UINT32,
	TYPE_INT64,
	TYPE_UINT64
} LexemeType;

class Lexeme {
private:
	class Value {
	public:
		std::string string; 
		uint64_t uint64; 
		int64_t int64; 
		float floatVal;
		double doubleVal;
	};
public:
	LexemeType type; 
	Value value;
};

std::vector<Lexeme *> Lex(std::string source);
void PrintLexemes(std::vector<Lexeme*> lexemes);

#endif 