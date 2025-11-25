Repo for Inno Compiler Course

## Key Implementation Notes

- **Array/Tuple Indexing**: Uses 1-based indexing (arr[1] is first element)
- **Dynamic Sparse Arrays**: Arrays support sparse indexing (arr[10], arr[100], arr[1000]) without preallocation
- **Variable Scoping**: Block scopes work correctly with lexical scoping for functions
- **Control Flow**: All basic control flow works (if/else, loops, exit, return)
- **Functions**: Full function support including recursion, closures, and arrow functions
- **Named Tuples**: Tuples support named fields with both name and index access
- **Array Concatenation**: Arrays can be concatenated using the + operator

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

Build interpreter:

```bash
# Generate parser (from repo root) - if not already done
bison -d lexer/parser.y -o lexer/parser.cpp

# Build interpreter
g++ -std=c++17 -o dli \
    main.cpp \
    lexer/lexer.cpp \
    lexer/parser.cpp \
    ast/AcceptImpl.cpp \
    interpreter/Interpreter.cpp \
    -I.

# Usage - run a program file
./dli tests/basic/literals_test.txt
./dli tests/functions/function_literal_test.txt

# Run all tests
for f in tests/*/*.txt; do 
    echo "Testing $f"
    ./dli "$f"
done
```
