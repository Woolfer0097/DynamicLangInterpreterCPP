Repo for Inno Compiler Course

Build and run lexer tools

Compile demo and lexdump:

```bash
g++ -std=c++17 -O2 -Wall -Wextra -I. -o dli main.cpp lexer/lexer.cpp
g++ -std=c++17 -O2 -Wall -Wextra -I. -o lexdump tools/lexdump.cpp lexer/lexer.cpp
```

Run demo:

```bash
./dli
```

Run lexer over all tests:

```bash
# Build lexdump from repo root
g++ -std=c++17 -O2 -Wall -Wextra -I. -o lexdump tools/lexdump.cpp lexer/lexer.cpp

# Run lexdump on every .txt under tests/
find tests -type f -name '*.txt' -print0 | xargs -0 -I{} sh -c './lexdump "$1"' _ {} > tokens.log
```

Build parser (Bison C++), AST pretty-printer, and print tool:

```bash
# Generate parser (from repo root)
bison -o lexer/parser.cpp -H lexer/parser.hpp lexer/parser.y

# Build print_ast tool
g++ -std=c++17 -O2 -Wall -Wextra -I. \
    -o print_ast \
    tools/print_ast.cpp \
    lexer/lexer.cpp \
    lexer/parser.cpp \
    ast/AcceptImpl.cpp

# Usage
./print_ast tests/expressions/arithmetic_test.txt
```

Build semantic analyzer tool:

```bash
# Generate parser (from repo root) - if not already done
bison -o lexer/parser.cpp -H lexer/parser.hpp lexer/parser.y

# Build semantic_analyzer tool
g++ -std=c++17 -O2 -Wall -Wextra -I. \
    -o semantic_analyzer \
    tools/semantic_analyzer.cpp \
    lexer/lexer.cpp \
    lexer/parser.cpp \
    ast/AcceptImpl.cpp

# Usage
./semantic_analyzer tests/expressions/arithmetic_test.txt
```

