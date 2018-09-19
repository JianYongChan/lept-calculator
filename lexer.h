#ifndef LEPT_CALCULATOR_LEXER_H__
#define LEPT_CALCULATOR_LEXER_H__


#include <iostream>
#include <cassert>
#include "token.h"

class Lexer {
    public:
        explicit Lexer(const std::string text)
            : text_(text),
              current_pos_(0) {
            assert(!text.empty());
            current_char_ = text_[0];
        }

        Token GetNextToken();

        void SkipWhitespace();

        void Advance();

        void Error();

        // print is the best debugger 🤢
        void Debug() {
            std::cout << "text = " << text_ 
                      << "\t pos = " << current_pos_ 
                      << "\t char = " << current_char_ 
                      << std::endl;
        }

    private:
        std::string text_;
        std::string::size_type current_pos_;
        char current_char_;
};

void Lexer::Advance() {
    if (current_pos_ < text_.size()) {
        ++current_pos_;
        current_char_ = text_[current_pos_];
    } else {
        current_char_ = '\0';
    }
}

void Lexer::SkipWhitespace() {
    while (current_char_ != '\0' && isspace(current_char_))
        Advance();
}

void Lexer::Error() {
}

Token Lexer::GetNextToken() {
    while (current_char_ != '\0') {
        if (isspace(current_char_)) {
            SkipWhitespace();
            continue;
        } else if (isdigit(current_char_)) {
            std::string value;
            while (current_pos_ < text_.size() && isdigit(current_char_)) {
                value.push_back(current_char_);
                Advance();
            }
            return Token(kNumber, value);
        } else if (current_char_ == '+') {
            Advance();
            return Token(kPlus, "+");
        } else if (current_char_ == '-') {
            Advance();
            return Token(kMinus, "-");
        } else if (current_char_ == '*') {
            Advance();
            return Token(kMulti, "*");
        } else if (current_char_ == '/') {
            Advance();
            return Token(kDivid, "/");
        } else if (current_char_ == '(') {
            Advance();
            return Token(kLparen, "(");
        } else if (current_char_ == ')') {
            Advance();
            return Token(kRparen, ")");
        }else {
            return Token(kError, "Invalid Character");
        }
    }

    return Token(kEOF, "EOF");
}

#endif /* LEPT_CALCULATOR_LEXER_H__ */
