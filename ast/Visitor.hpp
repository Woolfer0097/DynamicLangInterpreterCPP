#pragma once

namespace dli {

struct NumberExpr; struct StringExpr; struct VariableExpr;
struct BooleanExpr; struct NoneExpr;
struct UnaryExpr; struct BinaryExpr;
struct ArrayLiteral; struct TupleLiteral; struct IndexExpr; struct CallExpr; struct RangeExpr; struct AssignExpr;
struct TypeExpr; struct IsExpr; struct FieldAccessExpr; struct FunctionLiteral; struct IfExpr;
struct StatementList; struct VarDecl; struct Assign; struct IfStmt; struct PrintStmt; struct AssertStmt;
struct WhileStmt; struct ForStmt; struct LoopStmt; struct ExitStmt; struct ReturnStmt;
struct IndexedAssign; struct ExprStmt;

struct ASTVisitor {
    virtual ~ASTVisitor() = default;
    virtual void visit(NumberExpr&) = 0;
    virtual void visit(StringExpr&) = 0;
    virtual void visit(BooleanExpr&) = 0;
    virtual void visit(NoneExpr&) = 0;
    virtual void visit(VariableExpr&) = 0;
    virtual void visit(UnaryExpr&) = 0;
    virtual void visit(BinaryExpr&) = 0;
    virtual void visit(ArrayLiteral&) = 0;
    virtual void visit(TupleLiteral&) = 0;
    virtual void visit(IndexExpr&) = 0;
    virtual void visit(CallExpr&) = 0;
    virtual void visit(RangeExpr&) = 0;
    virtual void visit(AssignExpr&) = 0;
    virtual void visit(TypeExpr&) = 0;
    virtual void visit(IsExpr&) = 0;
    virtual void visit(FieldAccessExpr&) = 0;
    virtual void visit(FunctionLiteral&) = 0;
    virtual void visit(IfExpr&) = 0;
    virtual void visit(StatementList&) = 0;
    virtual void visit(VarDecl&) = 0;
    virtual void visit(Assign&) = 0;
    virtual void visit(IfStmt&) = 0;
    virtual void visit(PrintStmt&) = 0;
    virtual void visit(AssertStmt&) = 0;
    virtual void visit(WhileStmt&) = 0;
    virtual void visit(ForStmt&) = 0;
    virtual void visit(LoopStmt&) = 0;
    virtual void visit(ExitStmt&) = 0;
    virtual void visit(ReturnStmt&) = 0;
    virtual void visit(IndexedAssign&) = 0;
    virtual void visit(ExprStmt&) = 0;
};

} // namespace dli


