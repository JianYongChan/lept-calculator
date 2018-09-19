#include <stdio.h>
#include <iostream>
#include "parser.h"

static void test_1() {
    std::cout <<"-------------" << __FUNCTION__ << "--------------" << std::endl;

    std::string str = "  37 + 4 * 51 / 2 + 7";
    Lexer lexer(str);
    Token token;
    do {
        // lexer.Debug();
        token = lexer.GetNextToken();
        std::cout << token.ToString() << std::endl;
    } while (token.type != kError && token.type != kEOF);
}

static void test_2() {
    std::cout <<"-------------" << __FUNCTION__ << "--------------" << std::endl;

    std::string str = " (37 + 7) * 13 / (51 - 25)";
    std::string str2 = "17 + 13 * 15 - 15 * 12";
    std::string str3 = " (17) + 19 * 21 / 3 - 23 * (5 + 7) ";
    Lexer lexer(str3);
    Parser parser(lexer);
    printf("result of (%s) is %lf", str3.c_str(), parser.Expr());
}

int main(void) {
    test_1();
    test_2();
}
