#ifndef DLI_TOKEN_HPP
#define DLI_TOKEN_HPP

#include <string>

namespace dli {

enum class TokenType {
    // Special
    EndOfFile,
    Error,

    // Identifiers & literals
    Identifier,
    Integer,
    Real,
    String,
    Boolean,

    // Keywords
    KwVar,
    KwIf,
    KwThen,
    KwElse,
    KwEnd,
    KwLoop,
    KwExit,
    KwReturn,
    KwPrint,
    KwWhile,
    KwFor,
    KwFunc,
    KwTrue,
    KwFalse,
    KwNone,
    KwAnd,
    KwOr,
    KwXor,
    KwNot,
    KwTest,
    KwAssert,
    KwIs,
    KwIn,
    KwInt,
    KwReal,
    KwBool,
    KwString,

    // Operators & symbols
    AssignColon,     // :=
    Equal,           // =
    EqualEqual,      // ==
    Arrow,           // =>
    Less,            // <
    LessEqual,       // <=
    Greater,         // >
    GreaterEqual,    // >=
    NotEqualSlash,   // /=
    Plus,            // +
    Minus,           // -
    Star,            // *
    Slash,           // /
    LParen,          // (
    RParen,          // )
    LBracket,        // [
    RBracket,        // ]
    LBrace,          // {
    RBrace,          // }
    Dot,             // .
    DotDot,          // ..
    Semicolon,       // ;
    Comma            // ,
};

struct Location {
    std::size_t line {1};
    std::size_t column {1};
};

struct Token {
    TokenType type {TokenType::Error};
    std::string lexeme;
    Location location;
    std::size_t start_index{0}; // more deatil in errors and easy get substring
    std::size_t length{0};
    std::string message; // for error tokens
};

} // namespace dli

#endif // DLI_TOKEN_HPP


