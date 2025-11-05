#pragma once

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <memory>
#include <iostream>
#include "Visitor.hpp"
#include "Expression.hpp"
#include "Statement.hpp"
#include "ASTFactory.hpp"

namespace dli {

// SemanticChecker: проверки, которые НЕ модифицируют AST
struct SemanticChecker : ASTVisitor {
    std::vector<std::string> errors;
    bool inLoop {false};
    bool inFunction {false};
    std::unordered_set<std::string> declaredVars;
    std::unordered_map<std::string, std::shared_ptr<FunctionLiteral>> declaredFuncs;

    void reportError(const std::string& msg, const SourceLocation& loc) {
        errors.push_back("Error at " + std::to_string(loc.firstLine) + 
                        ":" + std::to_string(loc.firstColumn) + ": " + msg);
    }

    // Expressions
    void visit(NumberExpr&) override {}
    void visit(StringExpr&) override {}
    void visit(BooleanExpr&) override {}
    void visit(NoneExpr&) override {}

    void visit(VariableExpr& e) override {
        // True, False, None - это встроенные константы
        if (e.name == "True" || e.name == "False" || e.name == "None") {
            return;
        }
        
        if (declaredVars.find(e.name) == declaredVars.end() &&
            declaredFuncs.find(e.name) == declaredFuncs.end()) {
            reportError("Variable '" + e.name + "' is used before declaration", e.loc);
        }
    }

    void visit(UnaryExpr& e) override {
        e.rhs->accept(*this);
    }

    void visit(BinaryExpr& e) override {
        e.lhs->accept(*this);
        e.rhs->accept(*this);
    }

    void visit(ArrayLiteral& e) override {
        for (auto& elem : e.elements) {
            elem->accept(*this);
        }
    }

    void visit(TupleLiteral& e) override {
        for (auto& f : e.fields) {
            f.value->accept(*this);
        }
    }

    void visit(IndexExpr& e) override {
        e.array->accept(*this);
        e.index->accept(*this);
    }

    void visit(CallExpr& e) override {
        e.callee->accept(*this);
        for (auto& arg : e.args) {
            arg->accept(*this);
        }
    }

    void visit(RangeExpr& e) override {
        e.start->accept(*this);
        e.end->accept(*this);
    }

    void visit(AssignExpr& e) override {
        e.value->accept(*this);
    }

    void visit(TypeExpr&) override {}
    void visit(IsExpr& e) override {
        e.expr->accept(*this);
    }

    void visit(FieldAccessExpr& e) override {
        e.object->accept(*this);
    }

    void visit(FunctionLiteral& e) override {
        bool wasInFunction = inFunction;
        inFunction = true;
        
        std::unordered_set<std::string> savedVars = declaredVars;
        // Параметры функции доступны в теле функции
        for (const auto& param : e.params) {
            declaredVars.insert(param);
        }
        
        e.body->accept(*this);
        
        declaredVars = savedVars;
        inFunction = wasInFunction;
    }

    void visit(IfExpr& e) override {
        e.cond->accept(*this);
        e.thenExpr->accept(*this);
        if (e.elseExpr) {
            e.elseExpr->accept(*this);
        }
    }

    // Statements
    void visit(StatementList& s) override {
        for (auto& stmt : s.statements) {
            stmt->accept(*this);
        }
    }

    void visit(VarDecl& s) override {
        if (s.init) {
            s.init->accept(*this);
        }
        declaredVars.insert(s.name);
    }

    void visit(Assign& s) override {
        s.value->accept(*this);
        if (declaredVars.find(s.name) == declaredVars.end() &&
            declaredFuncs.find(s.name) == declaredFuncs.end()) {
            reportError("Variable '" + s.name + "' is assigned before declaration", s.loc);
        }
    }

    void visit(IfStmt& s) override {
        s.cond->accept(*this);
        s.thenBranch->accept(*this);
        if (s.elseBranch) {
            s.elseBranch->accept(*this);
        }
    }

    void visit(PrintStmt& s) override {
        for (auto& e : s.exprs) {
            e->accept(*this);
        }
    }

    void visit(AssertStmt& s) override {
        s.condition->accept(*this);
    }

    void visit(WhileStmt& s) override {
        s.condition->accept(*this);
        bool wasInLoop = inLoop;
        inLoop = true;
        s.body->accept(*this);
        inLoop = wasInLoop;
    }

    void visit(ForStmt& s) override {
        s.iterable->accept(*this);
        bool wasInLoop = inLoop;
        inLoop = true;
        std::unordered_set<std::string> savedVars = declaredVars;
        declaredVars.insert(s.variable); // переменная цикла доступна в теле
        s.body->accept(*this);
        declaredVars = savedVars;
        inLoop = wasInLoop;
    }

    void visit(LoopStmt& s) override {
        bool wasInLoop = inLoop;
        inLoop = true;
        s.body->accept(*this);
        inLoop = wasInLoop;
    }

    void visit(ExitStmt& s) override {
        if (!inLoop) {
            reportError("'exit' statement can only be used inside loops", s.loc);
        }
    }

    void visit(ReturnStmt& s) override {
        if (!inFunction) {
            reportError("'return' statement can only be used inside functions", s.loc);
        }
        if (s.value) {
            s.value->accept(*this);
        }
    }

    void visit(IndexedAssign& s) override {
        s.target->accept(*this);
        s.value->accept(*this);
    }

    void visit(ExprStmt& s) override {
        s.expr->accept(*this);
    }
};

// SemanticOptimizer: оптимизации, которые МОДИФИЦИРУЮТ AST
struct SemanticOptimizer : ASTVisitor {
    bool modified {false};
    std::shared_ptr<Expression> optimizedExpr {nullptr};
    std::shared_ptr<Statement> optimizedStmt {nullptr};

    // Вспомогательная функция для вычисления константных выражений
    std::shared_ptr<Expression> evaluateConstant(BinaryExpr& e) {
        auto lhs = dynamic_cast<NumberExpr*>(e.lhs.get());
        auto rhs = dynamic_cast<NumberExpr*>(e.rhs.get());
        
        if (lhs && rhs) {
            if (e.op == "+") {
                return make_number(lhs->value + rhs->value);
            } else if (e.op == "-") {
                return make_number(lhs->value - rhs->value);
            } else if (e.op == "*") {
                return make_number(lhs->value * rhs->value);
            } else if (e.op == "/" && rhs->value != 0) {
                return make_number(lhs->value / rhs->value);
            } else if (e.op == "<") {
                return make_boolean(lhs->value < rhs->value);
            } else if (e.op == "<=") {
                return make_boolean(lhs->value <= rhs->value);
            } else if (e.op == ">") {
                return make_boolean(lhs->value > rhs->value);
            } else if (e.op == ">=") {
                return make_boolean(lhs->value >= rhs->value);
            } else if (e.op == "==" || e.op == "=") {
                return make_boolean(lhs->value == rhs->value);
            } else if (e.op == "!=" || e.op == "/=") {
                return make_boolean(lhs->value != rhs->value);
            }
        }
        
        auto lhsBool = dynamic_cast<BooleanExpr*>(e.lhs.get());
        auto rhsBool = dynamic_cast<BooleanExpr*>(e.rhs.get());
        
        if (lhsBool && rhsBool) {
            if (e.op == "and") {
                return make_boolean(lhsBool->value && rhsBool->value);
            } else if (e.op == "or") {
                return make_boolean(lhsBool->value || rhsBool->value);
            } else if (e.op == "xor") {
                return make_boolean(lhsBool->value != rhsBool->value);
            } else if (e.op == "==" || e.op == "=") {
                return make_boolean(lhsBool->value == rhsBool->value);
            } else if (e.op == "!=" || e.op == "/=") {
                return make_boolean(lhsBool->value != rhsBool->value);
            }
        }
        
        return nullptr;
    }

    std::shared_ptr<Expression> optimizeExpr(std::shared_ptr<Expression> expr) {
        if (!expr) return expr;
        expr->accept(*this);
        return expr;
    }

    std::shared_ptr<Statement> optimizeStmt(std::shared_ptr<Statement> stmt) {
        if (!stmt) return stmt;
        stmt->accept(*this);
        return stmt;
    }

    // Expressions
    void visit(NumberExpr&) override {}
    void visit(StringExpr&) override {}
    void visit(BooleanExpr&) override {}
    void visit(NoneExpr&) override {}
    void visit(VariableExpr&) override {}
    void visit(TypeExpr&) override {}

    void visit(UnaryExpr& e) override {
        e.rhs->accept(*this);
        if (optimizedExpr) {
            e.rhs = optimizedExpr;
            optimizedExpr = nullptr;
        }
        
        // Оптимизация: -(-x) -> x, !(!x) -> x (если нужно)
        if (auto nested = dynamic_cast<UnaryExpr*>(e.rhs.get())) {
            if (e.op == nested->op && (e.op == "-" || e.op == "!" || e.op == "not")) {
                optimizedExpr = nested->rhs;
                modified = true;
            }
        }
    }

    void visit(BinaryExpr& e) override {
        e.lhs->accept(*this);
        if (optimizedExpr) {
            e.lhs = optimizedExpr;
            optimizedExpr = nullptr;
        }
        
        e.rhs->accept(*this);
        if (optimizedExpr) {
            e.rhs = optimizedExpr;
            optimizedExpr = nullptr;
        }
        
        // Оптимизация: упрощение константных выражений
        auto constant = evaluateConstant(e);
        if (constant) {
            optimizedExpr = constant;
            modified = true;
        }
    }

    void visit(ArrayLiteral& e) override {
        for (auto& elem : e.elements) {
            elem->accept(*this);
            if (optimizedExpr) {
                elem = optimizedExpr;
                optimizedExpr = nullptr;
            }
        }
    }

    void visit(TupleLiteral& e) override {
        for (auto& f : e.fields) {
            f.value->accept(*this);
            if (optimizedExpr) {
                f.value = optimizedExpr;
                optimizedExpr = nullptr;
            }
        }
    }

    void visit(IndexExpr& e) override {
        e.array->accept(*this);
        if (optimizedExpr) {
            e.array = optimizedExpr;
            optimizedExpr = nullptr;
        }
        
        e.index->accept(*this);
        if (optimizedExpr) {
            e.index = optimizedExpr;
            optimizedExpr = nullptr;
        }
    }

    void visit(CallExpr& e) override {
        e.callee->accept(*this);
        if (optimizedExpr) {
            e.callee = optimizedExpr;
            optimizedExpr = nullptr;
        }
        
        for (auto& arg : e.args) {
            arg->accept(*this);
            if (optimizedExpr) {
                arg = optimizedExpr;
                optimizedExpr = nullptr;
            }
        }
    }

    void visit(RangeExpr& e) override {
        e.start->accept(*this);
        if (optimizedExpr) {
            e.start = optimizedExpr;
            optimizedExpr = nullptr;
        }
        
        e.end->accept(*this);
        if (optimizedExpr) {
            e.end = optimizedExpr;
            optimizedExpr = nullptr;
        }
    }

    void visit(AssignExpr& e) override {
        e.value->accept(*this);
        if (optimizedExpr) {
            e.value = optimizedExpr;
            optimizedExpr = nullptr;
        }
    }

    void visit(IsExpr& e) override {
        e.expr->accept(*this);
        if (optimizedExpr) {
            e.expr = optimizedExpr;
            optimizedExpr = nullptr;
        }
    }

    void visit(FieldAccessExpr& e) override {
        e.object->accept(*this);
        if (optimizedExpr) {
            e.object = optimizedExpr;
            optimizedExpr = nullptr;
        }
    }

    void visit(FunctionLiteral& e) override {
        e.body->accept(*this);
        if (optimizedStmt) {
            e.body = optimizedStmt;
            optimizedStmt = nullptr;
        }
    }

    void visit(IfExpr& e) override {
        e.cond->accept(*this);
        if (optimizedExpr) {
            e.cond = optimizedExpr;
            optimizedExpr = nullptr;
        }
        
        e.thenExpr->accept(*this);
        if (optimizedExpr) {
            e.thenExpr = optimizedExpr;
            optimizedExpr = nullptr;
        }
        
        if (e.elseExpr) {
            e.elseExpr->accept(*this);
            if (optimizedExpr) {
                e.elseExpr = optimizedExpr;
                optimizedExpr = nullptr;
            }
        }
        
        // Проверяем, является ли условие булевой константой
        bool isTrue = false;
        bool isFalse = false;
        
        auto condBool = dynamic_cast<BooleanExpr*>(e.cond.get());
        if (condBool) {
            isTrue = condBool->value;
            isFalse = !condBool->value;
        } else if (auto varExpr = dynamic_cast<VariableExpr*>(e.cond.get())) {
            if (varExpr->name == "True") {
                isTrue = true;
            } else if (varExpr->name == "False") {
                isFalse = true;
            }
        }
        
        // Оптимизация: if True then X else Y -> X
        if (isTrue) {
            optimizedExpr = e.thenExpr;
            modified = true;
        } else if (isFalse && e.elseExpr) {
            optimizedExpr = e.elseExpr;
            modified = true;
        }
    }

    // Statements
    void visit(StatementList& s) override {
        std::vector<std::shared_ptr<Statement>> newStatements;
        bool foundReturn = false;
        bool listModified = false;
        
        for (auto& stmt : s.statements) {
            if (foundReturn) {
                // Удаляем недоступный код после return
                listModified = true;
                modified = true;
                continue;
            }
            
            stmt->accept(*this);
            
            // Заменяем утверждение на оптимизированное, если есть
            // Для IfStmt может быть замена на thenBranch или elseBranch
            if (optimizedStmt) {
                // Если IfStmt был заменен на StatementList, разворачиваем его
                if (auto list = dynamic_cast<StatementList*>(optimizedStmt.get())) {
                    for (auto& substmt : list->statements) {
                        newStatements.push_back(substmt);
                    }
                    listModified = true;
                } else {
                    stmt = optimizedStmt;
                    listModified = true;
                }
                optimizedStmt = nullptr;
            } else {
                newStatements.push_back(stmt);
            }
            
            // Проверяем, является ли это return
            if (dynamic_cast<ReturnStmt*>(stmt.get())) {
                foundReturn = true;
            }
        }
        
        if (listModified) {
            s.statements = std::move(newStatements);
        }
    }

    void visit(VarDecl& s) override {
        if (s.init) {
            s.init->accept(*this);
            if (optimizedExpr) {
                s.init = optimizedExpr;
                optimizedExpr = nullptr;
            }
        }
    }

    void visit(Assign& s) override {
        s.value->accept(*this);
        if (optimizedExpr) {
            s.value = optimizedExpr;
            optimizedExpr = nullptr;
        }
    }

    void visit(IfStmt& s) override {
        s.cond->accept(*this);
        if (optimizedExpr) {
            s.cond = optimizedExpr;
            optimizedExpr = nullptr;
        }
        
        // Проверяем, является ли условие булевой константой
        bool isTrue = false;
        bool isFalse = false;
        
        auto condBool = dynamic_cast<BooleanExpr*>(s.cond.get());
        if (condBool) {
            isTrue = condBool->value;
            isFalse = !condBool->value;
        } else if (auto varExpr = dynamic_cast<VariableExpr*>(s.cond.get())) {
            // Обрабатываем True/False как переменные (если парсер так их распознает)
            if (varExpr->name == "True") {
                isTrue = true;
            } else if (varExpr->name == "False") {
                isFalse = true;
            }
        }
        
        // Оптимизация: if True then X else Y -> X
        if (isTrue) {
            s.thenBranch->accept(*this);
            // Если thenBranch - это StatementList, используем его напрямую
            if (dynamic_cast<StatementList*>(s.thenBranch.get())) {
                optimizedStmt = s.thenBranch;
            } else {
                // Оборачиваем в StatementList
                auto newList = make_stmt_list();
                newList->push(s.thenBranch);
                optimizedStmt = newList;
            }
            modified = true;
        } 
        // Оптимизация: if False then X else Y -> Y (или удалить)
        else if (isFalse) {
            if (s.elseBranch) {
                s.elseBranch->accept(*this);
                if (dynamic_cast<StatementList*>(s.elseBranch.get())) {
                    optimizedStmt = s.elseBranch;
                } else {
                    auto newList = make_stmt_list();
                    newList->push(s.elseBranch);
                    optimizedStmt = newList;
                }
                modified = true;
            } else {
                // Удаляем весь if (заменяем на пустой StatementList)
                optimizedStmt = make_stmt_list();
                modified = true;
            }
        } else {
            s.thenBranch->accept(*this);
            if (optimizedStmt) {
                s.thenBranch = optimizedStmt;
                optimizedStmt = nullptr;
            }
            
            if (s.elseBranch) {
                s.elseBranch->accept(*this);
                if (optimizedStmt) {
                    s.elseBranch = optimizedStmt;
                    optimizedStmt = nullptr;
                }
            }
        }
    }

    void visit(PrintStmt& s) override {
        for (auto& e : s.exprs) {
            e->accept(*this);
            if (optimizedExpr) {
                e = optimizedExpr;
                optimizedExpr = nullptr;
            }
        }
    }

    void visit(AssertStmt& s) override {
        s.condition->accept(*this);
        if (optimizedExpr) {
            s.condition = optimizedExpr;
            optimizedExpr = nullptr;
        }
    }

    void visit(WhileStmt& s) override {
        s.condition->accept(*this);
        if (optimizedExpr) {
            s.condition = optimizedExpr;
            optimizedExpr = nullptr;
        }
        
        // Оптимизация: while False -> удалить тело
        auto condBool = dynamic_cast<BooleanExpr*>(s.condition.get());
        if (condBool && !condBool->value) {
            // Заменяем на пустой StatementList
            s.body = make_stmt_list();
            modified = true;
            return;
        }
        
        s.body->accept(*this);
        if (optimizedStmt) {
            s.body = optimizedStmt;
            optimizedStmt = nullptr;
        }
    }

    void visit(ForStmt& s) override {
        s.iterable->accept(*this);
        if (optimizedExpr) {
            s.iterable = optimizedExpr;
            optimizedExpr = nullptr;
        }
        
        s.body->accept(*this);
        if (optimizedStmt) {
            s.body = optimizedStmt;
            optimizedStmt = nullptr;
        }
    }

    void visit(LoopStmt& s) override {
        s.body->accept(*this);
        if (optimizedStmt) {
            s.body = optimizedStmt;
            optimizedStmt = nullptr;
        }
    }

    void visit(ExitStmt&) override {}
    
    void visit(ReturnStmt& s) override {
        if (s.value) {
            s.value->accept(*this);
            if (optimizedExpr) {
                s.value = optimizedExpr;
                optimizedExpr = nullptr;
            }
        }
    }

    void visit(IndexedAssign& s) override {
        s.target->accept(*this);
        if (optimizedExpr) {
            s.target = optimizedExpr;
            optimizedExpr = nullptr;
        }
        
        s.value->accept(*this);
        if (optimizedExpr) {
            s.value = optimizedExpr;
            optimizedExpr = nullptr;
        }
    }

    void visit(ExprStmt& s) override {
        s.expr->accept(*this);
        if (optimizedExpr) {
            s.expr = optimizedExpr;
            optimizedExpr = nullptr;
        }
    }
};

} // namespace dli

