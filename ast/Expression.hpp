#pragma once

#include <memory>
#include <string>
#include <vector>
#include "ASTNode.hpp"

namespace dli {

struct Expression : ASTNode {};

struct NumberExpr : Expression {
    double value {0.0};
    explicit NumberExpr(double v) : value(v) {}
    void accept(class ASTVisitor& v) override;
};

struct StringExpr : Expression {
    std::string value;
    explicit StringExpr(std::string v) : value(std::move(v)) {}
    void accept(class ASTVisitor& v) override;
};

struct BooleanExpr : Expression {
    bool value {false};
    explicit BooleanExpr(bool v) : value(v) {}
    void accept(class ASTVisitor& v) override;
};

struct NoneExpr : Expression {
    NoneExpr() = default;
    void accept(class ASTVisitor& v) override;
};

struct VariableExpr : Expression {
    std::string name;
    explicit VariableExpr(std::string n) : name(std::move(n)) {}
    void accept(class ASTVisitor& v) override;
};

struct UnaryExpr : Expression {
    std::string op;
    std::shared_ptr<Expression> rhs;
    UnaryExpr(std::string o, std::shared_ptr<Expression> r)
        : op(std::move(o)), rhs(std::move(r)) {}
    void accept(class ASTVisitor& v) override;
};

struct BinaryExpr : Expression {
    std::string op;
    std::shared_ptr<Expression> lhs;
    std::shared_ptr<Expression> rhs;
    BinaryExpr(std::string o, std::shared_ptr<Expression> l, std::shared_ptr<Expression> r)
        : op(std::move(o)), lhs(std::move(l)), rhs(std::move(r)) {}
    void accept(class ASTVisitor& v) override;
};

struct ArrayLiteral : Expression {
    std::vector<std::shared_ptr<Expression>> elements;
    ArrayLiteral() = default;
    explicit ArrayLiteral(std::vector<std::shared_ptr<Expression>> elems)
        : elements(std::move(elems)) {}
    void accept(class ASTVisitor& v) override;
};

struct TupleField {
    std::string name; // Пустая строка для безымянных полей
    std::shared_ptr<Expression> value;
    TupleField() = default;
    TupleField(std::string n, std::shared_ptr<Expression> v) 
        : name(std::move(n)), value(std::move(v)) {}
};

struct TupleLiteral : Expression {
    std::vector<TupleField> fields;
    TupleLiteral() = default;
    explicit TupleLiteral(std::vector<TupleField> f) : fields(std::move(f)) {}
    void accept(class ASTVisitor& v) override;
};

struct IndexExpr : Expression {
    std::shared_ptr<Expression> array;
    std::shared_ptr<Expression> index;
    IndexExpr(std::shared_ptr<Expression> arr, std::shared_ptr<Expression> idx)
        : array(std::move(arr)), index(std::move(idx)) {}
    void accept(class ASTVisitor& v) override;
};

struct CallExpr : Expression {
    std::shared_ptr<Expression> callee;
    std::vector<std::shared_ptr<Expression>> args;
    CallExpr(std::shared_ptr<Expression> c, std::vector<std::shared_ptr<Expression>> a)
        : callee(std::move(c)), args(std::move(a)) {}
    void accept(class ASTVisitor& v) override;
};

struct RangeExpr : Expression {
    std::shared_ptr<Expression> start;
    std::shared_ptr<Expression> end;
    RangeExpr(std::shared_ptr<Expression> s, std::shared_ptr<Expression> e)
        : start(std::move(s)), end(std::move(e)) {}
    void accept(class ASTVisitor& v) override;
};

struct TypeExpr : Expression {
    std::string typeName; // "int", "real", "bool", "string", "none", "func", "[]", "{}"
    explicit TypeExpr(std::string t) : typeName(std::move(t)) {}
    void accept(class ASTVisitor& v) override;
};

struct IsExpr : Expression {
    std::shared_ptr<Expression> expr;
    std::shared_ptr<TypeExpr> type;
    IsExpr(std::shared_ptr<Expression> e, std::shared_ptr<TypeExpr> t)
        : expr(std::move(e)), type(std::move(t)) {}
    void accept(class ASTVisitor& v) override;
};

struct FieldAccessExpr : Expression {
    std::shared_ptr<Expression> object;
    std::string fieldName; // Имя поля или число как строка "1", "2"
    FieldAccessExpr(std::shared_ptr<Expression> obj, std::string field)
        : object(std::move(obj)), fieldName(std::move(field)) {}
    void accept(class ASTVisitor& v) override;
};

struct FunctionLiteral : Expression {
    std::vector<std::string> params;
    std::shared_ptr<class Statement> body; // Может быть StatementList или одно выражение
    bool isArrow {false}; // true для func => expr
    FunctionLiteral(std::vector<std::string> p, std::shared_ptr<class Statement> b, bool arrow = false)
        : params(std::move(p)), body(std::move(b)), isArrow(arrow) {}
    void accept(class ASTVisitor& v) override;
};

struct AssignExpr : Expression {
    std::string name;
    std::shared_ptr<Expression> value;
    AssignExpr(std::string n, std::shared_ptr<Expression> v)
        : name(std::move(n)), value(std::move(v)) {}
    void accept(class ASTVisitor& v) override;
};

struct IfExpr : Expression {
    std::shared_ptr<Expression> cond;
    std::shared_ptr<Expression> thenExpr;
    std::shared_ptr<Expression> elseExpr; // может быть nullptr
    IfExpr(std::shared_ptr<Expression> c, std::shared_ptr<Expression> t, std::shared_ptr<Expression> e)
        : cond(std::move(c)), thenExpr(std::move(t)), elseExpr(std::move(e)) {}
    void accept(class ASTVisitor& v) override;
};

} // namespace dli


