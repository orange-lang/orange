#include <iostream>
#include <cctype>
#include <sstream>
#include <map>
#include "lexer.h"

#define LEX_SINGLE(c, s, t) if(source[idx] == c) {\
 	Lexeme *lex = new Lexeme();\
 	lex->value.string = s; lex->type = t;\
 	ret.push_back(lex); idx++;}

static std::map<LexemeType, int> *PrecedenceTable = nullptr;

int Precedence(LexemeType type) {
	if (PrecedenceTable == nullptr) {
		// initialize table 
		PrecedenceTable = new std::map<LexemeType, int>();
		(*PrecedenceTable)[EQUALS] = 1; 
		(*PrecedenceTable)[PLUS_ASSIGN] = 1; 
		(*PrecedenceTable)[MINUS_ASSIGN] = 1;
		(*PrecedenceTable)[TIMES_ASSIGN] = 1;
		(*PrecedenceTable)[DIVIDE_ASSIGN] = 1;
		(*PrecedenceTable)[MODULUS_ASSIGN] = 1;
		(*PrecedenceTable)[PLUS] = 2;
		(*PrecedenceTable)[MINUS] = 2; 
		(*PrecedenceTable)[TIMES] = 3; 
		(*PrecedenceTable)[DIVIDE] = 4;  
	}

	auto it = PrecedenceTable->find(type);
	if (it == PrecedenceTable->end()) {
		return -1; 
	}

	return it->second;
}


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

// returns true for 0->F
bool ishex(char c) {
	return isdigit(c) || (tolower(c) >= 'a' && tolower(c) <= 'f');
}

std::vector<Lexeme *> Lex(std::string source) {
	std::vector<Lexeme *> ret;

	// Handle whitespace 

	int idx = 0; 

	LexLambda parseNumber = [&idx, source](std::string existing) -> Lexeme* {
		Lexeme *lex = new Lexeme();
		lex->value.string = "NUMBER";
		lex->type = TYPE_INT64;

		std::string num = existing;

		bool isHex = false;

		while (isdigit(source[idx])) {
			num += source[idx++]; 
		}

		if (num == "0" && source[idx] == 'x' && ishex(source[idx+1])) {
			num += source[idx++];

			while (ishex(source[idx])) {
				num += source[idx++];
			}

			isHex = true; 
			lex->type = TYPE_UINT64;
		} else if (source[idx] == '.' && isdigit(source[idx+1])) {
			num += source[idx]; 
			idx++; 
			lex->type = TYPE_DOUBLE; 

			while (isdigit(source[idx])) {
				num += source[idx]; 
				idx++;
			}	
		}

		switch (lex->type) {
		case TYPE_INT64:
			lex->value.int64 = std::stoll(num, nullptr, isHex ? 16 : 10);
			break;
		case TYPE_UINT64:
			lex->value.uint64 = std::stoull(num, nullptr, isHex ? 16 : 10);
			break;		
		case TYPE_DOUBLE:
			lex->value.doubleVal = std::stod(num, nullptr);		
			break;
		default: break;
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

			lex->value.int64 = std::stoll(num, nullptr, isHex ? 16 : 10);
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

			lex->value.uint64 = std::stoull(num, nullptr, isHex ? 16 : 10);
		} else if (source[idx] == 'f') {
			if (isHex == true) {
				std::cerr << "Error: incorrect suffix f for hex number" << std::endl;
			} else {
				lex->type = TYPE_FLOAT;
				idx++;

				lex->value.floatVal = std::stof(num, nullptr);
			}
		} else if (source[idx] == 'd') {
			if (isHex == true) {
				std::cerr << "Error: incorrect suffix d for hex number" << std::endl;
			} else {
				lex->type = TYPE_DOUBLE;
				idx++;

				lex->value.doubleVal = std::stod(num, nullptr);
			}
		}


		lex->value.string = num;

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
			lex->value.string = id; 
			lex->type = TypeForKeyword(id);	

			ret.push_back(lex);
		}

		LEX_SINGLE('.', ".", DOT);
		LEX_SINGLE(',', ",", COMMA);
		LEX_SINGLE('(', "(", OPEN_PAREN);
		LEX_SINGLE(')', ")", CLOSE_PAREN);
		LEX_SINGLE('{', "{", OPEN_BRACE);
		LEX_SINGLE('}', "}", CLOSE_BRACE);
		LEX_SINGLE('[', "[", OPEN_BRACKET);
		LEX_SINGLE(']', "]", CLOSE_BRACKET);

		if (source[idx] == '+') {
			Lexeme *lex = new Lexeme();
			lex->value.string = "+"; 
			lex->type = PLUS; 
			idx++;

			if (source[idx] == '+') {
				lex->value.string += source[idx];
				lex->type = INCREMENT;
				idx++;
			}
			else if (source[idx] == '=') {
				lex->value.string += source[idx];
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
			lex->value.string = "-"; 
			lex->type = MINUS; 
			idx++;

			if (source[idx] == '-') {
				lex->value.string += source[idx];
				lex->type = DECREMENT;
				idx++;
			}
			else if (source[idx] == '>') {
				lex->value.string += source[idx];
				lex->type = ARROW;
				idx++;
			}
			else if (source[idx] == '=') {
				lex->value.string += source[idx];
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
			lex->value.string = "*"; 
			lex->type = TIMES; 
			idx++;

			if (source[idx] == '=') {
				lex->value.string += source[idx];
				lex->type = TIMES_ASSIGN;
				idx++;
			}

			ret.push_back(lex);
		}

		if (source[idx] == '/') {
			Lexeme *lex = new Lexeme();
			lex->value.string = "/"; 
			lex->type = DIVIDE; 
			idx++;

			if (source[idx] == '=') {
				lex->value.string += source[idx];
				lex->type = DIVIDE_ASSIGN;
				idx++;
			}

			ret.push_back(lex);
		}

		if (source[idx] == '%') {
			Lexeme *lex = new Lexeme();
			lex->value.string = "%"; 
			lex->type = MODULUS; 
			idx++;

			if (source[idx] == '=') {
				lex->value.string += source[idx];
				lex->type = MODULUS_ASSIGN;
				idx++;
			}

			ret.push_back(lex);
		}

		if (source[idx] == '=') {
			Lexeme *lex = new Lexeme();
			lex->value.string = "="; 
			lex->type = ASSIGN; 
			idx++;

			if (source[idx] == '=') {
				lex->value.string += source[idx];
				lex->type = EQUALS;
				idx++;
			}

			ret.push_back(lex);
		}

		if (source[idx] == '<') {
			Lexeme *lex = new Lexeme();
			lex->value.string = "<"; 
			lex->type = LESS_THAN; 
			idx++;

			if (source[idx] == '=') {
				lex->value.string += source[idx];
				lex->type = LESS_OR_EQUAL;
				idx++;
			} else if (source[idx] == '-') {
				lex->value.string += source[idx];
				lex->type = ARROW_LEFT;
				idx++;
			}

			ret.push_back(lex);
		}

		if (source[idx] == '>') {
			Lexeme *lex = new Lexeme();
			lex->value.string = ">"; 
			lex->type = GREATER_THAN; 
			idx++;

			if (source[idx] == '=') {
				lex->value.string += source[idx];
				lex->type = GREATER_OR_EQUAL;
				idx++;
			}

			ret.push_back(lex);
		}

		if (isdigit(source[idx])) {
			Lexeme *lex = parseNumber("");
			ret.push_back(lex);
		}
	}

	return ret;
}

std::string Lexeme::string() const {
	std::stringstream ss; 
	switch (type) {
		case TYPE_FLOAT:
			ss << value.floatVal; 
			return ss.str();
			break; 
		case TYPE_DOUBLE:
			ss << value.doubleVal; 
			return ss.str();
			break;
		case TYPE_INT8:
		case TYPE_INT16:
		case TYPE_INT32:
		case TYPE_INT64:
			ss << value.int64;
			return ss.str();
			break; 
		case TYPE_UINT8:
		case TYPE_UINT16:
		case TYPE_UINT32:
		case TYPE_UINT64:
			ss << value.uint64;
			return ss.str();
			break; 
		default:
			return value.string;
	}
}

void PrintLexemes(std::vector<Lexeme*> lexemes) {
	for (Lexeme* l : lexemes) {
		switch (l->type) {
			case TYPE_FLOAT:
				std::cout << l->value.floatVal << " ";
				break;
			case TYPE_DOUBLE:
				std::cout << l->value.doubleVal << " ";
				break;
			case TYPE_INT8:
			case TYPE_INT16:
			case TYPE_INT32:
			case TYPE_INT64:
				std::cout << l->value.int64 << " ";
				break;
			case TYPE_UINT8:
			case TYPE_UINT16:
			case TYPE_UINT32:
			case TYPE_UINT64:
				std::cout << l->value.uint64 << " ";
				break;
			default: 
				std::cout << l->value.string << " ";
		}
	}
	std::cout << std::endl;
}