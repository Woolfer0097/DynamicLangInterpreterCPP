#include <iostream>
#include <string>
#include <vector>
#include "lexer/lexer.hpp"

using namespace dli;

int main() {
    std::string source = R"(var x := 12.34
print(x)
if x >= 10 then
  // comment
  x := x + 1
end
)";

    Lexer lexer(source);
    while (true) {
        Token t = lexer.nextToken();
        std::cout << static_cast<int>(t.type) << " | '" << t.lexeme << "' @ "
                  << t.location.line << ":" << t.location.column;
        if (!t.message.empty()) std::cout << " | error: " << t.message;
        std::cout << "\n";
        if (t.type == TokenType::EndOfFile) break;
        if (t.type == TokenType::Error) break;
    }
    return 0;
}


