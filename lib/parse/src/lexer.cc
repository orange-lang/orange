/*
** Copyright 2014-2017 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <cctype>
#include <sstream>
#include <iostream>

#include "lexer.h"
#include "lexeme.h"

using namespace orange::parse;

bool isBaseDigit(int c, int base) {
    if (base == 2) {
        return c == '0' || c == '1';
    } else if (base == 8) {
        return c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' ||
               c == '6' || c == '7';
    } else if (base == 10) {
        return (bool)std::isdigit(c);
    } else if (base == 16) {
        return (bool)std::isxdigit(c);
    }
}


int prefixToBase(char prefix) {
    switch (prefix) {
        case 'x': return 16;
        case 'b': return 2;
        case 'o': return 8;
        default: return -1;
    }
}

bool validSuffixStarter(char suffix) {
    return suffix == 'i' || suffix == 'f' || suffix == 'd' || suffix == 'u';
}

bool validPrefix(char prefix) {
    return prefixToBase(prefix) != -1;
}

bool signedValue(Token ty) {
    return ty == Token::INT_VAL || ty == Token::INT8_VAL || ty == Token::INT16_VAL ||
           ty == Token::INT32_VAL || ty  == Token::INT64_VAL;
}

Lexer::Lexer(std::istream& input) : mInput(input) { }

Lexeme Lexer::lexNumber() {
    std::string sourceValue;
    Token numberType = Token::INT_VAL;
    int numberBase = 10;

    // If it starts with 0, it's either a float or another prefix
    if (mInput.peek() == '0') {
        char val = (char)mInput.get();

        char next = (char)mInput.peek();
        if (next == '.') {
            sourceValue += val;

            char newVal = (char)mInput.get();
            sourceValue += newVal;
            numberType = Token::DOUBLE_VAL;
        } else if (validPrefix(next)) {
            mInput.get();
            numberBase = prefixToBase(next);
            numberType = Token::UINT_VAL;
        } else if (!validSuffixStarter(next)) {
            std::stringstream errMsg;
            errMsg << "Invalid numeric prefix " << next;
            throw std::runtime_error(errMsg.str());
        }
    }

    while (isBaseDigit(mInput.peek(), numberBase)) {
        char val = (char)mInput.get();
        sourceValue += val;

        // Consume all separators
        while (mInput.peek() == '_') mInput.get();

        // If we found a . and we're not already a double
        if (mInput.peek() == '.' && numberType != Token::DOUBLE_VAL) {
            sourceValue += mInput.get();
            numberType = Token::DOUBLE_VAL;
        }
    }

    // If there's still a digit of base 10, the user inputted
    // an invalid number
    if (std::isdigit(mInput.peek())) {
        std::stringstream errMsg;
        errMsg << "Invalid digit " << (char)mInput.peek() << " for a number of base " << numberBase;
        throw std::runtime_error(errMsg.str());
    } else if (std::isxdigit(mInput.peek()) && mInput.peek() != 'f' && mInput.peek() != 'F') {
        // Invalid hex digit, treat it like a bad suffix
        std::stringstream errMsg;
        errMsg << "Invalid suffix " << (char)mInput.peek();
        throw std::runtime_error(errMsg.str());
    }

    // If last character is ., we want to convert it BACK to a regular number and ignore suffixes
    // This allows for 5.method()
    if (sourceValue[sourceValue.size()-1] == '.') {
        mInput.putback('.');
        sourceValue = sourceValue.substr(0, sourceValue.size() - 1);
        numberType = (numberBase == 10) ? Token::INT_VAL : Token::UINT_VAL;
    } else {
        std::string suffix = "";

        // Get all alnum
        while (std::isalnum(mInput.peek())) {
            suffix += (char)mInput.get();
        }

        if (suffix == "f") {
            numberType = Token::FLOAT_VAL;
        } else if (suffix == "d") {
            numberType = Token::DOUBLE_VAL;
        } else if (suffix == "u") {
            numberType = Token::UINT_VAL;
        } else if (suffix == "u8") {
            numberType = Token::UINT8_VAL;
        } else if (suffix == "u16") {
            numberType = Token::UINT16_VAL;
        } else if (suffix == "u32") {
            numberType = Token::UINT32_VAL;
        } else if (suffix == "u64") {
            numberType = Token::UINT64_VAL;
        } else if (suffix == "i") {
            numberType = Token::INT_VAL;
        } else if (suffix == "i8") {
            numberType = Token::INT8_VAL;
        } else if (suffix == "i16") {
            numberType = Token::INT16_VAL;
        } else if (suffix == "i32") {
            numberType = Token::INT32_VAL;
        } else if (suffix == "i64") {
            numberType = Token::INT64_VAL;
        } else if (suffix != "") {
            std::stringstream errMsg;
            errMsg << "Invalid suffix " << suffix;
            throw std::runtime_error(errMsg.str());
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
        if (sourceValue.find(".") != std::string::npos) {
            std::stringstream errMsg;
            errMsg << "Floating-point value can not have integral suffix";
            throw std::runtime_error(errMsg.str());
        }

        // If we're dealing with a non-decimal number, we need to convert it
        if (numberBase != 10) {
            long realNumber;
            try {
                realNumber = std::stol(sourceValue, nullptr, numberBase);
            } catch (std::out_of_range e) {
                throw std::runtime_error("Number out of range");
            }

            std::stringstream realNumberStr;
            realNumberStr << realNumber;

            sourceValue = realNumberStr.str();
        }
    }


    return Lexeme{
            .sourceFile = "",
            .lineNumber = 0,
            .columnNumber = 0,
            .token = numberType,
            .value = sourceValue,
    };
}

Lexeme Lexer::next() {
    // Consume all whitespace
    while (std::isspace(mInput.peek())) mInput.get();

    if (std::isdigit(mInput.peek())) {
        return lexNumber();
    }

	return Lexeme();
}


