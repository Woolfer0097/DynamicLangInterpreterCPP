#pragma once

#include <memory>
#include <string>
#include <vector>
#include "ASTNode.hpp"
#include "Expression.hpp"

namespace dli {

struct Statement : ASTNode {};

struct StatementList : Statement {
    std::vector<std::shared_ptr<Statement>> statements;
    void push(std::shared_ptr<Statement> s) { statements.push_back(std::move(s)); }
    void accept(class ASTVisitor& v) override;
};

struct VarDecl : Statement {
    std::string name;
    std::shared_ptr<Expression> init;
    VarDecl(std::string n, std::shared_ptr<Expression> i)
        : name(std::move(n)), init(std::move(i)) {}
    void accept(class ASTVisitor& v) override;
};

struct Assign : Statement {
    std::string name;
    std::shared_ptr<Expression> value;
    Assign(std::string n, std::shared_ptr<Expression> v)
        : name(std::move(n)), value(std::move(v)) {}
    void accept(class ASTVisitor& v) override;
};

struct IfStmt : Statement {
    std::shared_ptr<Expression> cond;
    std::shared_ptr<Statement> thenBranch;
    std::shared_ptr<Statement> elseBranch; // may be nullptr
    IfStmt(std::shared_ptr<Expression> c,
           std::shared_ptr<Statement> t,
           std::shared_ptr<Statement> e)
        : cond(std::move(c)), thenBranch(std::move(t)), elseBranch(std::move(e)) {}
    void accept(class ASTVisitor& v) override;
};

struct PrintStmt : Statement {
    std::vector<std::shared_ptr<Expression>> exprs; // Множественные аргументы
    explicit PrintStmt(std::vector<std::shared_ptr<Expression>> e) : exprs(std::move(e)) {}
    void accept(class ASTVisitor& v) override;
};

struct AssertStmt : Statement {
    std::shared_ptr<Expression> condition;
    explicit AssertStmt(std::shared_ptr<Expression> c) : condition(std::move(c)) {}
    void accept(class ASTVisitor& v) override;
};

struct WhileStmt : Statement {
    std::shared_ptr<Expression> condition;
    std::shared_ptr<Statement> body;
    WhileStmt(std::shared_ptr<Expression> c, std::shared_ptr<Statement> b)
        : condition(std::move(c)), body(std::move(b)) {}
    void accept(class ASTVisitor& v) override;
};

struct ForStmt : Statement {
    std::string variable;
    std::shared_ptr<Expression> iterable;
    std::shared_ptr<Statement> body;
    ForStmt(std::string v, std::shared_ptr<Expression> i, std::shared_ptr<Statement> b)
        : variable(std::move(v)), iterable(std::move(i)), body(std::move(b)) {}
    void accept(class ASTVisitor& v) override;
};

struct LoopStmt : Statement {
    std::shared_ptr<Statement> body;
    explicit LoopStmt(std::shared_ptr<Statement> b) : body(std::move(b)) {}
    void accept(class ASTVisitor& v) override;
};

struct ExitStmt : Statement {
    ExitStmt() = default;
    void accept(class ASTVisitor& v) override;
};

struct ReturnStmt : Statement {
    std::shared_ptr<class Expression> value; // nullptr для return без значения
    ReturnStmt() = default;
    explicit ReturnStmt(std::shared_ptr<class Expression> v) : value(std::move(v)) {}
    void accept(class ASTVisitor& v) override;
};

struct IndexedAssign : Statement {
    std::shared_ptr<class Expression> target; // должен быть IndexExpr или FieldAccessExpr
    std::shared_ptr<class Expression> value;
    IndexedAssign(std::shared_ptr<class Expression> t, std::shared_ptr<class Expression> v)
        : target(std::move(t)), value(std::move(v)) {}
    void accept(class ASTVisitor& v) override;
};

struct ExprStmt : Statement {
    std::shared_ptr<class Expression> expr;
    explicit ExprStmt(std::shared_ptr<class Expression> e) : expr(std::move(e)) {}
    void accept(class ASTVisitor& v) override;
};

} // namespace dli


