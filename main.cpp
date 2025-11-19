#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "lexer/lexer.hpp"
#include "lexer/parser.hpp"
#include "ast/SemanticAnalyzer.hpp"
#include "interpreter/Interpreter.hpp"

namespace dli {
    extern std::shared_ptr<ASTNode> g_root;
}

using namespace dli;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Could not open file: " << argv[1] << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();

    // 1. Lexing (implicit in Parser)
    Lexer lexer(source);
    
    // 2. Parsing
    Parser parser(lexer);
    if (parser.parse() != 0) {
        std::cerr << "Parsing failed.\n";
        return 1;
    }
    
    if (!g_root) {
        // Empty program
        return 0;
    }

    std::shared_ptr<StatementList> program = std::dynamic_pointer_cast<StatementList>(g_root);
    if (!program) {
        std::cerr << "Invalid AST root.\n";
        return 1;
    }

    // 3. Semantic Analysis
    SemanticChecker checker;
    checker.visit(*program);
    
    if (!checker.errors.empty()) {
        std::cerr << "Semantic errors:\n";
        for (const auto& err : checker.errors) {
            std::cerr << err << "\n";
        }
        return 1;
    }
    
    // 4. Semantic Optimization (Optional)
    SemanticOptimizer optimizer;
    optimizer.visit(*program);

    // 5. Interpretation
    Interpreter interpreter;
    interpreter.interpret(program->statements);

    return 0;
}
