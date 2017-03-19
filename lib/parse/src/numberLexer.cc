//
// Created by Robert Fratto on 3/18/17.
//


#include <string>
#include <sstream>
#include <cctype>

#include "numberLexer.h"
#include "lexeme.h"

using namespace orange::parse;

enum Prefix {
    NO_PREFIX,
    HEXADECIMAL_PREFIX,
    OCTAL_PREFIX,
    BINARY_PREFIX,
};


bool isBaseDigit(char c, int base);
int prefixToBase(Prefix prefix);
bool validSuffixStarter(char suffix);
bool validPrefix(char prefix);
bool signedValue(Token ty);
Prefix getPrefixFromChar(char c);
Prefix lexPrefix(std::istream& input);
bool validNumberStringForBase(std::string num, int base);
Token lexNumberSuffix(std::istream& input);

Lexeme orange::parse::lexNumber(std::istream& input) {
    std::string numberString;
    Token numberType = Token::INT_VAL;
    int numberBase = 10;

    Prefix p = lexPrefix(input);
    if (p != Prefix::NO_PREFIX) {
        numberBase = prefixToBase(p);
        numberType = Token::UINT_VAL;
    }

    // instead of getting only the valid number, let's just get
    // all alnum digits and then verify

    while (std::isxdigit(input.peek())) {
        // If we came across an f in non-base 16, break out, since that's a suffix
        if (input.peek() == 'f' && numberBase != 16) break;

        char val = (char)input.get();
        numberString += val;

        // Consume all separators
        while (input.peek() == '_') input.get();

        // If we found a . and we're not already a double
        if (input.peek() == '.' && numberType != Token::DOUBLE_VAL) {
            numberString += input.get();
            numberType = Token::DOUBLE_VAL;
        }
    }

    bool shouldParseSuffix = true;

    // If last character is ., we want to convert it BACK to a regular number and ignore suffixes
    // This allows for 5.method()
    if (numberString[numberString.size()-1] == '.') {
        input.putback('.');
        numberString = numberString.substr(0, numberString.size() - 1);
        numberType = (numberBase == 10) ? Token::INT_VAL : Token::UINT_VAL;
        shouldParseSuffix = false;
    }

    if (!validNumberStringForBase(numberString, numberBase)) {
        std::stringstream errMsg;
        errMsg << "Invalid number " << numberString << " for base " << numberBase;
        throw std::runtime_error(errMsg.str());
    }

    if (shouldParseSuffix) {
        Token typeFromSuffix = lexNumberSuffix(input);
        if (typeFromSuffix != Token::TOKEN_EOF) {
            numberType = typeFromSuffix;
        }

        if (numberBase != 10 && (numberType == Token::FLOAT_VAL || numberType == Token::DOUBLE_VAL)) {
            std::stringstream errMsg;
            errMsg << "Number of non-decimal base can not be floating-point";
            throw std::runtime_error(errMsg.str());
        }

        if (numberBase != 10 && signedValue(numberType)) {
            std::stringstream errMsg;
            errMsg << "Number of non-decimal base can not be signed";
            throw std::runtime_error(errMsg.str());
        }
    }

    if (numberType != Token::FLOAT_VAL && numberType != Token::DOUBLE_VAL) {
        if (numberString.find(".") != std::string::npos) {
            std::stringstream errMsg;
            errMsg << "Floating-point value can not have integral suffix";
            throw std::runtime_error(errMsg.str());
        }

        // If we're dealing with a non-decimal number, we need to convert it
        if (numberBase != 10) {
            long realNumber;
            try {
                realNumber = std::stol(numberString, nullptr, numberBase);
            } catch (std::out_of_range e) {
                throw std::runtime_error("Number out of range");
            }

            std::stringstream realNumberStr;
            realNumberStr << realNumber;

            numberString = realNumberStr.str();
        }
    }


    return Lexeme{
            .sourceFile = "",
            .lineNumber = 0,
            .columnNumber = 0,
            .token = numberType,
            .value = numberString,
    };
}

bool isBaseDigit(char c, int base) {
    if (base == 2) {
        return c == '0' || c == '1';
    } else if (base == 8) {
        return c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' ||
               c == '6' || c == '7';
    } else if (base == 10) {
        return (bool)std::isdigit(c);
    } else if (base == 16) {
        return (bool)std::isxdigit(c);
    } else {
        return false;
    }
}


int prefixToBase(Prefix prefix) {
    switch (prefix) {
        case HEXADECIMAL_PREFIX: return 16;
        case BINARY_PREFIX: return 2;
        case OCTAL_PREFIX: return 8;
        default: return -1;
    }
}

bool validSuffixStarter(char suffix) {
    return suffix == 'i' || suffix == 'f' || suffix == 'd' || suffix == 'u';
}

bool validPrefix(char prefix) {
    return prefix == 'o' || prefix == 'x' || prefix == 'b';
}

bool signedValue(Token ty) {
    return ty == Token::INT_VAL || ty == Token::INT8_VAL || ty == Token::INT16_VAL ||
           ty == Token::INT32_VAL || ty  == Token::INT64_VAL;
}


Prefix getPrefixFromChar(char c) {
    switch (c) {
        case 'b': return Prefix::BINARY_PREFIX;
        case 'o': return Prefix::OCTAL_PREFIX;
        case 'x': return Prefix::HEXADECIMAL_PREFIX;
        default: return Prefix::NO_PREFIX;
    }
}

Prefix lexPrefix(std::istream& input) {
    if (input.peek() != '0') return Prefix::NO_PREFIX;
    char val = (char)input.get();
    char next = (char)input.peek();

    if (next == '.') {
        // Found a floating-point number; put the 0 back
        input.putback('0');
        return Prefix::NO_PREFIX;
    }

    if (validPrefix(next)) {
        input.get();

        return getPrefixFromChar(next);
    } else if (!validSuffixStarter(next)) {
        std::stringstream errMsg;
        errMsg << "Invalid numeric prefix " << next;
        throw std::runtime_error(errMsg.str());
    } else {
        return Prefix::NO_PREFIX;
    }
}

bool validNumberStringForBase(std::string num, int base) {
    for (char c : num) {
        // Ignore periods if we're base 10
        if (c == '.' && base == 10) continue;

        if (!isBaseDigit(c, base)) return false;
    }

    return true;
}

Token lexNumberSuffix(std::istream& input) {
    std::string suffix = "";

    // Get all alnum
    while (std::isalnum(input.peek())) {
        suffix += (char)input.get();
    }

    if (suffix == "f") {
        return Token::FLOAT_VAL;
    } else if (suffix == "d") {
        return Token::DOUBLE_VAL;
    } else if (suffix == "u") {
        return Token::UINT_VAL;
    } else if (suffix == "u8") {
        return Token::UINT8_VAL;
    } else if (suffix == "u16") {
        return Token::UINT16_VAL;
    } else if (suffix == "u32") {
        return Token::UINT32_VAL;
    } else if (suffix == "u64") {
        return Token::UINT64_VAL;
    } else if (suffix == "i") {
        return Token::INT_VAL;
    } else if (suffix == "i8") {
        return Token::INT8_VAL;
    } else if (suffix == "i16") {
        return Token::INT16_VAL;
    } else if (suffix == "i32") {
        return Token::INT32_VAL;
    } else if (suffix == "i64") {
        return Token::INT64_VAL;
    } else if (suffix != "") {
        std::stringstream errMsg;
        errMsg << "Invalid suffix " << suffix;
        throw std::runtime_error(errMsg.str());
    } else {
        return Token::TOKEN_EOF;
    }
}

