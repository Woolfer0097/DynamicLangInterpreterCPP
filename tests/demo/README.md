# Demo Tests for Final Presentation

This folder contains curated demo tests showcasing the key features of the Dynamic Language Interpreter.

## Demo Files

1. **01_basic_features.txt** - Basic language features (literals, variables, arithmetic, conditionals)
2. **02_sparse_arrays.txt** - Dynamic sparse array implementation
3. **03_closures.txt** - Closures and lexical scoping
4. **04_recursion.txt** - Recursive functions (Fibonacci, factorial)
5. **05_data_structures.txt** - Complex nested data structures
6. **06_functional_programming.txt** - Map, filter, reduce patterns
7. **07_arrow_functions.txt** - Arrow function syntax
8. **08_control_flow.txt** - Loops and control statements
9. **09_complete_example.txt** - Complete application example
10. **10_static_checks.txt** - Semantic checker error showcase

## Running Demos

Run individual demos:
```bash
./dli tests/demo/01_basic_features.txt
./dli tests/demo/02_sparse_arrays.txt
# ... etc
```

Run all demos:
```bash
for file in tests/demo/*.txt; do
    echo "Running $file..."
    ./dli "$file"
    echo ""
done
```

## Presentation Tips

- Start with **01_basic_features.txt** to show fundamental capabilities
- Use **02_sparse_arrays.txt** to highlight unique sparse array feature
- Demonstrate **04_closures.txt** to show advanced scoping
- End with **10_complete_example.txt** to show real-world usage

