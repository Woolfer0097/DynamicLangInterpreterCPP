#include "Expression.hpp"
#include "Statement.hpp"
#include "Visitor.hpp"

namespace dli {

void NumberExpr::accept(ASTVisitor& v) { v.visit(*this); }
void StringExpr::accept(ASTVisitor& v) { v.visit(*this); }
void BooleanExpr::accept(ASTVisitor& v) { v.visit(*this); }
void NoneExpr::accept(ASTVisitor& v) { v.visit(*this); }
void VariableExpr::accept(ASTVisitor& v) { v.visit(*this); }
void UnaryExpr::accept(ASTVisitor& v) { v.visit(*this); }
void BinaryExpr::accept(ASTVisitor& v) { v.visit(*this); }
void ArrayLiteral::accept(ASTVisitor& v) { v.visit(*this); }
void TupleLiteral::accept(ASTVisitor& v) { v.visit(*this); }
void IndexExpr::accept(ASTVisitor& v) { v.visit(*this); }
void CallExpr::accept(ASTVisitor& v) { v.visit(*this); }
void RangeExpr::accept(ASTVisitor& v) { v.visit(*this); }
void AssignExpr::accept(ASTVisitor& v) { v.visit(*this); }
void TypeExpr::accept(ASTVisitor& v) { v.visit(*this); }
void IsExpr::accept(ASTVisitor& v) { v.visit(*this); }
void FieldAccessExpr::accept(ASTVisitor& v) { v.visit(*this); }
void FunctionLiteral::accept(ASTVisitor& v) { v.visit(*this); }
void IfExpr::accept(ASTVisitor& v) { v.visit(*this); }

void StatementList::accept(ASTVisitor& v) { v.visit(*this); }
void VarDecl::accept(ASTVisitor& v) { v.visit(*this); }
void Assign::accept(ASTVisitor& v) { v.visit(*this); }
void IfStmt::accept(ASTVisitor& v) { v.visit(*this); }
void PrintStmt::accept(ASTVisitor& v) { v.visit(*this); }
void AssertStmt::accept(ASTVisitor& v) { v.visit(*this); }
void WhileStmt::accept(ASTVisitor& v) { v.visit(*this); }
void ForStmt::accept(ASTVisitor& v) { v.visit(*this); }
void LoopStmt::accept(ASTVisitor& v) { v.visit(*this); }
void ExitStmt::accept(ASTVisitor& v) { v.visit(*this); }
void ReturnStmt::accept(ASTVisitor& v) { v.visit(*this); }
void IndexedAssign::accept(ASTVisitor& v) { v.visit(*this); }
void ExprStmt::accept(ASTVisitor& v) { v.visit(*this); }

} // namespace dli


