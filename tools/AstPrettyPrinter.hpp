#pragma once

#include <iostream>
#include <memory>
#include <string>
#include "ast/Visitor.hpp"
#include "ast/Expression.hpp"
#include "ast/Statement.hpp"

namespace dli {

struct AstPrettyPrinter : ASTVisitor {
    std::ostream& out;
    int indent {0};

    explicit AstPrettyPrinter(std::ostream& o) : out(o) {}

    void printIndent() { for (int i = 0; i < indent; ++i) out << "  "; }
    void line(const std::string& s) { printIndent(); out << s << '\n'; }

    void visit(NumberExpr& e) override {
        line("Number(" + std::to_string(e.value) + ")");
    }

    void visit(StringExpr& e) override {
        line("String(\"" + e.value + "\")");
    }

    void visit(BooleanExpr& e) override {
        line(std::string("Boolean(") + (e.value ? "true" : "false") + ")");
    }

    void visit(NoneExpr& e) override {
        line("None");
    }

    void visit(VariableExpr& e) override {
        line("Var(" + e.name + ")");
    }

    void visit(UnaryExpr& e) override {
        line("Unary(" + e.op + ")");
        indent++;
        e.rhs->accept(*this);
        indent--;
    }

    void visit(BinaryExpr& e) override {
        line("Binary(" + e.op + ")");
        indent++;
        e.lhs->accept(*this);
        e.rhs->accept(*this);
        indent--;
    }

    void visit(ArrayLiteral& e) override {
        line("Array[" + std::to_string(e.elements.size()) + "]");
        indent++;
        for (auto& elem : e.elements) {
            elem->accept(*this);
        }
        indent--;
    }

    void visit(TupleLiteral& e) override {
        line("Tuple[" + std::to_string(e.fields.size()) + " fields]");
        indent++;
        for (auto& f : e.fields) {
            if (f.name.empty()) {
                line("<unnamed>:");
            } else {
                line(f.name + ":");
            }
            indent++;
            f.value->accept(*this);
            indent--;
        }
        indent--;
    }

    void visit(IndexExpr& e) override {
        line("Index");
        indent++;
        line("Array:");
        indent++;
        e.array->accept(*this);
        indent--;
        line("Index:");
        indent++;
        e.index->accept(*this);
        indent--;
        indent--;
    }

    void visit(CallExpr& e) override {
        line("Call[" + std::to_string(e.args.size()) + " args]");
        indent++;
        line("Callee:");
        indent++;
        e.callee->accept(*this);
        indent--;
        if (!e.args.empty()) {
            line("Args:");
            indent++;
            for (auto& arg : e.args) {
                arg->accept(*this);
            }
            indent--;
        }
        indent--;
    }

    void visit(RangeExpr& e) override {
        line("Range");
        indent++;
        line("Start:");
        indent++;
        e.start->accept(*this);
        indent--;
        line("End:");
        indent++;
        e.end->accept(*this);
        indent--;
        indent--;
    }

    void visit(AssignExpr& e) override {
        line("AssignExpr(" + e.name + ")");
        indent++;
        e.value->accept(*this);
        indent--;
    }

    void visit(TypeExpr& e) override {
        line("Type(" + e.typeName + ")");
    }

    void visit(IsExpr& e) override {
        line("Is");
        indent++;
        line("Expr:");
        indent++;
        e.expr->accept(*this);
        indent--;
        line("Type:");
        indent++;
        e.type->accept(*this);
        indent--;
        indent--;
    }

    void visit(FieldAccessExpr& e) override {
        line("FieldAccess(." + e.fieldName + ")");
        indent++;
        e.object->accept(*this);
        indent--;
    }

    void visit(FunctionLiteral& e) override {
        line("Function[" + std::to_string(e.params.size()) + " params" + 
             (e.isArrow ? ", arrow" : "") + "]");
        indent++;
        if (!e.params.empty()) {
            std::string params_str = "Params: ";
            for (size_t i = 0; i < e.params.size(); ++i) {
                if (i > 0) params_str += ", ";
                params_str += e.params[i];
            }
            line(params_str);
        }
        line("Body:");
        indent++;
        e.body->accept(*this);
        indent--;
        indent--;
    }

    void visit(IfExpr& e) override {
        line("IfExpr");
        indent++;
        line("Cond:");
        indent++;
        e.cond->accept(*this);
        indent--;
        line("Then:");
        indent++;
        e.thenExpr->accept(*this);
        indent--;
        if (e.elseExpr) {
            line("Else:");
            indent++;
            e.elseExpr->accept(*this);
            indent--;
        }
        indent--;
    }

    void visit(StatementList& s) override {
        line("StmtList");
        indent++;
        for (auto& st : s.statements) {
            st->accept(*this);
        }
        indent--;
    }

    void visit(VarDecl& s) override {
        line("VarDecl(" + s.name + ")");
        if (s.init) {
            indent++;
            s.init->accept(*this);
            indent--;
        }
    }

    void visit(Assign& s) override {
        line("Assign(" + s.name + ")");
        indent++;
        s.value->accept(*this);
        indent--;
    }

    void visit(IfStmt& s) override {
        line("If");
        indent++;
        line("Cond:");
        indent++;
        s.cond->accept(*this);
        indent--;
        line("Then:");
        indent++;
        s.thenBranch->accept(*this);
        indent--;
        if (s.elseBranch) {
            line("Else:");
            indent++;
            s.elseBranch->accept(*this);
            indent--;
        }
        indent--;
    }

    void visit(PrintStmt& s) override {
        line("Print[" + std::to_string(s.exprs.size()) + " args]");
        indent++;
        for (auto& e : s.exprs) {
            e->accept(*this);
        }
        indent--;
    }

    void visit(AssertStmt& s) override {
        line("Assert");
        indent++;
        s.condition->accept(*this);
        indent--;
    }

    void visit(WhileStmt& s) override {
        line("While");
        indent++;
        line("Condition:");
        indent++;
        s.condition->accept(*this);
        indent--;
        line("Body:");
        indent++;
        s.body->accept(*this);
        indent--;
        indent--;
    }

    void visit(ForStmt& s) override {
        line("For(" + s.variable + ")");
        indent++;
        line("Iterable:");
        indent++;
        s.iterable->accept(*this);
        indent--;
        line("Body:");
        indent++;
        s.body->accept(*this);
        indent--;
        indent--;
    }

    void visit(LoopStmt& s) override {
        line("Loop");
        indent++;
        s.body->accept(*this);
        indent--;
    }

    void visit(ExitStmt&) override {
        line("Exit");
    }

    void visit(ReturnStmt& s) override {
        if (s.value) {
            line("Return");
            indent++;
            s.value->accept(*this);
            indent--;
        } else {
            line("Return (void)");
        }
    }

    void visit(IndexedAssign& s) override {
        line("IndexedAssign");
        indent++;
        line("Target:");
        indent++;
        s.target->accept(*this);
        indent--;
        line("Value:");
        indent++;
        s.value->accept(*this);
        indent--;
        indent--;
    }

    void visit(ExprStmt& s) override {
        line("ExprStmt");
        indent++;
        s.expr->accept(*this);
        indent--;
    }
};

} // namespace dli


