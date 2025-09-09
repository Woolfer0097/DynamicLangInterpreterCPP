#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include "lexer/lexer.hpp"

using namespace dli;

static const std::unordered_map<TokenType, std::string> kTypeToString = {
    {TokenType::EndOfFile, "EOF"}, {TokenType::Error, "ERROR"},
    {TokenType::Identifier, "IDENT"}, {TokenType::Integer, "INT"},
    {TokenType::Real, "REAL"}, {TokenType::String, "STRING"}, {TokenType::Boolean, "BOOLEAN"},
    {TokenType::KwVar, "KW_var"}, {TokenType::KwIf, "KW_if"}, {TokenType::KwThen, "KW_then"},
    {TokenType::KwElse, "KW_else"}, {TokenType::KwEnd, "KW_end"}, {TokenType::KwLoop, "KW_loop"},
    {TokenType::KwExit, "KW_exit"}, {TokenType::KwReturn, "KW_return"}, {TokenType::KwPrint, "KW_print"},
    {TokenType::KwWhile, "KW_while"}, {TokenType::KwFor, "KW_for"}, {TokenType::KwFunc, "KW_func"},
    {TokenType::KwTrue, "KW_true"}, {TokenType::KwFalse, "KW_false"}, {TokenType::KwNone, "KW_none"},
    {TokenType::KwAnd, "KW_and"}, {TokenType::KwOr, "KW_or"}, {TokenType::KwXor, "KW_xor"}, {TokenType::KwNot, "KW_not"},
    {TokenType::KwTest, "KW_test"}, {TokenType::KwAssert, "KW_assert"},
    {TokenType::KwIs, "KW_is"}, {TokenType::KwIn, "KW_in"},
    {TokenType::KwInt, "KW_int"}, {TokenType::KwReal, "KW_real"}, {TokenType::KwBool, "KW_bool"}, {TokenType::KwString, "KW_string"},
    {TokenType::AssignColon, ":="}, {TokenType::Equal, "="}, {TokenType::EqualEqual, "=="}, {TokenType::Less, "<"},
    {TokenType::LessEqual, "<="}, {TokenType::Greater, ">"}, {TokenType::GreaterEqual, ">="},
    {TokenType::NotEqualSlash, "/="}, {TokenType::Arrow, "=>"}, {TokenType::Plus, "+"}, {TokenType::Minus, "-"},
    {TokenType::Star, "*"}, {TokenType::Slash, "/"}, {TokenType::LParen, "("}, {TokenType::RParen, ")"},
    {TokenType::LBracket, "["}, {TokenType::RBracket, "]"}, {TokenType::LBrace, "{"}, {TokenType::RBrace, "}"},
    {TokenType::Dot, "."}, {TokenType::Semicolon, ";"}, {TokenType::Comma, ","},
};

static std::string readAll(std::istream &in) {
    std::ostringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

int main(int argc, char** argv) {
    std::ios::sync_with_stdio(false);

    std::string source;
    if (argc > 1) {
        std::ifstream f(argv[1]);
        if (!f) {
            std::cerr << "Cannot open file: " << argv[1] << "\n";
            return 1;
        }
        source = readAll(f);
    } else {
        source = readAll(std::cin);
    }

    Lexer lexer(source);
    while (true) {
        Token t = lexer.nextToken();
        auto it = kTypeToString.find(t.type);
        std::string tname = (it == kTypeToString.end()) ? std::to_string(static_cast<int>(t.type)) : it->second;
        std::cout << tname << "\t" << t.lexeme << "\t" << t.location.line << ':' << t.location.column;
        if (!t.message.empty()) std::cout << "\t" << t.message;
        std::cout << "\n";
        if (t.type == TokenType::EndOfFile || t.type == TokenType::Error) break;
    }
    return 0;
}


