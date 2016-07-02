//
// Copyright 2015-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <stdexcept>
#include <sstream>
#include <map>
#include <vector>

#include "stream_helpers.h"
#include "lex.h"
#include "char_types.h"

using namespace orange::parser;

typedef std::map<std::string, TokenType> TokenMapTy;
static TokenMapTy TokenMap = {
	{"\n", NEWLINE      }, {";" , SEMICOLON       }, {"("  , OPEN_PAREN       }, {")"  , CLOSE_PAREN       },
	{"+" , PLUS         }, {"-" , MINUS           }, {"/"  , DIVIDE           }, {"*"  , TIMES             },
	{"%" , REMAINDER    }, {"|" , BIT_OR          }, {"&"  , BIT_AND          }, {"^"  , BIT_XOR           },
	{"?" , QUESTION     }, {"<<", SHIFT_LEFT      }, {">>" , SHIFT_RIGHT      }, {"="  , ASSIGN            },
	{"==", EQUALS       }, {"+=", PLUS_ASSIGN     }, {"-=" , MINUS_ASSIGN     }, {"*=" , TIMES_ASSIGN      },
	{"/=", DIVIDE_ASSIGN}, {"%=", REMAINDER_ASSIGN}, {"<<=", SHIFT_LEFT_ASSIGN}, {">>=", SHIFT_RIGHT_ASSIGN},
	{"|=", BIT_OR_ASSIGN}, {"&=", BIT_AND_ASSIGN  }, {"^=" , BIT_XOR_ASSIGN   }, {"<"  , LESS_THAN         },
	{">" , GREATER_THAN }, {"<=", LEQ             }, {">=" , GEQ              }, {"!=" , NEQ               },
	{"&&", AND          }, {"||", OR              }, {"++" , INCREMENT        }, {"--" , DECREMENT         },
	{"{" , OPEN_CURLY   }, {"}" , CLOSE_CURLY     }, {","  , COMMA            }, {"."  , DOT               },
	{"[" , OPEN_BRACKET }, {"]" , CLOSE_BRACKET   }, {"...", EXLUSIVE_RANGE   }, {".." , INCLUSIVE_RANGE   },
	{":" , COLON        }, {"->", ARROW           }, {"~"  , TILDE            }, {"!"  , NOT               }
};

/// Gets a comment
static Token* getComment(std::istream& stream) {
	auto pos = stream.tellg();

	if (peekChar(stream) != '/') return nullptr;

	std::stringstream buf;
	buf << getChar(stream);

	if (peekChar(stream) == '/') {
		// One-line comment
		buf << getChar(stream);

		while (!streamEOF(stream) && peekChar(stream) != '\n') {
			buf << getChar(stream);
		}

		if (peekChar(stream) == '\n') getChar(stream);
	} else if (peekChar(stream) == '*') {
		// Block comment
		buf << getChar(stream);

		int count = 1;

		char last_char = 0;
		while (!streamEOF(stream) && count > 0) {
			char this_char = getChar(stream);

			if (last_char == '*' && this_char == '/') count--;
			if (last_char == '/' && this_char == '*') count++;

			last_char = this_char;
			buf << last_char;
		}

		if (count > 0) {
			throw std::runtime_error("Unterminated block comment");
		}
	} else {
		stream.clear();
		stream.seekg(pos, stream.beg);
		return nullptr;
	}

	return new Token(COMMENT, buf.str());
}

static TokenMapTy IntSuffixMap = {
	{"" , VAL_INT },
	{"i", VAL_INT }, {"i8", VAL_INT8 }, {"i16", VAL_INT16 }, {"i32", VAL_INT32 }, {"i64", VAL_INT64 },
	{"u", VAL_UINT}, {"u8", VAL_UINT8}, {"u16", VAL_UINT16}, {"u32", VAL_UINT32}, {"u64", VAL_UINT64},
};

static Token* getIntSuffix(std::string buf, std::istream& stream) {
	char next_char = peekChar(stream);

	std::string buffer = "";

	// Continue grabbing alphanumeric characters and store them in a buffer
	while (!streamEOF(stream) && isalnum(next_char)) {
		buffer += getChar(stream);
		next_char = peekChar(stream);
	}

	auto suffix = IntSuffixMap.find(buffer);
	if (suffix == IntSuffixMap.end()) {
		throw std::runtime_error("Unknown integer suffix " + buffer);
	}

	return new Token(suffix->second, buf);
}

/// This function will only be called when buf has 0b
static Token* getBinary(std::string buf, std::istream& stream) {
	char next_char = peekChar(stream);

	while (next_char == '0' || next_char == '1') {
		buf += getChar(stream);
		next_char = peekChar(stream);
	}

	if (isnumber(next_char) && next_char > '1') {
		throw std::runtime_error("Only 0 and 1 are valid digits in a binary constant");
	}

	return getIntSuffix(buf, stream);
}

/// This function will only be called when buf has 0x
static Token* getHexadecimal(std::string buf, std::istream& stream) {
	char next_char = peekChar(stream);

	while (ishexnumber(next_char)) {
		buf += getChar(stream);
		next_char = peekChar(stream);
	}

	return getIntSuffix(buf, stream);
}

/// This function will only be called when buf has 0x
static Token* getOctal(std::string buf, std::istream& stream) {
	char next_char = peekChar(stream);

	while (isoctnumber(next_char)) {
		buf += getChar(stream);
		next_char = peekChar(stream);
	}

	if (isnumber(next_char)) {
		throw std::runtime_error("Only 0-7 are valid digits in a binary constant");
	}

	return getIntSuffix(buf, stream);
}

/// This function will only be called when buf already has numbers up to a decimal point
static Token* getFloat(std::string buf, std::istream& stream) {
	char next_char = peekChar(stream);

	while (isnumber(next_char)) {
		buf += getChar(stream);
		next_char = peekChar(stream);
	}

	std::string suffix = "";
	while (isalnum(next_char)) {
		suffix += getChar(stream);
		next_char = peekChar(stream);
	}

	if (suffix == "f") {
		return new Token(VAL_FLOAT, buf);
	} else if (suffix == "d") {
		return new Token(VAL_DOUBLE, buf);
	} else if (suffix != "") {
		throw std::runtime_error("Invalid floating-point suffix " + suffix);
	}

	return new Token(VAL_DOUBLE, buf);
}

/// Gets a constant number
static Token* getNumber(std::istream& stream) {
	char next_char = peekChar(stream);
	if (!isnumber(next_char)) return nullptr;

	std::string buf = "";

	if (next_char == '0') {
		buf += getChar(stream);
		next_char = peekChar(stream);

		if (next_char == 'b') {
			buf += getChar(stream);
			return getBinary(buf, stream);
		} else if (next_char == 'x') {
			buf += getChar(stream);
			return getHexadecimal(buf, stream);
		} else if (next_char == 'o') {
			buf += getChar(stream);
			return getOctal(buf, stream);
		} else if (next_char == 'd') {
			getChar(stream);
			return new Token(VAL_DOUBLE, buf);
		} else if (next_char == 'f') {
			getChar(stream);
			return new Token(VAL_FLOAT, buf);
		} else if (next_char == '.') {
			buf += getChar(stream);
			return getFloat(buf, stream);
		} else {
			return getIntSuffix(buf, stream);
		}
	}

	// first digit was 1-9

	while (!streamEOF(stream) && isnumber(next_char)) {
		buf += getChar(stream);
		next_char = peekChar(stream);
	}

	if (next_char == '.') {
		buf += getChar(stream);
		return getFloat(buf, stream);
	}

	return getIntSuffix(buf, stream);
}

/// Gets a constant string
static Token* getString(std::istream& stream) {
	if (peekChar(stream) != '"') return nullptr;
	getChar(stream);

	std::string buf = "";

	while (!streamEOF(stream)) {
		auto this_char = getChar(stream);

		if (this_char == '"') break;
		else if (this_char == '\n') {
			throw std::runtime_error("Unterminated string");
		} else if (this_char == '\\') { // Escape character
			buf += toString(this_char) + getChar<std::string>(stream);
			continue;
		}

		buf += toString(this_char);
	}

	return new Token(VAL_STRING, buf);
}

static Token* getCharacter(std::istream& stream) {
	if (peekChar(stream) != '\'') return nullptr;
	getChar(stream);

	std::string buf = "";

	bool readChar = false;

	char nextChar = getChar(stream);
	if (nextChar == '\'') {
		return new Token(VAL_CHAR, buf);
	} else if (nextChar == '\n') {
		throw std::runtime_error("Unterminated character constant");
	} else if (nextChar == '\\') {
		buf += toString(nextChar) + getChar<std::string>(stream);
	}

	if (getChar(stream) != '\'') {
		throw std::runtime_error("Invalid character constant with more than one character");
	}

	return new Token(VAL_CHAR, buf);
}

/// Gets an operator (including newline)
static Token* getOperator(std::istream& stream) {
	std::string buf;

	// We want to get our operator but still check for longer operators that match.
	// Our solution is to keep track of the old matches, and see if we have a new
	// set of matches after peeking at the next character. If we do, we use that
	// as the base and continue on. If not, we use the old set and look for an exact
	// string match.
	std::vector<std::pair<std::string, TokenType>> matches;

	do {
		auto old_buf = buf;

		buf += peekChar(stream);
		std::vector<std::pair<std::string, TokenType>> new_matches;

		for (auto& kvp : TokenMap) {
			if (kvp.first.compare(0, buf.size(), buf) == 0) {
				new_matches.push_back(std::make_pair(kvp.first, kvp.second));
			}
		}

		// If we have a new set of matches, use that as the base.
		// otherwise, our previous set of matches is a winner.
		if (new_matches.size() > 0) {
			matches = new_matches;
			getChar(stream);
		} else {
			buf = old_buf;
			break;
		}
	} while (!streamEOF(stream) && matches.size() > 0);

	// Finally, go over our list of matches. If we find a token that matches
	// exactly, we can quit.
	for (auto& match : matches) {
		if (match.first == buf) {
			return new Token(match.second, buf);
		}
	}

	return nullptr;
}

static TokenMapTy IdentifierMap = {
	{"int"      , INT      }, {"uint"     , UINT     }, {"int8"     , INT8     }, {"int16"    , INT16    },
	{"int32"    , INT32    }, {"int64"    , INT64    }, {"uint8"    , UINT8    }, {"uint16"   , UINT16   },
	{"uint32"   , UINT32   }, {"uint64"   , UINT64   }, {"float"    , FLOAT    }, {"double"   , DOUBLE   },
	{"var"      , VAR      }, {"void"     , VOID     }, {"_"        , TEMP     }, {"operator" , OPERATOR },
	{"enum"     , ENUM     }, {"class"    , CLASS    }, {"partial"  , PARTIAL  }, {"in"       , IN       },
	{"if"       , IF       }, {"elif"     , ELIF     }, {"else"     , ELSE     }, {"for"      , FOR      },
	{"foreach"  , FOREACH  }, {"while"    , WHILE    }, {"forever"  , FOREVER  }, {"do"       , DO       },
	{"switch"   , SWITCH   }, {"break"    , BREAK    }, {"continue" , CONTINUE }, {"yield"    , YIELD    },
	{"def"      , DEF      }, {"extern"   , EXTERN   }, {"aggregate", AGGREGATE}, {"interface", INTERFACE},
	{"namespace", NAMESPACE}, {"import"   , IMPORT   }, {"new"      , NEW      }, {"delete"   , DELETE   },
	{"private"  , PRIVATE  }, {"protected", PROTECTED}, {"public"   , PUBLIC   }, {"get"      , GET      },
	{"set"      , SET      }, {"virtual"  , VIRTUAL  }, {"final"    , FINAL    }, {"partial"  , PARTIAL  },
	{"where"    , WHERE    }, {"data"     , DATA     }, {"extend"   , EXTEND   }, {"const"    , CONST    },
	{"try"      , TRY      }, {"catch"    , CATCH    }, {"finally"  , FINALLY  }, {"throw"    , THROW    },
	{"of"       , OF       }, {"char"     , CHAR     }, {"as"       , AS       }
};

/// Gets an identifier (includes _ and keywords)
static Token* getIdentifier(std::istream& stream) {
	char next_char = peekChar(stream);
	if (next_char != '_' && !isalpha(next_char)) return nullptr;

	std::string buf = "";
	buf += getChar(stream);

	if (next_char == '_' && (peekChar(stream) == '_' || isnumber(peekChar(stream)))) {
		throw std::runtime_error("Identifiers starting with _ must be followed by a letter.");
	}

	next_char = peekChar(stream);

	while (!streamEOF(stream) && (isalnum(next_char) || next_char == '_')) {
		buf += getChar(stream);
		next_char = peekChar(stream);
	}

	auto it = IdentifierMap.find(buf);
	if (it != IdentifierMap.end()) {
		return new Token(it->second, buf);
	} else {
		return new Token(IDENTIFIER, buf);
	}
}

Lexer::Lexer(std::istream& stream) : mStream(stream) { }

bool Lexer::eof() const {
	return streamEOF(mStream);
}

Token* Lexer::readToken() {
	if (eof()) return nullptr;

	// Ignore whitespace (minus newlines)
	char next_char = peekChar(mStream);
	while (isspace(next_char) && next_char != '\n') {
		getChar(mStream);
		next_char = peekChar(mStream);
	}

	Token* tok = nullptr;

	if ((tok = getComment(mStream))) return tok;
	if ((tok = getNumber(mStream))) return tok;
	if ((tok = getString(mStream))) return tok;
	if ((tok = getCharacter(mStream))) return tok;
	if ((tok = getOperator(mStream))) return tok;
	if ((tok = getIdentifier(mStream))) return tok;

	std::stringstream ss;
	ss << "Invalid token " << peekChar(mStream);
	throw std::runtime_error(ss.str());
}
