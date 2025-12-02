#include "Interpreter.hpp"
#include "RuntimeError.hpp"
#include <iostream>
#include <cmath>
#include <ctime>

namespace dli {

// Exceptions for control flow
struct ReturnException {
    std::shared_ptr<Value> value;
};

struct BreakException {};

// FunctionValue implementation
int FunctionValue::arity() {
    return declaration->params.size();
}

std::shared_ptr<Value> FunctionValue::call(Interpreter& interpreter, const std::vector<std::shared_ptr<Value>>& args) {
    auto environment = std::make_shared<Environment>(closure);
    for (size_t i = 0; i < declaration->params.size(); ++i) {
        environment->define(declaration->params[i], args[i]);
    }

    try {
        interpreter.executeBlock({declaration->body}, environment);
    } catch (const ReturnException& returnValue) {
        return returnValue.value;
    }

    return std::make_shared<NoneValue>();
}

// Interpreter implementation
Interpreter::Interpreter() {
    globals = std::make_shared<Environment>();
    environment = globals;

    // Define native functions if needed
    globals->define("clock", std::make_shared<BuiltinFunctionValue>(
        [](Interpreter&, const std::vector<std::shared_ptr<Value>>&) -> std::shared_ptr<Value> {
            return std::make_shared<NumberValue>((double)clock() / CLOCKS_PER_SEC);
        }, 0));
        
    // Note: 'print' is a statement in this language, not a function, but we could add one.
}

void Interpreter::interpret(const std::vector<std::shared_ptr<Statement>>& statements) {
    try {
        for (const auto& stmt : statements) {
            execute(stmt);
        }
    } catch (const RuntimeError& error) {
        std::cerr << "Runtime Error: " << error.what() << "\n"
                  << "  [line " << error.loc.firstLine << "]" << std::endl;
    }
}

std::shared_ptr<Value> Interpreter::evaluate(Expression& expr) {
    expr.accept(*this);
    return lastValue;
}

std::shared_ptr<Value> Interpreter::evaluate(const std::shared_ptr<Expression>& expr) {
    return evaluate(*expr);
}

void Interpreter::execute(Statement& stmt) {
    stmt.accept(*this);
}

void Interpreter::execute(const std::shared_ptr<Statement>& stmt) {
    execute(*stmt);
}

void Interpreter::executeBlock(const std::vector<std::shared_ptr<Statement>>& statements, std::shared_ptr<Environment> env) {
    std::shared_ptr<Environment> previous = this->environment;
    this->environment = env;

    try {
        for (const auto& stmt : statements) {
            execute(stmt);
        }
    } catch (...) {
        this->environment = previous;
        throw;
    }

    this->environment = previous;
}

// Helpers
bool Interpreter::isTruthy(const std::shared_ptr<Value>& val) {
    if (auto b = dynamic_cast<BooleanValue*>(val.get())) return b->value;
    if (dynamic_cast<NoneValue*>(val.get())) return false;
    if (auto n = dynamic_cast<NumberValue*>(val.get())) return n->value != 0;
    return true; // All other values are true
}

bool Interpreter::isEqual(const std::shared_ptr<Value>& left, const std::shared_ptr<Value>& right) {
    if (left->type() != right->type()) return false;
    if (auto l = dynamic_cast<NumberValue*>(left.get())) return l->value == dynamic_cast<NumberValue*>(right.get())->value;
    if (auto l = dynamic_cast<StringValue*>(left.get())) return l->value == dynamic_cast<StringValue*>(right.get())->value;
    if (auto l = dynamic_cast<BooleanValue*>(left.get())) return l->value == dynamic_cast<BooleanValue*>(right.get())->value;
    if (dynamic_cast<NoneValue*>(left.get())) return true;
    return false; // Arrays/Objects by reference? equality usually identity or value? Assuming identity for now unless overridden
}

void Interpreter::checkNumberOperand(const SourceLocation& loc, const std::shared_ptr<Value>& operand) {
    if (dynamic_cast<NumberValue*>(operand.get())) return;
    throw RuntimeError(loc, "Operand must be a number.");
}

void Interpreter::checkNumberOperands(const SourceLocation& loc, const std::shared_ptr<Value>& left, const std::shared_ptr<Value>& right) {
    if (dynamic_cast<NumberValue*>(left.get()) && dynamic_cast<NumberValue*>(right.get())) return;
    throw RuntimeError(loc, "Operands must be numbers.");
}

// Visitors
void Interpreter::visit(NumberExpr& e) {
    lastValue = std::make_shared<NumberValue>(e.value);
}

void Interpreter::visit(StringExpr& e) {
    lastValue = std::make_shared<StringValue>(e.value);
}

void Interpreter::visit(BooleanExpr& e) {
    lastValue = std::make_shared<BooleanValue>(e.value);
}

void Interpreter::visit(NoneExpr&) {
    lastValue = std::make_shared<NoneValue>();
}

void Interpreter::visit(VariableExpr& e) {
    // Handle built-in constants
    if (e.name == "True") { lastValue = std::make_shared<BooleanValue>(true); return; }
    if (e.name == "False") { lastValue = std::make_shared<BooleanValue>(false); return; }
    if (e.name == "None") { lastValue = std::make_shared<NoneValue>(); return; }

    lastValue = environment->get(e.name, e.loc);
}

void Interpreter::visit(UnaryExpr& e) {
    auto right = evaluate(e.rhs);

    if (e.op == "-") {
        checkNumberOperand(e.loc, right);
        lastValue = std::make_shared<NumberValue>(-dynamic_cast<NumberValue*>(right.get())->value);
    } else if (e.op == "!" || e.op == "not") {
        lastValue = std::make_shared<BooleanValue>(!isTruthy(right));
    } else {
         throw RuntimeError(e.loc, "Unknown unary operator.");
    }
}

void Interpreter::visit(BinaryExpr& e) {
    auto left = evaluate(e.lhs);
    auto right = evaluate(e.rhs);

    if (e.op == "+") {
        if (auto l = dynamic_cast<NumberValue*>(left.get())) {
            if (auto r = dynamic_cast<NumberValue*>(right.get())) {
                lastValue = std::make_shared<NumberValue>(l->value + r->value);
                return;
            }
        }
        if (auto l = dynamic_cast<StringValue*>(left.get())) {
            if (auto r = dynamic_cast<StringValue*>(right.get())) {
                lastValue = std::make_shared<StringValue>(l->value + r->value);
                return;
            }
        }
        if (auto l = dynamic_cast<ArrayValue*>(left.get())) {
            if (auto r = dynamic_cast<ArrayValue*>(right.get())) {
                // Concatenate sparse arrays
                auto result = std::make_shared<ArrayValue>();
                long long nextIdx = 1;
                
                // Copy left array elements in order
                for (const auto& [idx, val] : l->elements) {
                    result->elements[nextIdx++] = val;
                }
                
                // Copy right array elements in order
                for (const auto& [idx, val] : r->elements) {
                    result->elements[nextIdx++] = val;
                }
                
                lastValue = result;
                return;
            }
        }
        throw RuntimeError(e.loc, "Operands must be two numbers, two strings, or two arrays.");
    } else if (e.op == "-") {
        checkNumberOperands(e.loc, left, right);
        lastValue = std::make_shared<NumberValue>(dynamic_cast<NumberValue*>(left.get())->value - dynamic_cast<NumberValue*>(right.get())->value);
    } else if (e.op == "*") {
        checkNumberOperands(e.loc, left, right);
        lastValue = std::make_shared<NumberValue>(dynamic_cast<NumberValue*>(left.get())->value * dynamic_cast<NumberValue*>(right.get())->value);
    } else if (e.op == "/") {
        checkNumberOperands(e.loc, left, right);
        double r = dynamic_cast<NumberValue*>(right.get())->value;
        if (r == 0) throw RuntimeError(e.loc, "Division by zero.");
        lastValue = std::make_shared<NumberValue>(dynamic_cast<NumberValue*>(left.get())->value / r);
    } else if (e.op == ">") {
        checkNumberOperands(e.loc, left, right);
        lastValue = std::make_shared<BooleanValue>(dynamic_cast<NumberValue*>(left.get())->value > dynamic_cast<NumberValue*>(right.get())->value);
    } else if (e.op == ">=") {
        checkNumberOperands(e.loc, left, right);
        lastValue = std::make_shared<BooleanValue>(dynamic_cast<NumberValue*>(left.get())->value >= dynamic_cast<NumberValue*>(right.get())->value);
    } else if (e.op == "<") {
        checkNumberOperands(e.loc, left, right);
        lastValue = std::make_shared<BooleanValue>(dynamic_cast<NumberValue*>(left.get())->value < dynamic_cast<NumberValue*>(right.get())->value);
    } else if (e.op == "<=") {
        checkNumberOperands(e.loc, left, right);
        lastValue = std::make_shared<BooleanValue>(dynamic_cast<NumberValue*>(left.get())->value <= dynamic_cast<NumberValue*>(right.get())->value);
    } else if (e.op == "==" || e.op == "=") {
        lastValue = std::make_shared<BooleanValue>(isEqual(left, right));
    } else if (e.op == "!=" || e.op == "/=") {
        lastValue = std::make_shared<BooleanValue>(!isEqual(left, right));
    } else if (e.op == "and") {
        // Logical AND (без короткого замыкания, но с корректной логикой)
        lastValue = std::make_shared<BooleanValue>(isTruthy(left) && isTruthy(right));
    } else if (e.op == "or") {
        // Logical OR (без короткого замыкания, но с корректной логикой)
        lastValue = std::make_shared<BooleanValue>(isTruthy(left) || isTruthy(right));
    } else if (e.op == "xor") {
        lastValue = std::make_shared<BooleanValue>(isTruthy(left) != isTruthy(right));
    }
}

void Interpreter::visit(ArrayLiteral& e) {
    std::vector<std::shared_ptr<Value>> elements;
    for (auto& elem : e.elements) {
        elements.push_back(evaluate(elem));
    }
    lastValue = std::make_shared<ArrayValue>(elements);
}

void Interpreter::visit(TupleLiteral& e) {
    std::vector<std::shared_ptr<Value>> elements;
    std::vector<std::string> fieldNames;
    for (auto& f : e.fields) {
        elements.push_back(evaluate(f.value));
        fieldNames.push_back(f.name);
    }
    lastValue = std::make_shared<TupleValue>(elements, fieldNames);
}

void Interpreter::visit(IndexExpr& e) {
    auto obj = evaluate(e.array);
    auto idx = evaluate(e.index);

    if (auto arr = dynamic_cast<ArrayValue*>(obj.get())) {
        if (auto num = dynamic_cast<NumberValue*>(idx.get())) {
            long long i = (long long)num->value;
            // Arrays use 1-based indexing and support sparse indices
            if (i < 1) {
                throw RuntimeError(e.loc, "Array index must be positive.");
            }
            auto it = arr->elements.find(i);
            if (it != arr->elements.end()) {
                lastValue = it->second;
            } else {
                // Return none for uninitialized indices
                lastValue = std::make_shared<NoneValue>();
            }
            return;
        }
        throw RuntimeError(e.loc, "Array index must be a number.");
    }
    if (auto tup = dynamic_cast<TupleValue*>(obj.get())) {
        if (auto num = dynamic_cast<NumberValue*>(idx.get())) {
             int i = (int)num->value;
            // Tuples use 1-based indexing
            if (i < 1 || i > (int)tup->elements.size()) {
                throw RuntimeError(e.loc, "Tuple index out of bounds.");
            }
            lastValue = tup->elements[i - 1];  // Convert to 0-based for internal storage
            return;
        }
         throw RuntimeError(e.loc, "Tuple index must be a number.");
    }
    throw RuntimeError(e.loc, "Only arrays and tuples are indexable.");
}

void Interpreter::visit(CallExpr& e) {
    auto callee = evaluate(e.callee);

    std::vector<std::shared_ptr<Value>> args;
    for (auto& arg : e.args) {
        args.push_back(evaluate(arg));
    }

    if (auto fn = dynamic_cast<CallableValue*>(callee.get())) {
        if (args.size() != (size_t)fn->arity()) {
             throw RuntimeError(e.loc, "Expected " + std::to_string(fn->arity()) + " arguments but got " + std::to_string(args.size()) + ".");
        }
        lastValue = fn->call(*this, args);
    } else {
        throw RuntimeError(e.loc, "Can only call functions.");
    }
}

void Interpreter::visit(RangeExpr& e) {
    auto start = evaluate(e.start);
    auto end = evaluate(e.end);
    checkNumberOperands(e.loc, start, end);
    lastValue = std::make_shared<RangeValue>(
        dynamic_cast<NumberValue*>(start.get())->value,
        dynamic_cast<NumberValue*>(end.get())->value
    );
}

void Interpreter::visit(AssignExpr& e) {
    auto val = evaluate(e.value);
    environment->assign(e.name, val, e.loc);
    lastValue = val;
}

void Interpreter::visit(TypeExpr& e) {
    lastValue = std::make_shared<StringValue>(e.typeName);
}

void Interpreter::visit(IsExpr& e) {
    auto obj = evaluate(e.expr);
    std::string typeName = e.type->typeName; // e.type is TypeExpr
    
    bool match = false;
    if (typeName == "int" || typeName == "real") match = (obj->type() == "number");
    else if (typeName == "bool") match = (obj->type() == "boolean");
    else if (typeName == "string") match = (obj->type() == "string");
    else if (typeName == "none") match = (obj->type() == "none");
    else if (typeName == "func") match = (obj->type() == "function");
    else if (typeName == "[]") match = (obj->type() == "array");
    else if (typeName == "{}") match = (obj->type() == "tuple");
    else match = (obj->type() == typeName);

    lastValue = std::make_shared<BooleanValue>(match);
}

void Interpreter::visit(FieldAccessExpr& e) {
    auto obj = evaluate(e.object);
    if (auto tup = dynamic_cast<TupleValue*>(obj.get())) {
        // Try to access by field name first
        if (!tup->fieldNames.empty()) {
            for (size_t i = 0; i < tup->fieldNames.size(); ++i) {
                if (tup->fieldNames[i] == e.fieldName) {
                    lastValue = tup->elements[i];
                    return;
                }
            }
        }
        
        // Try to access by numeric index (1-based)
        try {
            int i = std::stoi(e.fieldName);
            if (i > 0 && i <= (int)tup->elements.size()) {
                lastValue = tup->elements[i-1]; // 1-based indexing
                return;
            } else {
                throw RuntimeError(e.loc, "Tuple index out of bounds.");
            }
        } catch (const std::invalid_argument&) {
            throw RuntimeError(e.loc, "Invalid field name: " + e.fieldName);
        } catch (const std::out_of_range&) {
            throw RuntimeError(e.loc, "Invalid field name: " + e.fieldName);
        }
    } else {
        throw RuntimeError(e.loc, "Only tuples have fields.");
    }
}

void Interpreter::visit(FunctionLiteral& e) {
    // Capture current environment
    auto fn = std::make_shared<FunctionValue>(std::make_shared<FunctionLiteral>(e), environment);
    lastValue = fn;
}

void Interpreter::visit(IfExpr& e) {
    if (isTruthy(evaluate(e.cond))) {
        lastValue = evaluate(e.thenExpr);
    } else if (e.elseExpr) {
        lastValue = evaluate(e.elseExpr);
    } else {
        lastValue = std::make_shared<NoneValue>();
    }
}

void Interpreter::visit(StatementList& s) {
    executeBlock(s.statements, std::make_shared<Environment>(environment));
}

void Interpreter::visit(VarDecl& s) {
    std::shared_ptr<Value> val;
    if (s.init) {
        val = evaluate(s.init);
    } else {
        val = std::make_shared<NoneValue>();
    }
    environment->define(s.name, val);
}

void Interpreter::visit(Assign& s) {
    auto val = evaluate(s.value);
    environment->assign(s.name, val, s.loc);
}

void Interpreter::visit(IfStmt& s) {
    if (isTruthy(evaluate(s.cond))) {
        execute(s.thenBranch);
    } else if (s.elseBranch) {
        execute(s.elseBranch);
    }
}

void Interpreter::visit(PrintStmt& s) {
    for (size_t i = 0; i < s.exprs.size(); ++i) {
        auto val = evaluate(s.exprs[i]);
        std::cout << val->toString();
        if (i < s.exprs.size() - 1) std::cout << " ";
    }
    std::cout << "\n";
}

void Interpreter::visit(AssertStmt& s) {
    if (!isTruthy(evaluate(s.condition))) {
        throw RuntimeError(s.loc, "Assertion failed.");
    }
}

void Interpreter::visit(WhileStmt& s) {
    try {
        while (isTruthy(evaluate(s.condition))) {
            execute(s.body);
        }
    } catch (const BreakException&) {
        // Stop loop
    }
}

void Interpreter::visit(ForStmt& s) {
    auto iterable = evaluate(s.iterable);
    
    std::vector<std::shared_ptr<Value>> items;
    
    if (auto arr = dynamic_cast<ArrayValue*>(iterable.get())) {
        // Extract values from sparse array map
        for (const auto& [idx, val] : arr->elements) {
            items.push_back(val);
        }
    } else if (auto tup = dynamic_cast<TupleValue*>(iterable.get())) {
        items = tup->elements;
    } else if (auto rng = dynamic_cast<RangeValue*>(iterable.get())) {
        // Range direction
        if (rng->start <= rng->end) {
            for (double i = rng->start; i <= rng->end; i++) {
                items.push_back(std::make_shared<NumberValue>(i));
            }
        } else {
            for (double i = rng->start; i >= rng->end; i--) {
                items.push_back(std::make_shared<NumberValue>(i));
            }
        }
    } else {
        throw RuntimeError(s.loc, "Object is not iterable.");
    }
    
    try {
        for (auto& item : items) {
            // Create new environment for loop variable? Or use current?
            // Semantic Analyzer says "loop variable is available in the loop body" and "savedVars" restored.
            // Usually loops introduce scope.
            auto loopEnv = std::make_shared<Environment>(environment);
            loopEnv->define(s.variable, item);
            executeBlock({s.body}, loopEnv);
        }
    } catch (const BreakException&) {
        // Stop loop
    }
}

void Interpreter::visit(LoopStmt& s) {
    try {
        while (true) {
            execute(s.body);
        }
    } catch (const BreakException&) {
        // Stop loop
    }
}

void Interpreter::visit(ExitStmt&) {
    throw BreakException();
}

void Interpreter::visit(ReturnStmt& s) {
    std::shared_ptr<Value> val = nullptr;
    if (s.value) val = evaluate(s.value);
    else val = std::make_shared<NoneValue>();
    
    throw ReturnException{val};
}

void Interpreter::visit(IndexedAssign& s) {
    // This handles: target[index] = value or target.field = value
    // s.target is an Expression (IndexExpr or FieldAccessExpr).
    
    // If target is IndexExpr (array[index] := value)
    if (auto idxExpr = dynamic_cast<IndexExpr*>(s.target.get())) {
        auto arrVal = evaluate(idxExpr->array);
        auto idxVal = evaluate(idxExpr->index);
        auto assignVal = evaluate(s.value);
        
        if (auto arr = dynamic_cast<ArrayValue*>(arrVal.get())) {
            if (auto num = dynamic_cast<NumberValue*>(idxVal.get())) {
                long long i = (long long)num->value;
                // Arrays use 1-based indexing and support sparse indices
                if (i < 1) throw RuntimeError(s.loc, "Array index must be positive.");
                arr->elements[i] = assignVal;  // Direct map insertion/update
                return;
            }
             throw RuntimeError(s.loc, "Index must be a number.");
        }
        throw RuntimeError(s.loc, "Only arrays are mutable via index.");
    }
    
    // If target is FieldAccessExpr (tuple.field := value)
    if (auto fieldExpr = dynamic_cast<FieldAccessExpr*>(s.target.get())) {
        auto tupleVal = evaluate(fieldExpr->object);
        auto assignVal = evaluate(s.value);
        
        if (auto tup = dynamic_cast<TupleValue*>(tupleVal.get())) {
            // Try to find field by name first
            if (!tup->fieldNames.empty()) {
                for (size_t i = 0; i < tup->fieldNames.size(); ++i) {
                    if (tup->fieldNames[i] == fieldExpr->fieldName) {
                        tup->elements[i] = assignVal;
                        return;
                    }
                }
            }
            
            // Try to access by numeric index (1-based)
            try {
                int i = std::stoi(fieldExpr->fieldName);
                if (i > 0 && i <= (int)tup->elements.size()) {
                    tup->elements[i-1] = assignVal; // 1-based indexing
                    return;
                } else {
                    throw RuntimeError(s.loc, "Tuple index out of bounds.");
                }
            } catch (const std::invalid_argument&) {
                throw RuntimeError(s.loc, "Invalid field name: " + fieldExpr->fieldName);
            } catch (const std::out_of_range&) {
                throw RuntimeError(s.loc, "Invalid field name: " + fieldExpr->fieldName);
            }
        }
        throw RuntimeError(s.loc, "Only tuples have fields.");
    }
    
    throw RuntimeError(s.loc, "Invalid assignment target.");
}

void Interpreter::visit(ExprStmt& s) {
    evaluate(s.expr);
}

} // namespace dli

