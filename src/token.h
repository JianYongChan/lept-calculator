#ifndef LEPT_CALCULATOR_TOKEN_H__
#define LEPT_CALCULATOR_TOKEN_H__

#include <string>

enum Type {
    kNumber = 0,
    kLparen = 1,
    kRparen = 2,
    kPlus = 3,
    kMinus = 4,
    kMulti = 5,
    kDivid = 6,
    kEOF = 7,
    kError = 8
};

struct Token {
    public:
        Token() = default;
        Token(const Token &) = default; 

        Token(Type t, const std::string &v)
            : type(t),
              value(v) {  }

        std::string ToString() const {
            return value;
        }

        Type type;
        std::string value;
};

#endif /* LEPT_CALCULATOR_TOKEN_H__ */
