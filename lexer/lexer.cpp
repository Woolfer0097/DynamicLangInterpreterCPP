// minimal implementation of the lexer
#include "lexer.hpp"

#include <cctype>
#include <unordered_map>

namespace dli {

namespace {
    const std::unordered_map<std::string_view, TokenType> kKeywords = {
        {"var", TokenType::KwVar}, {"if", TokenType::KwIf}, {"then", TokenType::KwThen},
        {"else", TokenType::KwElse}, {"end", TokenType::KwEnd}, {"loop", TokenType::KwLoop},
        {"exit", TokenType::KwExit}, {"return", TokenType::KwReturn}, {"print", TokenType::KwPrint},
        {"while", TokenType::KwWhile}, {"for", TokenType::KwFor}, {"func", TokenType::KwFunc},
        {"true", TokenType::KwTrue}, {"false", TokenType::KwFalse}, {"none", TokenType::KwNone},
        {"and", TokenType::KwAnd}, {"or", TokenType::KwOr}, {"xor", TokenType::KwXor}, {"not", TokenType::KwNot},
        {"test", TokenType::KwTest}, {"assert", TokenType::KwAssert},
        {"is", TokenType::KwIs}, {"in", TokenType::KwIn},
        {"int", TokenType::KwInt}, {"real", TokenType::KwReal}, {"bool", TokenType::KwBool}, {"string", TokenType::KwString},
    };
}

Lexer::Lexer(std::string_view source) noexcept : source_(source) {}

bool Lexer::isAtEnd() const noexcept { return current_ >= source_.size(); }

char Lexer::peek() const noexcept { return isAtEnd() ? '\0' : source_[current_]; }

char Lexer::peekNext() const noexcept { return (current_ + 1 >= source_.size()) ? '\0' : source_[current_ + 1]; }

char Lexer::advance() noexcept {
    if (isAtEnd()) return '\0';
    char c = source_[current_++];
    if (c == '\n') {
        location_.line++;
        location_.column = 1;
    } else {
        location_.column++;
    }
    return c;
}

bool Lexer::match(char expected) noexcept {
    if (isAtEnd() || source_[current_] != expected) return false;
    advance();
    return true;
}

Token Lexer::makeToken(TokenType type, std::string_view lexeme) const {
    Token t;
    t.type = type;
    t.lexeme = std::string(lexeme);
    t.location = token_start_location_;
    t.start_index = start_;
    t.length = current_ - start_;
    t.message = "";

    return t;
}

Token Lexer::makeError(std::string_view message) const {
    Token t;
    t.type = TokenType::Error;
    t.lexeme = "";
    t.location = token_start_location_;
    t.start_index = start_;
    t.length = current_ - start_;
    t.message = std::string(message);

    return t;
}

std::optional<Token> Lexer::skipWhitespaceAndComments() {
    while (true) {
        char c = peek();
        switch (c) {
            case ' ': case '\r': case '\t': case '\n':
                advance();
                break;
            case '/':
                if (peekNext() == '/') { // // line comment
                    // consume '//' and skip to end of line
                    advance(); // consume '/'
                    advance(); // consume second '/'
                    while (peek() != '\n' && !isAtEnd()) advance();
                    break;
                } else if (peekNext() == '*') { // /* block comment */
                    // mark start of the comment so we can report error at its start if unterminated
                    token_start_location_ = location_;
                    start_ = current_;
                    advance(); // consume '/'
                    advance(); // consume '*'
                    // until closing */
                    while (!isAtEnd()) {
                        if (peek() == '*' && peekNext() == '/') {
                            advance(); // consume '*'
                            advance(); // consume '/'
                            break; // comment closed, continue outer loop
                        }
                        advance();
                    }
                    if (isAtEnd()) {
                        // unterminated block comment -> return error token
                        return makeError("Unterminated block comment");
                    }
                    break;
                } else {
                    return std::nullopt;
                }
            default:
                return std::nullopt;
        }
    }
}

Token Lexer::scanIdentifierOrKeyword() {
    std::size_t start_index = current_ - 1; // we assume first char already consumed
    while (isAlphaNumeric(peek()) || peek() == '_') advance();
    std::string_view text = source_.substr(start_index, current_ - start_index);
    auto it = kKeywords.find(text);
    if (it != kKeywords.end()) {
        // boolean literals as keywords too
        return makeToken(it->second, text);
    }
    return makeToken(TokenType::Identifier, text);
}

Token Lexer::scanNumber() {
    std::size_t start_index = current_ - 1; // first digit consumed
    while (isDigit(peek())) advance();
    bool is_real = false;
    if (peek() == '.' && isDigit(peekNext())) { // real like 12.34
        is_real = true;
        advance(); // '.'
        while (isDigit(peek())) advance();
    }
    // Handle 12. (decide: treat as real with trailing dot error?) We'll allow 12. as real and stop at '.' if no digits after.
    if (!is_real && peek() == '.' && !isDigit(peekNext())) {
        // Do not consume '.' here; leave it for symbol scanning. Keep as integer.
    }
    std::string_view text = source_.substr(start_index, current_ - start_index);
    return makeToken(is_real ? TokenType::Real : TokenType::Integer, text);
}

Token Lexer::scanString() {
    char quote = source_[current_ - 1]; // ' or " consumed
    std::size_t start_index = current_;
    while (!isAtEnd()) {
        char c = advance();
        if (c == '\n') {
            return makeError("Unterminated string literal");
        }
        if (c == '\\') {
            // escape next char
            if (isAtEnd()) return makeError("Unterminated string escape");
            advance();
            continue;
        }
        if (c == quote) {
            std::string_view content = source_.substr(start_index, (current_ - 1) - start_index);
            return makeToken(TokenType::String, content);
        }
    }
    return makeError("Unterminated string literal");
}

bool Lexer::isAlpha(char c) noexcept { return std::isalpha(static_cast<unsigned char>(c)) != 0; }
bool Lexer::isDigit(char c) noexcept { return std::isdigit(static_cast<unsigned char>(c)) != 0; }
bool Lexer::isAlphaNumeric(char c) noexcept { return isAlpha(c) || isDigit(c); }

Token Lexer::scanSymbol() {
    char c = source_[current_ - 1];
    switch (c) {
        case ':':
            if (match('=')) return makeToken(TokenType::AssignColon, ":=");
            return makeError("Unexpected ':' (did you mean ':=')");
        case '=':
            if (match('=')) return makeToken(TokenType::EqualEqual, "==");
            if (match('>')) return makeToken(TokenType::Arrow, "=>");
            return makeToken(TokenType::Equal, "=");
        case '<':
            if (match('=')) return makeToken(TokenType::LessEqual, "<=");
            return makeToken(TokenType::Less, "<");
        case '>':
            if (match('=')) return makeToken(TokenType::GreaterEqual, ">=");
            return makeToken(TokenType::Greater, ">");
        case '/':
            if (match('=')) return makeToken(TokenType::NotEqualSlash, "/=");
            return makeToken(TokenType::Slash, "/");
        case '+': return makeToken(TokenType::Plus, "+");
        case '-': return makeToken(TokenType::Minus, "-");
        case '*': return makeToken(TokenType::Star, "*");
        case '(': return makeToken(TokenType::LParen, "(");
        case ')': return makeToken(TokenType::RParen, ")");
        case '[': return makeToken(TokenType::LBracket, "[");
        case ']': return makeToken(TokenType::RBracket, "]");
        case '{': return makeToken(TokenType::LBrace, "{");
        case '}': return makeToken(TokenType::RBrace, "}");
        case '.':
            if (match('.')) return makeToken(TokenType::DotDot, "..");
            return makeToken(TokenType::Dot, ".");
        case ';': return makeToken(TokenType::Semicolon, ";");
        case ',': return makeToken(TokenType::Comma, ",");
        default:
            return makeError("Unknown character");
    }
}

Token Lexer::nextToken() {
    skipWhitespaceAndComments();

    token_start_location_ = location_;
    start_ = current_;
    if (isAtEnd()) return makeToken(TokenType::EndOfFile, "");
    char c = advance();

    if (isAlpha(c) || c == '_') return scanIdentifierOrKeyword();
    if (isDigit(c)) return scanNumber();
    if (c == '"' || c == '\'') return scanString();

    return scanSymbol();
}

} // namespace dli


