%skeleton "lalr1.cc"
%require "3.8"
%language "c++"
%defines
%define api.namespace {dli}
%define api.parser.class {Parser}
%define api.value.type variant
%define api.token.constructor
%define parse.error verbose
%locations
%parse-param { dli::Lexer& lexer }
%initial-action {
    dli::g_current_lexer = &lexer;
}

%code requires {
    #include <memory>
    #include <string>
    #include <vector>
    #include <iostream>
    #include "lexer/token.hpp"
    #include "lexer/lexer.hpp"
    #include "ast/ASTNode.hpp"
    #include "ast/Expression.hpp"
    #include "ast/Statement.hpp"
    #include "ast/ASTFactory.hpp"

    namespace dli {
        class ASTNode;
        class Expression;
        class Statement;
        // extern declaration for thread-local current lexer used by yylex()
        extern thread_local Lexer* g_current_lexer;
    }
}

%code {
    namespace dli {
        std::shared_ptr<ASTNode> g_root;
    }

    namespace dli {
        thread_local Lexer* g_current_lexer = nullptr;

        Parser::symbol_type yylex() {
            using Sym = Parser;
            auto& lx = *g_current_lexer;
            auto t = lx.nextToken();
            Parser::location_type loc;
            loc.begin.line = static_cast<int>(t.location.line);
            loc.begin.column = static_cast<int>(t.location.column);
            loc.end.line = static_cast<int>(t.location.line);
            loc.end.column = static_cast<int>(t.location.column + (t.length > 0 ? t.length - 1 : 0));

            switch (t.type) {
                case TokenType::EndOfFile: return Sym::make_YYEOF(loc);
                case TokenType::Error:     return Sym::make_YYerror(loc);

                case TokenType::Identifier: return Sym::make_IDENTIFIER(t, loc);
                case TokenType::Integer:    return Sym::make_INTEGER(t, loc);
                case TokenType::Real:       return Sym::make_REAL(t, loc);
                case TokenType::String:     return Sym::make_STRING(t, loc);

                case TokenType::KwTrue:   return Sym::make_KW_TRUE(loc);
                case TokenType::KwFalse:  return Sym::make_KW_FALSE(loc);
                case TokenType::KwNone:   return Sym::make_KW_NONE(loc);
                case TokenType::KwVar:    return Sym::make_KW_VAR(loc);
                case TokenType::KwIf:     return Sym::make_KW_IF(loc);
                case TokenType::KwThen:   return Sym::make_KW_THEN(loc);
                case TokenType::KwElse:   return Sym::make_KW_ELSE(loc);
                case TokenType::KwEnd:    return Sym::make_KW_END(loc);
                case TokenType::KwExit:   return Sym::make_KW_EXIT(loc);
                case TokenType::KwReturn: return Sym::make_KW_RETURN(loc);
                case TokenType::KwPrint:  return Sym::make_KW_PRINT(loc);
                case TokenType::KwAssert: return Sym::make_KW_ASSERT(loc);
                case TokenType::KwTest:   return Sym::make_KW_TEST(loc);
                case TokenType::KwWhile:  return Sym::make_KW_WHILE(loc);
                case TokenType::KwFor:    return Sym::make_KW_FOR(loc);
                case TokenType::KwLoop:   return Sym::make_KW_LOOP(loc);
                case TokenType::KwIn:     return Sym::make_KW_IN(loc);
                case TokenType::KwIs:     return Sym::make_KW_IS(loc);
                case TokenType::KwInt:    return Sym::make_KW_INT(loc);
                case TokenType::KwReal:   return Sym::make_KW_REAL(loc);
                case TokenType::KwBool:   return Sym::make_KW_BOOL(loc);
                case TokenType::KwString: return Sym::make_KW_STRING(loc);
                case TokenType::KwFunc:   return Sym::make_KW_FUNC(loc);
                case TokenType::KwAnd:    return Sym::make_KW_AND(loc);
                case TokenType::KwOr:     return Sym::make_KW_OR(loc);
                case TokenType::KwXor:    return Sym::make_KW_XOR(loc);
                case TokenType::KwNot:    return Sym::make_KW_NOT(loc);

                case TokenType::AssignColon:   return Sym::make_ASSIGN_COLON(loc);
                case TokenType::Equal:         return Sym::make_EQUAL(loc);
                case TokenType::EqualEqual:    return Sym::make_EQUAL_EQUAL(loc);
                case TokenType::Arrow:         return Sym::make_ARROW(loc);
                case TokenType::Less:          return Sym::make_LESS(loc);
                case TokenType::LessEqual:     return Sym::make_LESS_EQUAL(loc);
                case TokenType::Greater:       return Sym::make_GREATER(loc);
                case TokenType::GreaterEqual:  return Sym::make_GREATER_EQUAL(loc);
                case TokenType::NotEqualSlash: return Sym::make_NOT_EQUAL_SLASH(loc);
                case TokenType::Plus:          return Sym::make_PLUS(loc);
                case TokenType::Minus:         return Sym::make_MINUS(loc);
                case TokenType::Star:          return Sym::make_STAR(loc);
                case TokenType::Slash:         return Sym::make_SLASH(loc);
                case TokenType::LParen:        return Sym::make_LPAREN(loc);
                case TokenType::RParen:        return Sym::make_RPAREN(loc);
                case TokenType::LBracket:      return Sym::make_LBRACKET(loc);
                case TokenType::RBracket:      return Sym::make_RBRACKET(loc);
                case TokenType::LBrace:        return Sym::make_LBRACE(loc);
                case TokenType::RBrace:        return Sym::make_RBRACE(loc);
                case TokenType::Comma:         return Sym::make_COMMA(loc);
                case TokenType::Dot:           return Sym::make_DOT(loc);
                case TokenType::DotDot:        return Sym::make_DOT_DOT(loc);
                case TokenType::Semicolon:     return Sym::make_SEMICOLON(loc);

                default:
                    return Sym::make_YYerror(loc);
            }
        }
    }

}

%code provides {
    // Provide Parser::error implementation after class declaration
    inline void dli::Parser::error(const dli::Parser::location_type& loc, const std::string& msg) {
        std::cerr << loc << ": " << msg << '\n';
    }
    
    // Helper macro to set location on AST nodes
    #define SET_LOC(node, location) \
        do { \
            (node)->loc.firstLine = (location).begin.line; \
            (node)->loc.firstColumn = (location).begin.column; \
            (node)->loc.lastLine = (location).end.line; \
            (node)->loc.lastColumn = (location).end.column; \
        } while(0)
}

%token <dli::Token> IDENTIFIER INTEGER REAL STRING

%token KW_TRUE
%token KW_FALSE
%token KW_NONE
%token KW_VAR
%token KW_IF
%token KW_THEN
%token KW_ELSE
%token KW_END
%token KW_EXIT
%token KW_RETURN
%token KW_PRINT
%token KW_ASSERT
%token KW_TEST
%token KW_WHILE
%token KW_FOR
%token KW_LOOP
%token KW_IN
%token KW_IS
%token KW_INT
%token KW_REAL
%token KW_BOOL
%token KW_STRING
%token KW_FUNC
%token KW_AND
%token KW_OR
%token KW_XOR
%token KW_NOT

%token ASSIGN_COLON
%token EQUAL
%token EQUAL_EQUAL
%token ARROW
%token LESS
%token LESS_EQUAL
%token GREATER
%token GREATER_EQUAL
%token NOT_EQUAL_SLASH
%token PLUS
%token MINUS
%token STAR
%token SLASH
%token LPAREN
%token RPAREN
%token LBRACKET
%token RBRACKET
%token LBRACE
%token RBRACE
%token COMMA
%token DOT
%token DOT_DOT
%token SEMICOLON

/* declarations continue below; grammar starts at the next %% */

%left KW_OR KW_XOR
%left KW_AND
%left EQUAL EQUAL_EQUAL NOT_EQUAL_SLASH LESS LESS_EQUAL GREATER GREATER_EQUAL
%left PLUS MINUS
%left STAR SLASH
%right KW_NOT UMINUS

%type <std::shared_ptr<dli::Statement>> statement
%type <std::shared_ptr<dli::StatementList>> statement_list
%type <std::shared_ptr<dli::Expression>> expression relation term unary postfix primary if_expression
%type <std::shared_ptr<dli::TypeExpr>> type_name
%type <std::vector<std::shared_ptr<dli::Expression>>> expression_list_nonempty
%type <std::vector<dli::TupleField>> tuple_field_list tuple_field_list_nonempty
%type <dli::TupleField> tuple_field
%type <std::vector<std::string>> param_list param_list_nonempty
%type <std::vector<std::pair<std::string, std::shared_ptr<dli::Expression>>>> var_decl_list var_decl_list_nonempty
%type <std::pair<std::string, std::shared_ptr<dli::Expression>>> var_decl_item

%%

translation_unit:
    /* empty */                     { dli::g_root = nullptr; }
  | statement_list                  { dli::g_root = $1; }
  ;

statement_list:
    statement                       { $$ = dli::make_stmt_list(); $$->push($1); }
  | statement_list SEMICOLON statement { $$ = dli::append_stmt($1, $3); }
  | statement_list statement        { $$ = dli::append_stmt($1, $2); }
  ;

statement:
    KW_TEST IDENTIFIER LPAREN param_list RPAREN KW_IS statement_list KW_END
      { auto func = dli::make_function($4, $7, false);
        $$ = dli::make_var_decl($2.lexeme, func); }
  | KW_VAR var_decl_list
      { auto stmts = dli::make_stmt_list();
        for (auto& [name, expr] : $2) {
          stmts->push(dli::make_var_decl(name, expr));
        }
        $$ = stmts; }
  | KW_VAR IDENTIFIER
      { $$ = dli::make_var_decl($2.lexeme, dli::make_none()); SET_LOC($$, @$); }
  | IDENTIFIER ASSIGN_COLON expression          { $$ = dli::make_assignment($1.lexeme, $3); SET_LOC($$, @$); }
  | postfix ASSIGN_COLON expression             { $$ = dli::make_indexed_assign($1, $3); SET_LOC($$, @$); }
  | postfix                                     { $$ = dli::make_expr_stmt($1); SET_LOC($$, @$); }
  | KW_IF expression ARROW statement            { $$ = dli::make_if($2, $4, nullptr); SET_LOC($$, @$); }
  | KW_IF expression KW_THEN statement_list KW_END   { $$ = dli::make_if($2, $4, nullptr); SET_LOC($$, @$); }
  | KW_IF expression KW_THEN statement_list KW_ELSE statement_list KW_END 
      { $$ = dli::make_if($2, $4, $6); SET_LOC($$, @$); }
  | KW_PRINT expression_list_nonempty           { $$ = dli::make_print($2); SET_LOC($$, @$); }
  | KW_ASSERT expression                        { $$ = dli::make_assert($2); SET_LOC($$, @$); }
  | KW_WHILE expression KW_LOOP statement_list KW_END { $$ = dli::make_while($2, $4); SET_LOC($$, @$); }
  | KW_FOR IDENTIFIER KW_IN expression KW_LOOP statement_list KW_END { $$ = dli::make_for($2.lexeme, $4, $6); SET_LOC($$, @$); }
  | KW_LOOP statement_list KW_END               { $$ = dli::make_loop($2); SET_LOC($$, @$); }
  | KW_EXIT                                     { $$ = dli::make_exit(); SET_LOC($$, @$); }
  | KW_RETURN expression                        { $$ = dli::make_return($2); SET_LOC($$, @$); }
  | KW_RETURN                                   { $$ = dli::make_return(); SET_LOC($$, @$); }
  ;

expression:
    relation
  | if_expression
  | expression KW_OR relation    { $$ = dli::make_binary("or", $1, $3); SET_LOC($$, @$); }
  | expression KW_AND relation   { $$ = dli::make_binary("and", $1, $3); SET_LOC($$, @$); }
  | expression KW_XOR relation   { $$ = dli::make_binary("xor", $1, $3); SET_LOC($$, @$); }
  ;

if_expression:
    KW_IF expression KW_THEN expression KW_ELSE expression KW_END
      { $$ = dli::make_if_expr($2, $4, $6); SET_LOC($$, @$); }
  | KW_IF expression KW_THEN expression KW_ELSE KW_IF expression KW_THEN expression KW_END
      { $$ = dli::make_if_expr($2, $4, dli::make_if_expr($7, $9, dli::make_none())); SET_LOC($$, @$); }
  | KW_IF expression KW_THEN expression KW_ELSE KW_IF expression KW_THEN expression KW_ELSE expression KW_END
      { $$ = dli::make_if_expr($2, $4, dli::make_if_expr($7, $9, $11)); SET_LOC($$, @$); }
  ;

relation:
    term
  | relation LESS term           { $$ = dli::make_binary("<", $1, $3); SET_LOC($$, @$); }
  | relation LESS_EQUAL term     { $$ = dli::make_binary("<=", $1, $3); SET_LOC($$, @$); }
  | relation GREATER term        { $$ = dli::make_binary(">", $1, $3); SET_LOC($$, @$); }
  | relation GREATER_EQUAL term  { $$ = dli::make_binary(">=", $1, $3); SET_LOC($$, @$); }
  | relation EQUAL term          { $$ = dli::make_binary("=", $1, $3); SET_LOC($$, @$); }
  | relation EQUAL_EQUAL term    { $$ = dli::make_binary("==", $1, $3); SET_LOC($$, @$); }
  | relation NOT_EQUAL_SLASH term{ $$ = dli::make_binary("/=", $1, $3); SET_LOC($$, @$); }
  | relation KW_IS type_name     { $$ = dli::make_is($1, $3); SET_LOC($$, @$); }
  ;

term:
    unary
  | term PLUS unary     { $$ = dli::make_binary("+", $1, $3); SET_LOC($$, @$); }
  | term MINUS unary    { $$ = dli::make_binary("-", $1, $3); SET_LOC($$, @$); }
  | term STAR unary     { $$ = dli::make_binary("*", $1, $3); SET_LOC($$, @$); }
  | term SLASH unary    { $$ = dli::make_binary("/", $1, $3); SET_LOC($$, @$); }
  | term DOT_DOT unary  { $$ = dli::make_range($1, $3); SET_LOC($$, @$); }
  ;

unary:
    postfix
  | MINUS unary %prec UMINUS { $$ = dli::make_unary("-", $2); SET_LOC($$, @$); }
  | PLUS unary               { $$ = dli::make_unary("+", $2); SET_LOC($$, @$); }
  | KW_NOT unary             { $$ = dli::make_unary("not", $2); SET_LOC($$, @$); }
  ;

postfix:
    primary
  | postfix LBRACKET expression RBRACKET { $$ = dli::make_index($1, $3); SET_LOC($$, @$); }
  | postfix LPAREN RPAREN { $$ = dli::make_call($1, std::vector<std::shared_ptr<dli::Expression>>()); SET_LOC($$, @$); }
  | postfix LPAREN expression_list_nonempty RPAREN { $$ = dli::make_call($1, $3); SET_LOC($$, @$); }
  | postfix DOT IDENTIFIER { $$ = dli::make_field_access($1, $3.lexeme); SET_LOC($$, @$); }
  | postfix DOT INTEGER    { $$ = dli::make_field_access($1, $3.lexeme); SET_LOC($$, @$); }
  ;

primary:
    INTEGER    { $$ = dli::make_number(std::stod($1.lexeme)); SET_LOC($$, @1); }
  | REAL       { $$ = dli::make_number(std::stod($1.lexeme)); SET_LOC($$, @1); }
  | STRING     { $$ = dli::make_string($1.lexeme); SET_LOC($$, @1); }
  | KW_TRUE    { $$ = dli::make_boolean(true); SET_LOC($$, @1); }
  | KW_FALSE   { $$ = dli::make_boolean(false); SET_LOC($$, @1); }
  | KW_NONE    { $$ = dli::make_none(); SET_LOC($$, @1); }
  | IDENTIFIER { $$ = dli::make_variable($1.lexeme); SET_LOC($$, @1); }
  | LPAREN expression RPAREN { $$ = $2; }
  | LPAREN IDENTIFIER ASSIGN_COLON expression RPAREN { $$ = dli::make_assign_expr($2.lexeme, $4); SET_LOC($$, @$); }
  | LBRACKET expression_list_nonempty RBRACKET { $$ = dli::make_array($2); SET_LOC($$, @$); }
  | LBRACKET RBRACKET { $$ = dli::make_array(std::vector<std::shared_ptr<dli::Expression>>()); SET_LOC($$, @$); }
  | LBRACE tuple_field_list RBRACE { $$ = dli::make_tuple($2); SET_LOC($$, @$); }
  | LBRACE RBRACE { $$ = dli::make_tuple(std::vector<dli::TupleField>()); SET_LOC($$, @$); }
  | LBRACE tuple_field_list KW_END { $$ = dli::make_tuple($2); SET_LOC($$, @$); }
  | LBRACE KW_END { $$ = dli::make_tuple(std::vector<dli::TupleField>()); SET_LOC($$, @$); }
  | KW_FUNC LPAREN param_list RPAREN KW_IS statement_list KW_END
      { $$ = dli::make_function($3, $6, false); SET_LOC($$, @$); }
  | KW_FUNC LPAREN param_list RPAREN ARROW expression
      { auto stmts = dli::make_stmt_list();
        stmts->push(dli::make_return($6));
        $$ = dli::make_function($3, stmts, true); SET_LOC($$, @$); }
  ;

expression_list_nonempty:
    expression { $$ = std::vector<std::shared_ptr<dli::Expression>>(); $$.push_back($1); }
  | expression_list_nonempty COMMA expression { $$ = $1; $$.push_back($3); }
  ;

type_name:
    KW_INT    { $$ = dli::make_type("int"); }
  | KW_REAL   { $$ = dli::make_type("real"); }
  | KW_BOOL   { $$ = dli::make_type("bool"); }
  | KW_STRING { $$ = dli::make_type("string"); }
  | KW_NONE   { $$ = dli::make_type("none"); }
  | KW_FUNC   { $$ = dli::make_type("func"); }
  | LBRACKET RBRACKET { $$ = dli::make_type("[]"); }
  | LBRACE RBRACE     { $$ = dli::make_type("{}"); }
  ;

tuple_field_list:
    /* empty */  { $$ = std::vector<dli::TupleField>(); }
  | tuple_field_list_nonempty { $$ = $1; }
  ;

tuple_field_list_nonempty:
    tuple_field { $$ = std::vector<dli::TupleField>(); $$.push_back($1); }
  | tuple_field_list_nonempty COMMA tuple_field { $$ = $1; $$.push_back($3); }
  ;

tuple_field:
    IDENTIFIER ASSIGN_COLON expression { $$ = dli::TupleField($1.lexeme, $3); }
  | expression { $$ = dli::TupleField("", $1); }
  ;

param_list:
    /* empty */ { $$ = std::vector<std::string>(); }
  | param_list_nonempty { $$ = $1; }
  ;

param_list_nonempty:
    IDENTIFIER { $$ = std::vector<std::string>(); $$.push_back($1.lexeme); }
  | param_list_nonempty COMMA IDENTIFIER { $$ = $1; $$.push_back($3.lexeme); }
  ;

var_decl_list:
    var_decl_list_nonempty { $$ = $1; }
  ;

var_decl_list_nonempty:
    var_decl_item 
      { $$ = std::vector<std::pair<std::string, std::shared_ptr<dli::Expression>>>(); 
        $$.push_back($1); }
  | var_decl_list_nonempty COMMA var_decl_item 
      { $$ = $1; $$.push_back($3); }
  ;

var_decl_item:
    IDENTIFIER ASSIGN_COLON expression 
      { $$ = std::make_pair($1.lexeme, $3); }
    ;

%%
