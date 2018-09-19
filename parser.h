#ifndef LEPT_CALCULATOR_PARSER_H__
#define LEPT_CALCULATOR_PARSER_H__

#include "lexer.h"

/*
 * 这里最重要的就是处理结合性和优先级两个问题了
 * 解析采用的方法是递归下降
 */
class Parser {
    public:
        explicit Parser(Lexer &lexer)
            : lexer_(&lexer) {
            current_token_ = lexer_->GetNextToken();
        }

        double Factor();

        double Term();

        double Expr();

        void Error() const;

        bool Eat(Type t);

        void Debug() const {
            lexer_->Debug();
            std::cout << "token = " << current_token_.ToString() << std::endl;
        }

    private:
        Lexer *const lexer_;
        Token current_token_;
};

void Parser::Error() const {
    std::cout << "Parsing Invalid Syntax error occurred at line " << __LINE__ << std::endl;
}

bool Parser::Eat(Type t) {
    if (current_token_.type == t) {
        current_token_ = lexer_->GetNextToken();
        return true;
    } else {
        Error();
        return false;
    }
}

/*
 * factor : digit
 *        | (expr)
 */
double Parser::Factor() {
    double result = 0.0;
    if (current_token_.type == kNumber) {
        result = std::stoi(current_token_.value);
        Eat(kNumber);
    } else if (current_token_.type == kLparen) {
        assert(Eat(kLparen));
        result = Expr();
        assert(Eat(kRparen));
    }

    return result;
}

/*
 * term : factor ((MULTI | DIVID) factor)*
 */
double Parser::Term() {
    double result = Factor();
    while (current_token_.type == kMulti || current_token_.type == kDivid) {
        if (current_token_.type == kMulti) {
            Eat(kMulti);
            result *= Factor();
        } else {
            Eat(kDivid);
            Debug();
            int divisor = Factor();
            assert(divisor != 0);
            result /= divisor;
        }
    }

    return result;
}

/*
 * expr : term ((PLUS | MINUS) term)*
 */
double Parser::Expr() {
    double result = Term();
    while (current_token_.type == kPlus || current_token_.type == kMinus) {
        std::cout << "result = " << result << std::endl;
        if (current_token_.type == kPlus) {
            Eat(kPlus);
            result += Term();
        } else {
            Eat(kMinus);
            result -= Term();
        }
    }

    return result;
}
#endif /* LEPT_CALCULATOR_PARSER_H__ */
