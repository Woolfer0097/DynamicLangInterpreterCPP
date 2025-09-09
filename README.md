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

Dump tokens from file:

```bash
./lexdump tests/lexer/keywords_identifiers.txt | sed -n '1,20p'
```

Run lexer over all tests (relative paths, no abbreviations):

```bash
# Build lexdump from repo root
g++ -std=c++17 -O2 -Wall -Wextra -I. -o lexdump tools/lexdump.cpp lexer/lexer.cpp

# Run lexdump on every .txt under tests/
find tests -type f -name '*.txt' -print0 | xargs -0 -I{} sh -c './lexdump "$1"' _ {} > tokens.log
```

