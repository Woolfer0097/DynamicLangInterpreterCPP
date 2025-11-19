#pragma once

#include "../ast/Visitor.hpp"
#include "../ast/Expression.hpp"
#include "../ast/Statement.hpp"
#include "Environment.hpp"
#include "Value.hpp"
#include <vector>
#include <memory>

namespace dli {

class Interpreter : public ASTVisitor {
public:
    std::shared_ptr<Environment> globals;
    std::shared_ptr<Environment> environment;
    
private:
    std::shared_ptr<Value> lastValue; // Result of expression evaluation

public:
    Interpreter();

    void interpret(const std::vector<std::shared_ptr<Statement>>& statements);
    
    // Helper to evaluate an expression and get its value
    std::shared_ptr<Value> evaluate(Expression& expr);
    std::shared_ptr<Value> evaluate(const std::shared_ptr<Expression>& expr);
    
    // Helper to execute a statement
    void execute(Statement& stmt);
    void execute(const std::shared_ptr<Statement>& stmt);
    
    // For block execution (introduces new scope)
    void executeBlock(const std::vector<std::shared_ptr<Statement>>& statements, std::shared_ptr<Environment> env);

    // Visitor methods
    void visit(NumberExpr&) override;
    void visit(StringExpr&) override;
    void visit(BooleanExpr&) override;
    void visit(NoneExpr&) override;
    void visit(VariableExpr&) override;
    void visit(UnaryExpr&) override;
    void visit(BinaryExpr&) override;
    void visit(ArrayLiteral&) override;
    void visit(TupleLiteral&) override;
    void visit(IndexExpr&) override;
    void visit(CallExpr&) override;
    void visit(RangeExpr&) override;
    void visit(AssignExpr&) override;
    void visit(TypeExpr&) override;
    void visit(IsExpr&) override;
    void visit(FieldAccessExpr&) override;
    void visit(FunctionLiteral&) override;
    void visit(IfExpr&) override;

    void visit(StatementList&) override;
    void visit(VarDecl&) override;
    void visit(Assign&) override;
    void visit(IfStmt&) override;
    void visit(PrintStmt&) override;
    void visit(AssertStmt&) override;
    void visit(WhileStmt&) override;
    void visit(ForStmt&) override;
    void visit(LoopStmt&) override;
    void visit(ExitStmt&) override;
    void visit(ReturnStmt&) override;
    void visit(IndexedAssign&) override;
    void visit(ExprStmt&) override;

private:
    bool isTruthy(const std::shared_ptr<Value>& val);
    bool isEqual(const std::shared_ptr<Value>& left, const std::shared_ptr<Value>& right);
    void checkNumberOperand(const SourceLocation& loc, const std::shared_ptr<Value>& operand);
    void checkNumberOperands(const SourceLocation& loc, const std::shared_ptr<Value>& left, const std::shared_ptr<Value>& right);
};

} // namespace dli

