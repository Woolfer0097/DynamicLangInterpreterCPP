#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <sstream>
#include <functional>

namespace dli {

// Forward declarations
struct Statement;
class Environment;
struct FunctionLiteral;

struct Value {
    virtual ~Value() = default;
    virtual std::string toString() const = 0;
    virtual std::string type() const = 0;
};

struct NumberValue : Value {
    double value;
    explicit NumberValue(double v) : value(v) {}
    std::string toString() const override {
        std::ostringstream oss;
        oss << value;
        return oss.str();
    }
    std::string type() const override { return "number"; }
};

struct StringValue : Value {
    std::string value;
    explicit StringValue(std::string v) : value(std::move(v)) {}
    std::string toString() const override { return value; } // Or quoted? usually print outputs raw
    std::string type() const override { return "string"; }
};

struct BooleanValue : Value {
    bool value;
    explicit BooleanValue(bool v) : value(v) {}
    std::string toString() const override { return value ? "true" : "false"; }
    std::string type() const override { return "boolean"; }
};

struct NoneValue : Value {
    std::string toString() const override { return "none"; }
    std::string type() const override { return "none"; }
};

struct ArrayValue : Value {
    // Using map for sparse array support (allows indices like 10, 100, 1000)
    std::map<long long, std::shared_ptr<Value>> elements;
    
    ArrayValue() = default;
    
    // Constructor from vector (for array literals)
    explicit ArrayValue(std::vector<std::shared_ptr<Value>> elems) {
        for (size_t i = 0; i < elems.size(); ++i) {
            elements[i + 1] = elems[i]; // 1-based indexing
        }
    }
    
    std::string toString() const override {
        if (elements.empty()) return "[]";
        
        std::string res = "[";
        bool first = true;
        for (const auto& [idx, val] : elements) {
            if (!first) res += ", ";
            res += val->toString();
            first = false;
        }
        res += "]";
        return res;
    }
    
    std::string type() const override { return "array"; }
};

struct TupleValue : Value {
    std::vector<std::shared_ptr<Value>> elements;
    std::vector<std::string> fieldNames; // Empty string for unnamed fields
    
    explicit TupleValue(std::vector<std::shared_ptr<Value>> elems, std::vector<std::string> names = {}) 
        : elements(std::move(elems)), fieldNames(std::move(names)) {}
    
    std::string toString() const override {
        std::string res = "{";
        for (size_t i = 0; i < elements.size(); ++i) {
            if (!fieldNames.empty() && i < fieldNames.size() && !fieldNames[i].empty()) {
                res += fieldNames[i] + " := ";
            }
            res += elements[i]->toString();
            if (i < elements.size() - 1) res += ", ";
        }
        res += "}";
        return res;
    }
    std::string type() const override { return "tuple"; }
};

struct RangeValue : Value {
    double start;
    double end;
    RangeValue(double s, double e) : start(s), end(e) {}
    std::string toString() const override {
        std::ostringstream oss;
        oss << start << " .. " << end;
        return oss.str();
    }
    std::string type() const override { return "range"; }
};

// Base for anything callable
struct CallableValue : Value {
    virtual int arity() = 0;
    virtual std::shared_ptr<Value> call(class Interpreter& interpreter, const std::vector<std::shared_ptr<Value>>& args) = 0;
    std::string type() const override { return "function"; }
};

struct FunctionValue : CallableValue {
    std::shared_ptr<FunctionLiteral> declaration;
    std::shared_ptr<Environment> closure;
    
    FunctionValue(std::shared_ptr<FunctionLiteral> decl, std::shared_ptr<Environment> clos)
        : declaration(std::move(decl)), closure(std::move(clos)) {}
        
    std::string toString() const override { return "<func>"; } // Maybe add name if available?
    
    int arity() override; // Implemented in cpp to avoid circular dep
    std::shared_ptr<Value> call(class Interpreter& interpreter, const std::vector<std::shared_ptr<Value>>& args) override;
};

struct BuiltinFunctionValue : CallableValue {
    using BuiltinFn = std::function<std::shared_ptr<Value>(class Interpreter&, const std::vector<std::shared_ptr<Value>>&)>;
    BuiltinFn function;
    int arityValue; // -1 for variadic?
    
    BuiltinFunctionValue(BuiltinFn fn, int a) : function(std::move(fn)), arityValue(a) {}
    
    std::string toString() const override { return "<native func>"; }
    
    int arity() override { return arityValue; }
    std::shared_ptr<Value> call(class Interpreter& interpreter, const std::vector<std::shared_ptr<Value>>& args) override {
        return function(interpreter, args);
    }
};

} // namespace dli

