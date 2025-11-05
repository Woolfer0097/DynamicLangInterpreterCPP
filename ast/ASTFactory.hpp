#pragma once

#include <memory>
#include <string>
#include "Expression.hpp"
#include "Statement.hpp"

namespace dli {

inline std::shared_ptr<StatementList> make_stmt_list() {
    return std::make_shared<StatementList>();
}

inline std::shared_ptr<StatementList> append_stmt(std::shared_ptr<StatementList> list,
                                                  std::shared_ptr<Statement> stmt) {
    // Flatten nested StatementList to avoid double StmtList in bodies
    if (auto nested = dynamic_cast<StatementList*>(stmt.get())) {
        for (auto& sub : nested->statements) {
            list->push(std::move(sub));
        }
    } else {
        list->push(std::move(stmt));
    }
    return list;
}

inline std::shared_ptr<Expression> make_binary(const std::string& op,
                                               std::shared_ptr<Expression> lhs,
                                               std::shared_ptr<Expression> rhs) {
    return std::make_shared<BinaryExpr>(op, std::move(lhs), std::move(rhs));
}

inline std::shared_ptr<Expression> make_unary(const std::string& op,
                                              std::shared_ptr<Expression> rhs) {
    return std::make_shared<UnaryExpr>(op, std::move(rhs));
}

inline std::shared_ptr<Expression> make_number(double v) {
    return std::make_shared<NumberExpr>(v);
}

inline std::shared_ptr<Expression> make_string(const std::string& s) {
    return std::make_shared<StringExpr>(s);
}

inline std::shared_ptr<Expression> make_boolean(bool v) {
    return std::make_shared<BooleanExpr>(v);
}

inline std::shared_ptr<Expression> make_none() {
    return std::make_shared<NoneExpr>();
}

inline std::shared_ptr<Expression> make_variable(const std::string& name) {
    return std::make_shared<VariableExpr>(name);
}

inline std::shared_ptr<Expression> make_array(std::vector<std::shared_ptr<Expression>> elements) {
    return std::make_shared<ArrayLiteral>(std::move(elements));
}

inline std::shared_ptr<Expression> make_tuple(std::vector<TupleField> fields) {
    return std::make_shared<TupleLiteral>(std::move(fields));
}

inline std::shared_ptr<Expression> make_field_access(std::shared_ptr<Expression> object, std::string field) {
    return std::make_shared<FieldAccessExpr>(std::move(object), std::move(field));
}

inline std::shared_ptr<Expression> make_index(std::shared_ptr<Expression> array, std::shared_ptr<Expression> index) {
    return std::make_shared<IndexExpr>(std::move(array), std::move(index));
}

inline std::shared_ptr<Expression> make_call(std::shared_ptr<Expression> callee, std::vector<std::shared_ptr<Expression>> args) {
    return std::make_shared<CallExpr>(std::move(callee), std::move(args));
}

inline std::shared_ptr<Expression> make_range(std::shared_ptr<Expression> start, std::shared_ptr<Expression> end) {
    return std::make_shared<RangeExpr>(std::move(start), std::move(end));
}

inline std::shared_ptr<TypeExpr> make_type(const std::string& typeName) {
    return std::make_shared<TypeExpr>(typeName);
}

inline std::shared_ptr<Expression> make_is(std::shared_ptr<Expression> expr, std::shared_ptr<TypeExpr> type) {
    return std::make_shared<IsExpr>(std::move(expr), std::move(type));
}

inline std::shared_ptr<Statement> make_var_decl(const std::string& name, std::shared_ptr<Expression> init) {
    return std::make_shared<VarDecl>(name, std::move(init));
}

inline std::shared_ptr<Statement> make_assignment(const std::string& name, std::shared_ptr<Expression> value) {
    return std::make_shared<Assign>(name, std::move(value));
}

inline std::shared_ptr<Statement> make_if(std::shared_ptr<Expression> cond,
                                          std::shared_ptr<Statement> thenSt,
                                          std::shared_ptr<Statement> elseSt) {
    return std::make_shared<IfStmt>(std::move(cond), std::move(thenSt), std::move(elseSt));
}

inline std::shared_ptr<Statement> make_print(std::vector<std::shared_ptr<Expression>> exprs) {
    return std::make_shared<PrintStmt>(std::move(exprs));
}

inline std::shared_ptr<Statement> make_assert(std::shared_ptr<Expression> c) {
    return std::make_shared<AssertStmt>(std::move(c));
}

inline std::shared_ptr<Statement> make_while(std::shared_ptr<Expression> cond, std::shared_ptr<Statement> body) {
    return std::make_shared<WhileStmt>(std::move(cond), std::move(body));
}

inline std::shared_ptr<Statement> make_for(const std::string& var, std::shared_ptr<Expression> iter, std::shared_ptr<Statement> body) {
    return std::make_shared<ForStmt>(var, std::move(iter), std::move(body));
}

inline std::shared_ptr<Statement> make_loop(std::shared_ptr<Statement> body) {
    return std::make_shared<LoopStmt>(std::move(body));
}

inline std::shared_ptr<Statement> make_exit() {
    return std::make_shared<ExitStmt>();
}

inline std::shared_ptr<Statement> make_return(std::shared_ptr<Expression> val = nullptr) {
    return std::make_shared<ReturnStmt>(std::move(val));
}

inline std::shared_ptr<Expression> make_function(std::vector<std::string> params, 
                                                  std::shared_ptr<Statement> body,
                                                  bool arrow = false) {
    return std::make_shared<FunctionLiteral>(std::move(params), std::move(body), arrow);
}

inline std::shared_ptr<Expression> make_assign_expr(const std::string& name, std::shared_ptr<Expression> value) {
    return std::make_shared<AssignExpr>(name, std::move(value));
}

inline std::shared_ptr<Statement> make_indexed_assign(std::shared_ptr<Expression> target,
                                                       std::shared_ptr<Expression> value) {
    return std::make_shared<IndexedAssign>(std::move(target), std::move(value));
}

inline std::shared_ptr<Statement> make_expr_stmt(std::shared_ptr<Expression> expr) {
    return std::make_shared<ExprStmt>(std::move(expr));
}

inline std::shared_ptr<Expression> make_if_expr(std::shared_ptr<Expression> cond,
                                                 std::shared_ptr<Expression> thenExpr,
                                                 std::shared_ptr<Expression> elseExpr) {
    return std::make_shared<IfExpr>(std::move(cond), std::move(thenExpr), std::move(elseExpr));
}

} // namespace dli


