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

// SemanticChecker: checks that do NOT modify the AST
struct SemanticChecker : ASTVisitor {
    std::vector<std::string> errors;
    bool inLoop {false};
    bool inFunction {false};
    std::unordered_set<std::string> declaredVars;
    std::unordered_map<std::string, std::shared_ptr<FunctionLiteral>> declaredFuncs;
    std::unordered_map<std::string, std::size_t> arrayLiteralSizes; // track known array literal sizes by variable name

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
        // True, False, None are built-in constants
        if (e.name == "True" || e.name == "False" || e.name == "None") {
            return;
        }
        // Treat 'break' specially: if used outside loops, report; never treat as a variable
        if (e.name == "break") {
            if (!inLoop) {
                reportError("'break' statement can only be used inside loops", e.loc);
            }
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
        // Basic validation for array indices
        if (auto idxNum = dynamic_cast<NumberExpr*>(e.index.get())) {
            double d = idxNum->value;
            long long i = static_cast<long long>(d);
            // Check for non-integral or non-positive indices
            if (static_cast<double>(i) != d) {
                SourceLocation loc = e.loc;
                if (loc.firstLine == 1 && loc.firstColumn == 1 && e.index) loc = e.index->loc;
                reportError("Array index must be an integer", loc);
            } else if (i < 1) {
                SourceLocation loc = e.loc;
                if (loc.firstLine == 1 && loc.firstColumn == 1 && e.index) loc = e.index->loc;
                reportError("Array index must be positive (1-based indexing)", loc);
            }
            // Note: No upper bound check - arrays are dynamic and support sparse indices
        }
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
        // Function parameters are available in the function body
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
        // For recursive functions, declare the variable name before processing the function body
        if (s.init && dynamic_cast<FunctionLiteral*>(s.init.get())) {
            declaredVars.insert(s.name);
        }
        
        if (s.init) {
            if (auto fn = dynamic_cast<FunctionLiteral*>(s.init.get())) {
                bool wasInFunction = inFunction;
                inFunction = true;

                std::unordered_set<std::string> savedVars = declaredVars;
                for (const auto& param : fn->params) {
                    declaredVars.insert(param);
                }

                if (fn->body) {
                    fn->body->accept(*this);
                }

                declaredVars = savedVars;
                // Restore the function name declaration
                declaredVars.insert(s.name);
                inFunction = wasInFunction;
            } else {
                s.init->accept(*this);
            }
        }
        declaredVars.insert(s.name);
        // Track functions assigned at declaration
        if (s.init) {
            if (auto fn = std::dynamic_pointer_cast<FunctionLiteral>(s.init)) {
                declaredFuncs[s.name] = fn;
            }
            if (auto arr = std::dynamic_pointer_cast<ArrayLiteral>(s.init)) {
                arrayLiteralSizes[s.name] = arr->elements.size();
            }
        }
    }

    void visit(Assign& s) override {
        s.value->accept(*this);
        if (declaredVars.find(s.name) == declaredVars.end() &&
            declaredFuncs.find(s.name) == declaredFuncs.end()) {
            reportError("Variable '" + s.name + "' is assigned before declaration", s.loc);
        }
        // Track functions assigned after declaration
        if (auto fn = std::dynamic_pointer_cast<FunctionLiteral>(s.value)) {
            declaredFuncs[s.name] = fn;
        }
        // Track/clear known array literal sizes
        if (auto arr = std::dynamic_pointer_cast<ArrayLiteral>(s.value)) {
            arrayLiteralSizes[s.name] = arr->elements.size();
        } else {
            // If reassigned to unknown, forget precise size
            arrayLiteralSizes.erase(s.name);
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
        // Basic type check: assert requires boolean-like condition when statically known
        if (dynamic_cast<NumberExpr*>(s.condition.get()) ||
            dynamic_cast<StringExpr*>(s.condition.get()) ||
            dynamic_cast<NoneExpr*>(s.condition.get()) ||
            dynamic_cast<ArrayLiteral*>(s.condition.get()) ||
            dynamic_cast<TupleLiteral*>(s.condition.get())) {
            reportError("Assert condition must be boolean", s.loc);
        }
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
        declaredVars.insert(s.variable); // loop variable is available in the loop body
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
        // Special-case: 'break' used as a statement parsed as a variable expression
        if (auto var = dynamic_cast<VariableExpr*>(s.expr.get())) {
            if (var->name == "break") {
                if (!inLoop) {
                    reportError("'break' statement can only be used inside loops", s.loc);
                }
                return; // Do not treat as variable usage
            }
        }
        s.expr->accept(*this);
    }
};

// SemanticOptimizer: optimizations that MODIFY the AST
struct SemanticOptimizer : ASTVisitor {
    bool modified {false};
    std::shared_ptr<Expression> optimizedExpr {nullptr};
    std::shared_ptr<Statement> optimizedStmt {nullptr};
    int stmtListDepth {0};

    // Collect variable reads to enable removing unused variable declarations
    struct UsageCollector : ASTVisitor {
        std::unordered_set<std::string> usedVars;
        void visit(NumberExpr&) override {}
        void visit(StringExpr&) override {}
        void visit(BooleanExpr&) override {}
        void visit(NoneExpr&) override {}
        void visit(VariableExpr& e) override { usedVars.insert(e.name); }
        void visit(UnaryExpr& e) override { e.rhs->accept(*this); }
        void visit(BinaryExpr& e) override { e.lhs->accept(*this); e.rhs->accept(*this); }
        void visit(ArrayLiteral& e) override { for (auto& el : e.elements) el->accept(*this); }
        void visit(TupleLiteral& e) override { for (auto& f : e.fields) f.value->accept(*this); }
        void visit(IndexExpr& e) override { e.array->accept(*this); e.index->accept(*this); }
        void visit(CallExpr& e) override { e.callee->accept(*this); for (auto& a : e.args) a->accept(*this); }
        void visit(RangeExpr& e) override { e.start->accept(*this); e.end->accept(*this); }
        void visit(AssignExpr& e) override { e.value->accept(*this); }
        void visit(TypeExpr&) override {}
        void visit(IsExpr& e) override { e.expr->accept(*this); }
        void visit(FieldAccessExpr& e) override { e.object->accept(*this); }
        void visit(FunctionLiteral& e) override { if (e.body) e.body->accept(*this); }
        void visit(IfExpr& e) override {
            e.cond->accept(*this); e.thenExpr->accept(*this); if (e.elseExpr) e.elseExpr->accept(*this);
        }
        void visit(StatementList& s) override { for (auto& st : s.statements) st->accept(*this); }
        void visit(VarDecl& s) override { if (s.init) s.init->accept(*this); }
        void visit(Assign& s) override { usedVars.insert(s.name); s.value->accept(*this); }
        void visit(IfStmt& s) override {
            s.cond->accept(*this); s.thenBranch->accept(*this); if (s.elseBranch) s.elseBranch->accept(*this);
        }
        void visit(PrintStmt& s) override { for (auto& e : s.exprs) e->accept(*this); }
        void visit(AssertStmt& s) override { s.condition->accept(*this); }
        void visit(WhileStmt& s) override { s.condition->accept(*this); s.body->accept(*this); }
        void visit(ForStmt& s) override { s.iterable->accept(*this); s.body->accept(*this); }
        void visit(LoopStmt& s) override { s.body->accept(*this); }
        void visit(ExitStmt&) override {}
        void visit(ReturnStmt& s) override { if (s.value) s.value->accept(*this); }
        void visit(IndexedAssign& s) override { s.target->accept(*this); s.value->accept(*this); }
        void visit(ExprStmt& s) override { s.expr->accept(*this); }
    };

    // Helper function to evaluate constant expressions
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
        
        // Optimization: -(-x) -> x, !(!x) -> x (if needed)
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
        
        // Optimization: simplify constant expressions
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

        // Inline simple zero-arg function literal returning an expression
        if (auto fn = dynamic_cast<FunctionLiteral*>(e.callee.get())) {
            if (fn->params.empty()) {
                // Try to extract an expression from body
                if (auto bodyList = dynamic_cast<StatementList*>(fn->body.get())) {
                    // Inline if body is a single ExprStmt or Return with value
                    if (bodyList->statements.size() == 1) {
                        if (auto es = dynamic_cast<ExprStmt*>(bodyList->statements[0].get())) {
                            optimizedExpr = es->expr;
                            modified = true;
                        } else if (auto rs = dynamic_cast<ReturnStmt*>(bodyList->statements[0].get())) {
                            if (rs->value) { optimizedExpr = rs->value; modified = true; }
                        }
                    }
                } else if (auto es2 = dynamic_cast<ExprStmt*>(fn->body.get())) {
                    optimizedExpr = es2->expr; modified = true;
                } else if (auto rs2 = dynamic_cast<ReturnStmt*>(fn->body.get())) {
                    if (rs2->value) { optimizedExpr = rs2->value; modified = true; }
                }
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
        
        // Check if the condition is a boolean constant
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
        
        // Optimization: if True then X else Y -> X
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
        stmtListDepth++;
        // First, collect variable usage inside this block
        UsageCollector collector;
        s.accept(collector); // safe: UsageCollector doesn't modify

        std::vector<std::shared_ptr<Statement>> newStatements;
        bool foundReturn = false;
        bool listModified = false;

        for (auto& stmt : s.statements) {
            if (foundReturn) {
                listModified = true;
                modified = true;
                continue;
            }

            // Remove unused variable declarations (never read)
            // Only inside nested blocks (not at root), and keep function declarations
            if (auto vd = dynamic_cast<VarDecl*>(stmt.get())) {
                bool isFunctionDecl = vd->init && dynamic_cast<FunctionLiteral*>(vd->init.get());
                if (stmtListDepth > 1 && !isFunctionDecl && collector.usedVars.find(vd->name) == collector.usedVars.end()) {
                    listModified = true;
                    modified = true;
                    if (vd->init) vd->init->accept(*this);
                    continue; // drop declaration
                }
            }

            // Inline ExprStmt(Call(FunctionLiteral0)) into statements
            if (auto es = dynamic_cast<ExprStmt*>(stmt.get())) {
                if (auto call = dynamic_cast<CallExpr*>(es->expr.get())) {
                    if (auto fn = dynamic_cast<FunctionLiteral*>(call->callee.get())) {
                        if (fn->params.empty()) {
                            // Inline body into statement list when it's a block
                            if (auto bl = dynamic_cast<StatementList*>(fn->body.get())) {
                                for (auto& sub : bl->statements) newStatements.push_back(sub);
                                listModified = true; modified = true; continue;
                            } else if (auto rs = dynamic_cast<ReturnStmt*>(fn->body.get())) {
                                if (rs->value) {
                                    newStatements.push_back(std::make_shared<ExprStmt>(rs->value));
                                    listModified = true; modified = true; continue;
                                }
                            } else if (auto esb = dynamic_cast<ExprStmt*>(fn->body.get())) {
                                newStatements.push_back(std::make_shared<ExprStmt>(esb->expr));
                                listModified = true; modified = true; continue;
                            }
                        }
                    }
                }
            }

            stmt->accept(*this);

            if (optimizedStmt) {
                if (auto list = dynamic_cast<StatementList*>(optimizedStmt.get())) {
                    for (auto& substmt : list->statements) {
                        newStatements.push_back(substmt);
                    }
                    listModified = true;
                } else {
                    newStatements.push_back(optimizedStmt);
                    listModified = true;
                }
                optimizedStmt = nullptr;
            } else {
                newStatements.push_back(stmt);
            }

            if (dynamic_cast<ReturnStmt*>(newStatements.back().get())) {
                foundReturn = true;
            }
        }

        if (listModified) {
            s.statements = std::move(newStatements);
        }
        stmtListDepth--;
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
        
        // Check if the condition is a boolean constant
        bool isTrue = false;
        bool isFalse = false;
        
        auto condBool = dynamic_cast<BooleanExpr*>(s.cond.get());
        if (condBool) {
            isTrue = condBool->value;
            isFalse = !condBool->value;
        } else if (auto varExpr = dynamic_cast<VariableExpr*>(s.cond.get())) {
            // Process True/False as variables (if the parser recognizes them)
            if (varExpr->name == "True") {
                isTrue = true;
            } else if (varExpr->name == "False") {
                isFalse = true;
            }
        }
        
        // Optimization: if True then X else Y -> X
        if (isTrue) {
            s.thenBranch->accept(*this);
            // If thenBranch is a StatementList, use it directly
            if (dynamic_cast<StatementList*>(s.thenBranch.get())) {
                optimizedStmt = s.thenBranch;
            } else {
                // Wrap in StatementList
                auto newList = make_stmt_list();
                newList->push(s.thenBranch);
                optimizedStmt = newList;
            }
            modified = true;
        } 
        // Optimization: if False then X else Y -> Y (or remove)
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
                // Remove the entire if (replace with empty StatementList)
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
        
        // Optimization: while False -> remove the body
        auto condBool = dynamic_cast<BooleanExpr*>(s.condition.get());
        if (condBool && !condBool->value) {
            // Replace with empty StatementList
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
