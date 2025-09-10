#ifndef DLI_LEXER_HPP
#define DLI_LEXER_HPP

#include <cstddef>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include "token.hpp"

namespace dli {

class Lexer {
public:
    explicit Lexer(std::string_view source) noexcept;

    Token nextToken();

    Location currentLocation() const noexcept { return location_; }

private:
    // core
    Token makeToken(TokenType type, std::string_view lexeme) const;
    Token makeError(std::string_view message) const;

    // movement
    bool isAtEnd() const noexcept;
    char peek() const noexcept;
    char peekNext() const noexcept;
    char advance() noexcept;
    bool match(char expected) noexcept;

    // skipping
    std::optional<Token> skipWhitespaceAndComments();

    // scanners
    Token scanIdentifierOrKeyword();
    Token scanNumber();
    Token scanString();

    // helpers
    static bool isAlpha(char c) noexcept;
    static bool isDigit(char c) noexcept;
    static bool isAlphaNumeric(char c) noexcept;

    Token scanSymbol();

private:
    std::string_view source_;
    std::size_t start_ {0};
    std::size_t current_ {0};
    Location location_ {1, 1};
    Location token_start_location_ {1, 1};
};

} // namespace dli

#endif // DLI_LEXER_HPP


