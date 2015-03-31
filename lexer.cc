#include <iostream>
#include <cctype>
#include "lexer.h"

LexemeType TypeForKeyword(std::string id) {
	if (id == "def") 
		return KEYWORD_DEF;
	else if (id == "end")
		return KEYWORD_END;
	else if (id == "class")
		return KEYWORD_CLASS;
	else if (id == "using")
		return KEYWORD_USING;
	else if (id == "public")
		return KEYWORD_PUBLIC;
	else if (id == "private")
		return KEYWORD_PRIVATE;
	else if (id == "shared")
		return KEYWORD_SHARED;
	else if (id == "int")
		return KEYWORD_INT;
	else if (id == "float")
		return KEYWORD_FLOAT;
	else if (id == "int8")
		return KEYWORD_INT8;
	else if (id == "uint8")
		return KEYWORD_UINT8;
	else if (id == "int16")
		return KEYWORD_INT16;
	else if (id == "uint16")
		return KEYWORD_UINT16;
	else if (id == "int32")
		return KEYWORD_INT32;
	else if (id == "uint32")
		return KEYWORD_UINT32;
	else if (id == "int64")
		return KEYWORD_INT64;
	else if (id == "uint64")
		return KEYWORD_UINT64;
	else 
		return ID; 
}

typedef std::function<Lexeme*(std::string)> LexLambda;

std::vector<Lexeme *> Lex(std::string source) {
	std::vector<Lexeme *> ret;

	// Handle whitespace 

	int idx = 0; 

	LexLambda parseNumber = [&idx, source](std::string existing) -> Lexeme* {
		Lexeme *lex = new Lexeme();
		lex->value = existing;
		lex->type = TYPE_INT64;

		while (isdigit(source[idx])) {
			lex->value += source[idx]; 
			idx++;
		}

		if (source[idx] == '.' && isdigit(source[idx+1])) {
			lex->value += source[idx]; 
			idx++; 
			lex->type = TYPE_DOUBLE; 

			while (isdigit(source[idx])) {
				lex->value += source[idx]; 
				idx++;
			}	
		}

		// Now do suffixes 
		if (source[idx] == 'i') {
			lex->type = TYPE_INT64;
			idx++;

			std::string precision = "";
			while (isdigit(source[idx])) {
				precision += source[idx++];
			}

			if (precision == "8") 
				lex->type = TYPE_INT8; 
			else if (precision == "16") 
				lex->type = TYPE_INT16;
			else if (precision == "32")
				lex->type = TYPE_INT32;
			else if (precision == "64") 
				lex->type = TYPE_INT64;
			else {
				std::cerr << "Error: unknown precision " << precision << std::endl;
			}
		} else if (source[idx] == 'u') {
			lex->type = TYPE_UINT64;
			idx++;

			std::string precision = "";
			while (isdigit(source[idx])) {
				precision += source[idx++];
			}

			if (precision == "8") 
				lex->type = TYPE_UINT8; 
			else if (precision == "16") 
				lex->type = TYPE_UINT16;
			else if (precision == "32")
				lex->type = TYPE_UINT32;
			else if (precision == "64") 
				lex->type = TYPE_UINT64;
			else {
				std::cerr << "Error: unknown precision " << precision << std::endl;
			}
		} else if (source[idx] == 'f') {
			lex->type = TYPE_FLOAT;
			idx++;
		} else if (source[idx] == 'd') {
			lex->type = TYPE_DOUBLE;
			idx++;
		}

		return lex;
	};

	while (idx < source.length()) {
		while (isspace(source[idx]) == true) {
			idx++;
		}

		// Handle comments 
		if (source[idx] == '#') {
			while (source[idx] != '\n' && source[idx] != '\r') {
				idx++;
			}
		}

		// Handle other.
		if (isalpha(source[idx])) {
			std::string id = "";
			id += source[idx++];

			while (isalnum(source[idx]) || source[idx] == '_') {
				id += source[idx++];
			}
			
			Lexeme *lex = new Lexeme();
			lex->value = id; 
			lex->type = TypeForKeyword(id);	

			ret.push_back(lex);
		}

		if (source[idx] == '.') {
			Lexeme *lex = new Lexeme();
			lex->value = ".";
			lex->type = DOT;
			ret.push_back(lex);
			idx++;
		}

		if (source[idx] == ',') {
			Lexeme *lex = new Lexeme();
			lex->value = ",";
			lex->type = COMMA;
			ret.push_back(lex);
			idx++;
		}

		if (source[idx] == '(') {
			Lexeme *lex = new Lexeme();
			lex->value = "(";
			lex->type = OPEN_PAREN;
			ret.push_back(lex);
			idx++;
		}

		if (source[idx] == ')') {
			Lexeme *lex = new Lexeme();
			lex->value = ")";
			lex->type = CLOSE_PAREN;
			ret.push_back(lex);
			idx++;
		}

		if (source[idx] == '{') {
			Lexeme *lex = new Lexeme();
			lex->value = "{";
			lex->type = OPEN_BRACE;
			ret.push_back(lex);
			idx++;
		}

		if (source[idx] == '}') {
			Lexeme *lex = new Lexeme();
			lex->value = "}";
			lex->type = CLOSE_BRACE;
			ret.push_back(lex);
			idx++;
		}

		if (source[idx] == '[') {
			Lexeme *lex = new Lexeme();
			lex->value = "[";
			lex->type = OPEN_BRACKET;
			ret.push_back(lex);
			idx++;
		}

		if (source[idx] == ']') {
			Lexeme *lex = new Lexeme();
			lex->value = "]";
			lex->type = CLOSE_BRACKET;
			ret.push_back(lex);
			idx++;
		}

		if (source[idx] == '+') {
			Lexeme *lex = new Lexeme();
			lex->value = "+"; 
			lex->type = PLUS; 
			idx++;

			if (source[idx] == '+') {
				lex->value += source[idx];
				lex->type = INCREMENT;
				idx++;
			}
			else if (source[idx] == '=') {
				lex->value += source[idx];
				lex->type = PLUS_ASSIGN;
				idx++;
			} else if (isdigit(source[idx])) {
				// do digit 
				delete lex; 
				lex = parseNumber("");
			}


			ret.push_back(lex);
		}

		if (source[idx] == '-') {
			Lexeme *lex = new Lexeme();
			lex->value = "-"; 
			lex->type = MINUS; 
			idx++;

			if (source[idx] == '-') {
				lex->value += source[idx];
				lex->type = DECREMENT;
				idx++;
			}
			else if (source[idx] == '>') {
				lex->value += source[idx];
				lex->type = ARROW;
				idx++;
			}
			else if (source[idx] == '=') {
				lex->value += source[idx];
				lex->type = MINUS_ASSIGN;
				idx++;
			} 
			else if (isdigit(source[idx])) {
				// do digit 
				delete lex; 
				lex = parseNumber("-");
			}

			ret.push_back(lex);
		}

		if (source[idx] == '*') {
			Lexeme *lex = new Lexeme();
			lex->value = "*"; 
			lex->type = TIMES; 
			idx++;

			if (source[idx] == '=') {
				lex->value += source[idx];
				lex->type = TIMES_ASSIGN;
				idx++;
			}

			ret.push_back(lex);
		}

		if (source[idx] == '/') {
			Lexeme *lex = new Lexeme();
			lex->value = "/"; 
			lex->type = DIVIDE; 
			idx++;

			if (source[idx] == '=') {
				lex->value += source[idx];
				lex->type = DIVIDE_ASSIGN;
				idx++;
			}

			ret.push_back(lex);
		}

		if (source[idx] == '%') {
			Lexeme *lex = new Lexeme();
			lex->value = "%"; 
			lex->type = MODULUS; 
			idx++;

			if (source[idx] == '=') {
				lex->value += source[idx];
				lex->type = MODULUS_ASSIGN;
				idx++;
			}

			ret.push_back(lex);
		}

		if (source[idx] == '=') {
			Lexeme *lex = new Lexeme();
			lex->value = "="; 
			lex->type = ASSIGN; 
			idx++;

			if (source[idx] == '=') {
				lex->value += source[idx];
				lex->type = EQUALS;
				idx++;
			}

			ret.push_back(lex);
		}

		if (source[idx] == '<') {
			Lexeme *lex = new Lexeme();
			lex->value = "<"; 
			lex->type = LESS_THAN; 
			idx++;

			if (source[idx] == '=') {
				lex->value += source[idx];
				lex->type = LESS_OR_EQUAL;
				idx++;
			}

			ret.push_back(lex);
		}

		if (source[idx] == '>') {
			Lexeme *lex = new Lexeme();
			lex->value = ">"; 
			lex->type = GREATER_THAN; 
			idx++;

			if (source[idx] == '=') {
				lex->value += source[idx];
				lex->type = GREATER_OR_EQUAL;
				idx++;
			}

			ret.push_back(lex);
		}

		// now do numbers
		// (-|+)?[0-9]*(\.[0-9]?)suffix
		if (isdigit(source[idx])) {
			Lexeme *lex = parseNumber("");
			ret.push_back(lex);
		}

	}


	return ret;
}

void PrintLexemes(std::vector<Lexeme*> lexemes) {
	for (Lexeme* l : lexemes) {
		std::cout << l->value << " ";
	}
	std::cout << std::endl;
}