# Semantic Analysis Tests

This directory contains tests for the semantic analyzer (Stage 3 of the compiler).

## Test Files

### Checks (Non-modifying)
- **exit_outside_loop_test.txt** - Tests that `exit` can only be used inside loops
- **return_outside_function_test.txt** - Tests that `return` can only be used inside functions  
- **undeclared_variable_test.txt** - Tests that variables must be declared before use
- **correct_usage_test.txt** - Tests valid code that should pass all semantic checks

### Optimizations (AST Modifying)
- **constant_folding_test.txt** - Tests constant expression simplification
- **if_simplification_test.txt** - Tests `if True/False` statement simplification
- **unreachable_code_test.txt** - Tests removal of unreachable code after `return`

## Running Tests

Use the semantic analyzer tool to run tests:

```bash
# Check for semantic errors
./semantic_analyzer tests/semantic_analysis/exit_outside_loop_test.txt

# Check optimizations
./semantic_analyzer tests/semantic_analysis/constant_folding_test.txt
```

## Expected Results

### Error Tests
Files with `_test.txt` that should produce semantic errors:
- `exit_outside_loop_test.txt` - Should report errors about `exit` outside loops
- `return_outside_function_test.txt` - Should report errors about `return` outside functions
- `undeclared_variable_test.txt` - Should report errors about undeclared variables

### Optimization Tests
Files that should pass checks and show optimized AST:
- `constant_folding_test.txt` - Should show constant expressions simplified
- `if_simplification_test.txt` - Should show `if True/False` simplified
- `unreachable_code_test.txt` - Should show unreachable code removed

### Correct Usage Tests
- `correct_usage_test.txt` - Should pass all checks with no errors

