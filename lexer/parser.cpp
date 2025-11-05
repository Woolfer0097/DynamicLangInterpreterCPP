// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "parser.hpp"


// Unqualified %code blocks.
#line 37 "lexer/parser.y"

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


#line 133 "lexer/parser.cpp"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 5 "lexer/parser.y"
namespace dli {
#line 226 "lexer/parser.cpp"

  /// Build a parser object.
  Parser::Parser (dli::Lexer& lexer_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      lexer (lexer_yyarg)
  {}

  Parser::~Parser ()
  {}

  Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



  // by_state.
  Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Parser::symbol_kind_type
  Parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_INTEGER: // INTEGER
      case symbol_kind::S_REAL: // REAL
      case symbol_kind::S_STRING: // STRING
        value.YY_MOVE_OR_COPY< dli::Token > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_tuple_field: // tuple_field
        value.YY_MOVE_OR_COPY< dli::TupleField > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_var_decl_item: // var_decl_item
        value.YY_MOVE_OR_COPY< std::pair<std::string, std::shared_ptr<dli::Expression>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_if_expression: // if_expression
      case symbol_kind::S_relation: // relation
      case symbol_kind::S_term: // term
      case symbol_kind::S_unary: // unary
      case symbol_kind::S_postfix: // postfix
      case symbol_kind::S_primary: // primary
        value.YY_MOVE_OR_COPY< std::shared_ptr<dli::Expression> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement: // statement
        value.YY_MOVE_OR_COPY< std::shared_ptr<dli::Statement> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement_list: // statement_list
        value.YY_MOVE_OR_COPY< std::shared_ptr<dli::StatementList> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_name: // type_name
        value.YY_MOVE_OR_COPY< std::shared_ptr<dli::TypeExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_tuple_field_list: // tuple_field_list
      case symbol_kind::S_tuple_field_list_nonempty: // tuple_field_list_nonempty
        value.YY_MOVE_OR_COPY< std::vector<dli::TupleField> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_var_decl_list: // var_decl_list
      case symbol_kind::S_var_decl_list_nonempty: // var_decl_list_nonempty
        value.YY_MOVE_OR_COPY< std::vector<std::pair<std::string, std::shared_ptr<dli::Expression>>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expression_list_nonempty: // expression_list_nonempty
        value.YY_MOVE_OR_COPY< std::vector<std::shared_ptr<dli::Expression>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param_list: // param_list
      case symbol_kind::S_param_list_nonempty: // param_list_nonempty
        value.YY_MOVE_OR_COPY< std::vector<std::string> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_INTEGER: // INTEGER
      case symbol_kind::S_REAL: // REAL
      case symbol_kind::S_STRING: // STRING
        value.move< dli::Token > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_tuple_field: // tuple_field
        value.move< dli::TupleField > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_var_decl_item: // var_decl_item
        value.move< std::pair<std::string, std::shared_ptr<dli::Expression>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_if_expression: // if_expression
      case symbol_kind::S_relation: // relation
      case symbol_kind::S_term: // term
      case symbol_kind::S_unary: // unary
      case symbol_kind::S_postfix: // postfix
      case symbol_kind::S_primary: // primary
        value.move< std::shared_ptr<dli::Expression> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement: // statement
        value.move< std::shared_ptr<dli::Statement> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement_list: // statement_list
        value.move< std::shared_ptr<dli::StatementList> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_name: // type_name
        value.move< std::shared_ptr<dli::TypeExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_tuple_field_list: // tuple_field_list
      case symbol_kind::S_tuple_field_list_nonempty: // tuple_field_list_nonempty
        value.move< std::vector<dli::TupleField> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_var_decl_list: // var_decl_list
      case symbol_kind::S_var_decl_list_nonempty: // var_decl_list_nonempty
        value.move< std::vector<std::pair<std::string, std::shared_ptr<dli::Expression>>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expression_list_nonempty: // expression_list_nonempty
        value.move< std::vector<std::shared_ptr<dli::Expression>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param_list: // param_list
      case symbol_kind::S_param_list_nonempty: // param_list_nonempty
        value.move< std::vector<std::string> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_INTEGER: // INTEGER
      case symbol_kind::S_REAL: // REAL
      case symbol_kind::S_STRING: // STRING
        value.copy< dli::Token > (that.value);
        break;

      case symbol_kind::S_tuple_field: // tuple_field
        value.copy< dli::TupleField > (that.value);
        break;

      case symbol_kind::S_var_decl_item: // var_decl_item
        value.copy< std::pair<std::string, std::shared_ptr<dli::Expression>> > (that.value);
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_if_expression: // if_expression
      case symbol_kind::S_relation: // relation
      case symbol_kind::S_term: // term
      case symbol_kind::S_unary: // unary
      case symbol_kind::S_postfix: // postfix
      case symbol_kind::S_primary: // primary
        value.copy< std::shared_ptr<dli::Expression> > (that.value);
        break;

      case symbol_kind::S_statement: // statement
        value.copy< std::shared_ptr<dli::Statement> > (that.value);
        break;

      case symbol_kind::S_statement_list: // statement_list
        value.copy< std::shared_ptr<dli::StatementList> > (that.value);
        break;

      case symbol_kind::S_type_name: // type_name
        value.copy< std::shared_ptr<dli::TypeExpr> > (that.value);
        break;

      case symbol_kind::S_tuple_field_list: // tuple_field_list
      case symbol_kind::S_tuple_field_list_nonempty: // tuple_field_list_nonempty
        value.copy< std::vector<dli::TupleField> > (that.value);
        break;

      case symbol_kind::S_var_decl_list: // var_decl_list
      case symbol_kind::S_var_decl_list_nonempty: // var_decl_list_nonempty
        value.copy< std::vector<std::pair<std::string, std::shared_ptr<dli::Expression>>> > (that.value);
        break;

      case symbol_kind::S_expression_list_nonempty: // expression_list_nonempty
        value.copy< std::vector<std::shared_ptr<dli::Expression>> > (that.value);
        break;

      case symbol_kind::S_param_list: // param_list
      case symbol_kind::S_param_list_nonempty: // param_list_nonempty
        value.copy< std::vector<std::string> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_INTEGER: // INTEGER
      case symbol_kind::S_REAL: // REAL
      case symbol_kind::S_STRING: // STRING
        value.move< dli::Token > (that.value);
        break;

      case symbol_kind::S_tuple_field: // tuple_field
        value.move< dli::TupleField > (that.value);
        break;

      case symbol_kind::S_var_decl_item: // var_decl_item
        value.move< std::pair<std::string, std::shared_ptr<dli::Expression>> > (that.value);
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_if_expression: // if_expression
      case symbol_kind::S_relation: // relation
      case symbol_kind::S_term: // term
      case symbol_kind::S_unary: // unary
      case symbol_kind::S_postfix: // postfix
      case symbol_kind::S_primary: // primary
        value.move< std::shared_ptr<dli::Expression> > (that.value);
        break;

      case symbol_kind::S_statement: // statement
        value.move< std::shared_ptr<dli::Statement> > (that.value);
        break;

      case symbol_kind::S_statement_list: // statement_list
        value.move< std::shared_ptr<dli::StatementList> > (that.value);
        break;

      case symbol_kind::S_type_name: // type_name
        value.move< std::shared_ptr<dli::TypeExpr> > (that.value);
        break;

      case symbol_kind::S_tuple_field_list: // tuple_field_list
      case symbol_kind::S_tuple_field_list_nonempty: // tuple_field_list_nonempty
        value.move< std::vector<dli::TupleField> > (that.value);
        break;

      case symbol_kind::S_var_decl_list: // var_decl_list
      case symbol_kind::S_var_decl_list_nonempty: // var_decl_list_nonempty
        value.move< std::vector<std::pair<std::string, std::shared_ptr<dli::Expression>>> > (that.value);
        break;

      case symbol_kind::S_expression_list_nonempty: // expression_list_nonempty
        value.move< std::vector<std::shared_ptr<dli::Expression>> > (that.value);
        break;

      case symbol_kind::S_param_list: // param_list
      case symbol_kind::S_param_list_nonempty: // param_list_nonempty
        value.move< std::vector<std::string> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  Parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::operator() ()
  {
    return parse ();
  }

  int
  Parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    // User initialization code.
#line 12 "lexer/parser.y"
{
    dli::g_current_lexer = &lexer;
}

#line 715 "lexer/parser.cpp"


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex ());
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_INTEGER: // INTEGER
      case symbol_kind::S_REAL: // REAL
      case symbol_kind::S_STRING: // STRING
        yylhs.value.emplace< dli::Token > ();
        break;

      case symbol_kind::S_tuple_field: // tuple_field
        yylhs.value.emplace< dli::TupleField > ();
        break;

      case symbol_kind::S_var_decl_item: // var_decl_item
        yylhs.value.emplace< std::pair<std::string, std::shared_ptr<dli::Expression>> > ();
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_if_expression: // if_expression
      case symbol_kind::S_relation: // relation
      case symbol_kind::S_term: // term
      case symbol_kind::S_unary: // unary
      case symbol_kind::S_postfix: // postfix
      case symbol_kind::S_primary: // primary
        yylhs.value.emplace< std::shared_ptr<dli::Expression> > ();
        break;

      case symbol_kind::S_statement: // statement
        yylhs.value.emplace< std::shared_ptr<dli::Statement> > ();
        break;

      case symbol_kind::S_statement_list: // statement_list
        yylhs.value.emplace< std::shared_ptr<dli::StatementList> > ();
        break;

      case symbol_kind::S_type_name: // type_name
        yylhs.value.emplace< std::shared_ptr<dli::TypeExpr> > ();
        break;

      case symbol_kind::S_tuple_field_list: // tuple_field_list
      case symbol_kind::S_tuple_field_list_nonempty: // tuple_field_list_nonempty
        yylhs.value.emplace< std::vector<dli::TupleField> > ();
        break;

      case symbol_kind::S_var_decl_list: // var_decl_list
      case symbol_kind::S_var_decl_list_nonempty: // var_decl_list_nonempty
        yylhs.value.emplace< std::vector<std::pair<std::string, std::shared_ptr<dli::Expression>>> > ();
        break;

      case symbol_kind::S_expression_list_nonempty: // expression_list_nonempty
        yylhs.value.emplace< std::vector<std::shared_ptr<dli::Expression>> > ();
        break;

      case symbol_kind::S_param_list: // param_list
      case symbol_kind::S_param_list_nonempty: // param_list_nonempty
        yylhs.value.emplace< std::vector<std::string> > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // translation_unit: %empty
#line 208 "lexer/parser.y"
                                    { dli::g_root = nullptr; }
#line 909 "lexer/parser.cpp"
    break;

  case 3: // translation_unit: statement_list
#line 209 "lexer/parser.y"
                                    { dli::g_root = yystack_[0].value.as < std::shared_ptr<dli::StatementList> > (); }
#line 915 "lexer/parser.cpp"
    break;

  case 4: // statement_list: statement
#line 213 "lexer/parser.y"
                                    { yylhs.value.as < std::shared_ptr<dli::StatementList> > () = dli::make_stmt_list(); yylhs.value.as < std::shared_ptr<dli::StatementList> > ()->push(yystack_[0].value.as < std::shared_ptr<dli::Statement> > ()); }
#line 921 "lexer/parser.cpp"
    break;

  case 5: // statement_list: statement_list SEMICOLON statement
#line 214 "lexer/parser.y"
                                       { yylhs.value.as < std::shared_ptr<dli::StatementList> > () = dli::append_stmt(yystack_[2].value.as < std::shared_ptr<dli::StatementList> > (), yystack_[0].value.as < std::shared_ptr<dli::Statement> > ()); }
#line 927 "lexer/parser.cpp"
    break;

  case 6: // statement_list: statement_list statement
#line 215 "lexer/parser.y"
                                    { yylhs.value.as < std::shared_ptr<dli::StatementList> > () = dli::append_stmt(yystack_[1].value.as < std::shared_ptr<dli::StatementList> > (), yystack_[0].value.as < std::shared_ptr<dli::Statement> > ()); }
#line 933 "lexer/parser.cpp"
    break;

  case 7: // statement: KW_TEST IDENTIFIER LPAREN param_list RPAREN KW_IS statement_list KW_END
#line 220 "lexer/parser.y"
      { auto func = dli::make_function(yystack_[4].value.as < std::vector<std::string> > (), yystack_[1].value.as < std::shared_ptr<dli::StatementList> > (), false);
        yylhs.value.as < std::shared_ptr<dli::Statement> > () = dli::make_var_decl(yystack_[6].value.as < dli::Token > ().lexeme, func); }
#line 940 "lexer/parser.cpp"
    break;

  case 8: // statement: KW_VAR var_decl_list
#line 223 "lexer/parser.y"
      { auto stmts = dli::make_stmt_list();
        for (auto& [name, expr] : yystack_[0].value.as < std::vector<std::pair<std::string, std::shared_ptr<dli::Expression>>> > ()) {
          stmts->push(dli::make_var_decl(name, expr));
        }
        yylhs.value.as < std::shared_ptr<dli::Statement> > () = stmts; }
#line 950 "lexer/parser.cpp"
    break;

  case 9: // statement: KW_VAR IDENTIFIER
#line 229 "lexer/parser.y"
      { yylhs.value.as < std::shared_ptr<dli::Statement> > () = dli::make_var_decl(yystack_[0].value.as < dli::Token > ().lexeme, dli::make_none()); }
#line 956 "lexer/parser.cpp"
    break;

  case 10: // statement: IDENTIFIER ASSIGN_COLON expression
#line 230 "lexer/parser.y"
                                                { yylhs.value.as < std::shared_ptr<dli::Statement> > () = dli::make_assignment(yystack_[2].value.as < dli::Token > ().lexeme, yystack_[0].value.as < std::shared_ptr<dli::Expression> > ()); }
#line 962 "lexer/parser.cpp"
    break;

  case 11: // statement: postfix ASSIGN_COLON expression
#line 231 "lexer/parser.y"
                                                { yylhs.value.as < std::shared_ptr<dli::Statement> > () = dli::make_indexed_assign(yystack_[2].value.as < std::shared_ptr<dli::Expression> > (), yystack_[0].value.as < std::shared_ptr<dli::Expression> > ()); }
#line 968 "lexer/parser.cpp"
    break;

  case 12: // statement: postfix
#line 232 "lexer/parser.y"
                                                { yylhs.value.as < std::shared_ptr<dli::Statement> > () = dli::make_expr_stmt(yystack_[0].value.as < std::shared_ptr<dli::Expression> > ()); }
#line 974 "lexer/parser.cpp"
    break;

  case 13: // statement: KW_IF expression ARROW statement
#line 233 "lexer/parser.y"
                                                { yylhs.value.as < std::shared_ptr<dli::Statement> > () = dli::make_if(yystack_[2].value.as < std::shared_ptr<dli::Expression> > (), yystack_[0].value.as < std::shared_ptr<dli::Statement> > (), nullptr); }
#line 980 "lexer/parser.cpp"
    break;

  case 14: // statement: KW_IF expression KW_THEN statement_list KW_END
#line 234 "lexer/parser.y"
                                                     { yylhs.value.as < std::shared_ptr<dli::Statement> > () = dli::make_if(yystack_[3].value.as < std::shared_ptr<dli::Expression> > (), yystack_[1].value.as < std::shared_ptr<dli::StatementList> > (), nullptr); }
#line 986 "lexer/parser.cpp"
    break;

  case 15: // statement: KW_IF expression KW_THEN statement_list KW_ELSE statement_list KW_END
#line 236 "lexer/parser.y"
      { yylhs.value.as < std::shared_ptr<dli::Statement> > () = dli::make_if(yystack_[5].value.as < std::shared_ptr<dli::Expression> > (), yystack_[3].value.as < std::shared_ptr<dli::StatementList> > (), yystack_[1].value.as < std::shared_ptr<dli::StatementList> > ()); }
#line 992 "lexer/parser.cpp"
    break;

  case 16: // statement: KW_PRINT expression_list_nonempty
#line 237 "lexer/parser.y"
                                                { yylhs.value.as < std::shared_ptr<dli::Statement> > () = dli::make_print(yystack_[0].value.as < std::vector<std::shared_ptr<dli::Expression>> > ()); }
#line 998 "lexer/parser.cpp"
    break;

  case 17: // statement: KW_ASSERT expression
#line 238 "lexer/parser.y"
                                                { yylhs.value.as < std::shared_ptr<dli::Statement> > () = dli::make_assert(yystack_[0].value.as < std::shared_ptr<dli::Expression> > ()); }
#line 1004 "lexer/parser.cpp"
    break;

  case 18: // statement: KW_WHILE expression KW_LOOP statement_list KW_END
#line 239 "lexer/parser.y"
                                                      { yylhs.value.as < std::shared_ptr<dli::Statement> > () = dli::make_while(yystack_[3].value.as < std::shared_ptr<dli::Expression> > (), yystack_[1].value.as < std::shared_ptr<dli::StatementList> > ()); }
#line 1010 "lexer/parser.cpp"
    break;

  case 19: // statement: KW_FOR IDENTIFIER KW_IN expression KW_LOOP statement_list KW_END
#line 240 "lexer/parser.y"
                                                                     { yylhs.value.as < std::shared_ptr<dli::Statement> > () = dli::make_for(yystack_[5].value.as < dli::Token > ().lexeme, yystack_[3].value.as < std::shared_ptr<dli::Expression> > (), yystack_[1].value.as < std::shared_ptr<dli::StatementList> > ()); }
#line 1016 "lexer/parser.cpp"
    break;

  case 20: // statement: KW_LOOP statement_list KW_END
#line 241 "lexer/parser.y"
                                                { yylhs.value.as < std::shared_ptr<dli::Statement> > () = dli::make_loop(yystack_[1].value.as < std::shared_ptr<dli::StatementList> > ()); }
#line 1022 "lexer/parser.cpp"
    break;

  case 21: // statement: KW_EXIT
#line 242 "lexer/parser.y"
                                                { yylhs.value.as < std::shared_ptr<dli::Statement> > () = dli::make_exit(); }
#line 1028 "lexer/parser.cpp"
    break;

  case 22: // statement: KW_RETURN expression
#line 243 "lexer/parser.y"
                                                { yylhs.value.as < std::shared_ptr<dli::Statement> > () = dli::make_return(yystack_[0].value.as < std::shared_ptr<dli::Expression> > ()); }
#line 1034 "lexer/parser.cpp"
    break;

  case 23: // statement: KW_RETURN
#line 244 "lexer/parser.y"
                                                { yylhs.value.as < std::shared_ptr<dli::Statement> > () = dli::make_return(); }
#line 1040 "lexer/parser.cpp"
    break;

  case 24: // expression: relation
#line 248 "lexer/parser.y"
    { yylhs.value.as < std::shared_ptr<dli::Expression> > () = yystack_[0].value.as < std::shared_ptr<dli::Expression> > (); }
#line 1046 "lexer/parser.cpp"
    break;

  case 25: // expression: if_expression
#line 249 "lexer/parser.y"
    { yylhs.value.as < std::shared_ptr<dli::Expression> > () = yystack_[0].value.as < std::shared_ptr<dli::Expression> > (); }
#line 1052 "lexer/parser.cpp"
    break;

  case 26: // expression: expression KW_OR relation
#line 250 "lexer/parser.y"
                                 { yylhs.value.as < std::shared_ptr<dli::Expression> > () = dli::make_binary("or", yystack_[2].value.as < std::shared_ptr<dli::Expression> > (), yystack_[0].value.as < std::shared_ptr<dli::Expression> > ()); }
#line 1058 "lexer/parser.cpp"
    break;

  case 27: // expression: expression KW_AND relation
#line 251 "lexer/parser.y"
                                 { yylhs.value.as < std::shared_ptr<dli::Expression> > () = dli::make_binary("and", yystack_[2].value.as < std::shared_ptr<dli::Expression> > (), yystack_[0].value.as < std::shared_ptr<dli::Expression> > ()); }
#line 1064 "lexer/parser.cpp"
    break;

  case 28: // expression: expression KW_XOR relation
#line 252 "lexer/parser.y"
                                 { yylhs.value.as < std::shared_ptr<dli::Expression> > () = dli::make_binary("xor", yystack_[2].value.as < std::shared_ptr<dli::Expression> > (), yystack_[0].value.as < std::shared_ptr<dli::Expression> > ()); }
#line 1070 "lexer/parser.cpp"
    break;

  case 29: // if_expression: KW_IF expression KW_THEN expression KW_ELSE expression KW_END
#line 257 "lexer/parser.y"
      { yylhs.value.as < std::shared_ptr<dli::Expression> > () = dli::make_if_expr(yystack_[5].value.as < std::shared_ptr<dli::Expression> > (), yystack_[3].value.as < std::shared_ptr<dli::Expression> > (), yystack_[1].value.as < std::shared_ptr<dli::Expression> > ()); }
#line 1076 "lexer/parser.cpp"
    break;

  case 30: // if_expression: KW_IF expression KW_THEN expression KW_ELSE KW_IF expression KW_THEN expression KW_END
#line 259 "lexer/parser.y"
      { yylhs.value.as < std::shared_ptr<dli::Expression> > () = dli::make_if_expr(yystack_[8].value.as < std::shared_ptr<dli::Expression> > (), yystack_[6].value.as < std::shared_ptr<dli::Expression> > (), dli::make_if_expr(yystack_[3].value.as < std::shared_ptr<dli::Expression> > (), yystack_[1].value.as < std::shared_ptr<dli::Expression> > (), dli::make_none())); }
#line 1082 "lexer/parser.cpp"
    break;

  case 31: // if_expression: KW_IF expression KW_THEN expression KW_ELSE KW_IF expression KW_THEN expression KW_ELSE expression KW_END
#line 261 "lexer/parser.y"
      { yylhs.value.as < std::shared_ptr<dli::Expression> > () = dli::make_if_expr(yystack_[10].value.as < std::shared_ptr<dli::Expression> > (), yystack_[8].value.as < std::shared_ptr<dli::Expression> > (), dli::make_if_expr(yystack_[5].value.as < std::shared_ptr<dli::Expression> > (), yystack_[3].value.as < std::shared_ptr<dli::Expression> > (), yystack_[1].value.as < std::shared_ptr<dli::Expression> > ())); }
#line 1088 "lexer/parser.cpp"
    break;

  case 32: // relation: term
#line 265 "lexer/parser.y"
    { yylhs.value.as < std::shared_ptr<dli::Expression> > () = yystack_[0].value.as < std::shared_ptr<dli::Expression> > (); }
#line 1094 "lexer/parser.cpp"
    break;

  case 33: // relation: relation LESS term
#line 266 "lexer/parser.y"
                                 { yylhs.value.as < std::shared_ptr<dli::Expression> > () = dli::make_binary("<", yystack_[2].value.as < std::shared_ptr<dli::Expression> > (), yystack_[0].value.as < std::shared_ptr<dli::Expression> > ()); }
#line 1100 "lexer/parser.cpp"
    break;

  case 34: // relation: relation LESS_EQUAL term
#line 267 "lexer/parser.y"
                                 { yylhs.value.as < std::shared_ptr<dli::Expression> > () = dli::make_binary("<=", yystack_[2].value.as < std::shared_ptr<dli::Expression> > (), yystack_[0].value.as < std::shared_ptr<dli::Expression> > ()); }
#line 1106 "lexer/parser.cpp"
    break;

  case 35: // relation: relation GREATER term
#line 268 "lexer/parser.y"
                                 { yylhs.value.as < std::shared_ptr<dli::Expression> > () = dli::make_binary(">", yystack_[2].value.as < std::shared_ptr<dli::Expression> > (), yystack_[0].value.as < std::shared_ptr<dli::Expression> > ()); }
#line 1112 "lexer/parser.cpp"
    break;

  case 36: // relation: relation GREATER_EQUAL term
#line 269 "lexer/parser.y"
                                 { yylhs.value.as < std::shared_ptr<dli::Expression> > () = dli::make_binary(">=", yystack_[2].value.as < std::shared_ptr<dli::Expression> > (), yystack_[0].value.as < std::shared_ptr<dli::Expression> > ()); }
#line 1118 "lexer/parser.cpp"
    break;

  case 37: // relation: relation EQUAL term
#line 270 "lexer/parser.y"
                                 { yylhs.value.as < std::shared_ptr<dli::Expression> > () = dli::make_binary("=", yystack_[2].value.as < std::shared_ptr<dli::Expression> > (), yystack_[0].value.as < std::shared_ptr<dli::Expression> > ()); }
#line 1124 "lexer/parser.cpp"
    break;

  case 38: // relation: relation EQUAL_EQUAL term
#line 271 "lexer/parser.y"
                                 { yylhs.value.as < std::shared_ptr<dli::Expression> > () = dli::make_binary("==", yystack_[2].value.as < std::shared_ptr<dli::Expression> > (), yystack_[0].value.as < std::shared_ptr<dli::Expression> > ()); }
#line 1130 "lexer/parser.cpp"
    break;

  case 39: // relation: relation NOT_EQUAL_SLASH term
#line 272 "lexer/parser.y"
                                 { yylhs.value.as < std::shared_ptr<dli::Expression> > () = dli::make_binary("/=", yystack_[2].value.as < std::shared_ptr<dli::Expression> > (), yystack_[0].value.as < std::shared_ptr<dli::Expression> > ()); }
#line 1136 "lexer/parser.cpp"
    break;

  case 40: // relation: relation KW_IS type_name
#line 273 "lexer/parser.y"
                                 { yylhs.value.as < std::shared_ptr<dli::Expression> > () = dli::make_is(yystack_[2].value.as < std::shared_ptr<dli::Expression> > (), yystack_[0].value.as < std::shared_ptr<dli::TypeExpr> > ()); }
#line 1142 "lexer/parser.cpp"
    break;

  case 41: // term: unary
#line 277 "lexer/parser.y"
    { yylhs.value.as < std::shared_ptr<dli::Expression> > () = yystack_[0].value.as < std::shared_ptr<dli::Expression> > (); }
#line 1148 "lexer/parser.cpp"
    break;

  case 42: // term: term PLUS unary
#line 278 "lexer/parser.y"
                        { yylhs.value.as < std::shared_ptr<dli::Expression> > () = dli::make_binary("+", yystack_[2].value.as < std::shared_ptr<dli::Expression> > (), yystack_[0].value.as < std::shared_ptr<dli::Expression> > ()); }
#line 1154 "lexer/parser.cpp"
    break;

  case 43: // term: term MINUS unary
#line 279 "lexer/parser.y"
                        { yylhs.value.as < std::shared_ptr<dli::Expression> > () = dli::make_binary("-", yystack_[2].value.as < std::shared_ptr<dli::Expression> > (), yystack_[0].value.as < std::shared_ptr<dli::Expression> > ()); }
#line 1160 "lexer/parser.cpp"
    break;

  case 44: // term: term STAR unary
#line 280 "lexer/parser.y"
                        { yylhs.value.as < std::shared_ptr<dli::Expression> > () = dli::make_binary("*", yystack_[2].value.as < std::shared_ptr<dli::Expression> > (), yystack_[0].value.as < std::shared_ptr<dli::Expression> > ()); }
#line 1166 "lexer/parser.cpp"
    break;

  case 45: // term: term SLASH unary
#line 281 "lexer/parser.y"
                        { yylhs.value.as < std::shared_ptr<dli::Expression> > () = dli::make_binary("/", yystack_[2].value.as < std::shared_ptr<dli::Expression> > (), yystack_[0].value.as < std::shared_ptr<dli::Expression> > ()); }
#line 1172 "lexer/parser.cpp"
    break;

  case 46: // term: term DOT_DOT unary
#line 282 "lexer/parser.y"
                        { yylhs.value.as < std::shared_ptr<dli::Expression> > () = dli::make_range(yystack_[2].value.as < std::shared_ptr<dli::Expression> > (), yystack_[0].value.as < std::shared_ptr<dli::Expression> > ()); }
#line 1178 "lexer/parser.cpp"
    break;

  case 47: // unary: postfix
#line 286 "lexer/parser.y"
    { yylhs.value.as < std::shared_ptr<dli::Expression> > () = yystack_[0].value.as < std::shared_ptr<dli::Expression> > (); }
#line 1184 "lexer/parser.cpp"
    break;

  case 48: // unary: MINUS unary
#line 287 "lexer/parser.y"
                             { yylhs.value.as < std::shared_ptr<dli::Expression> > () = dli::make_unary("-", yystack_[0].value.as < std::shared_ptr<dli::Expression> > ()); }
#line 1190 "lexer/parser.cpp"
    break;

  case 49: // unary: PLUS unary
#line 288 "lexer/parser.y"
                             { yylhs.value.as < std::shared_ptr<dli::Expression> > () = dli::make_unary("+", yystack_[0].value.as < std::shared_ptr<dli::Expression> > ()); }
#line 1196 "lexer/parser.cpp"
    break;

  case 50: // unary: KW_NOT unary
#line 289 "lexer/parser.y"
                             { yylhs.value.as < std::shared_ptr<dli::Expression> > () = dli::make_unary("not", yystack_[0].value.as < std::shared_ptr<dli::Expression> > ()); }
#line 1202 "lexer/parser.cpp"
    break;

  case 51: // postfix: primary
#line 293 "lexer/parser.y"
    { yylhs.value.as < std::shared_ptr<dli::Expression> > () = yystack_[0].value.as < std::shared_ptr<dli::Expression> > (); }
#line 1208 "lexer/parser.cpp"
    break;

  case 52: // postfix: postfix LBRACKET expression RBRACKET
#line 294 "lexer/parser.y"
                                         { yylhs.value.as < std::shared_ptr<dli::Expression> > () = dli::make_index(yystack_[3].value.as < std::shared_ptr<dli::Expression> > (), yystack_[1].value.as < std::shared_ptr<dli::Expression> > ()); }
#line 1214 "lexer/parser.cpp"
    break;

  case 53: // postfix: postfix LPAREN RPAREN
#line 295 "lexer/parser.y"
                          { yylhs.value.as < std::shared_ptr<dli::Expression> > () = dli::make_call(yystack_[2].value.as < std::shared_ptr<dli::Expression> > (), std::vector<std::shared_ptr<dli::Expression>>()); }
#line 1220 "lexer/parser.cpp"
    break;

  case 54: // postfix: postfix LPAREN expression_list_nonempty RPAREN
#line 296 "lexer/parser.y"
                                                   { yylhs.value.as < std::shared_ptr<dli::Expression> > () = dli::make_call(yystack_[3].value.as < std::shared_ptr<dli::Expression> > (), yystack_[1].value.as < std::vector<std::shared_ptr<dli::Expression>> > ()); }
#line 1226 "lexer/parser.cpp"
    break;

  case 55: // postfix: postfix DOT IDENTIFIER
#line 297 "lexer/parser.y"
                           { yylhs.value.as < std::shared_ptr<dli::Expression> > () = dli::make_field_access(yystack_[2].value.as < std::shared_ptr<dli::Expression> > (), yystack_[0].value.as < dli::Token > ().lexeme); }
#line 1232 "lexer/parser.cpp"
    break;

  case 56: // postfix: postfix DOT INTEGER
#line 298 "lexer/parser.y"
                           { yylhs.value.as < std::shared_ptr<dli::Expression> > () = dli::make_field_access(yystack_[2].value.as < std::shared_ptr<dli::Expression> > (), yystack_[0].value.as < dli::Token > ().lexeme); }
#line 1238 "lexer/parser.cpp"
    break;

  case 57: // primary: INTEGER
#line 302 "lexer/parser.y"
               { yylhs.value.as < std::shared_ptr<dli::Expression> > () = dli::make_number(std::stod(yystack_[0].value.as < dli::Token > ().lexeme)); }
#line 1244 "lexer/parser.cpp"
    break;

  case 58: // primary: REAL
#line 303 "lexer/parser.y"
               { yylhs.value.as < std::shared_ptr<dli::Expression> > () = dli::make_number(std::stod(yystack_[0].value.as < dli::Token > ().lexeme)); }
#line 1250 "lexer/parser.cpp"
    break;

  case 59: // primary: STRING
#line 304 "lexer/parser.y"
               { yylhs.value.as < std::shared_ptr<dli::Expression> > () = dli::make_string(yystack_[0].value.as < dli::Token > ().lexeme); }
#line 1256 "lexer/parser.cpp"
    break;

  case 60: // primary: KW_TRUE
#line 305 "lexer/parser.y"
               { yylhs.value.as < std::shared_ptr<dli::Expression> > () = dli::make_boolean(true); }
#line 1262 "lexer/parser.cpp"
    break;

  case 61: // primary: KW_FALSE
#line 306 "lexer/parser.y"
               { yylhs.value.as < std::shared_ptr<dli::Expression> > () = dli::make_boolean(false); }
#line 1268 "lexer/parser.cpp"
    break;

  case 62: // primary: KW_NONE
#line 307 "lexer/parser.y"
               { yylhs.value.as < std::shared_ptr<dli::Expression> > () = dli::make_none(); }
#line 1274 "lexer/parser.cpp"
    break;

  case 63: // primary: IDENTIFIER
#line 308 "lexer/parser.y"
               { yylhs.value.as < std::shared_ptr<dli::Expression> > () = dli::make_variable(yystack_[0].value.as < dli::Token > ().lexeme); }
#line 1280 "lexer/parser.cpp"
    break;

  case 64: // primary: LPAREN expression RPAREN
#line 309 "lexer/parser.y"
                             { yylhs.value.as < std::shared_ptr<dli::Expression> > () = yystack_[1].value.as < std::shared_ptr<dli::Expression> > (); }
#line 1286 "lexer/parser.cpp"
    break;

  case 65: // primary: LPAREN IDENTIFIER ASSIGN_COLON expression RPAREN
#line 310 "lexer/parser.y"
                                                     { yylhs.value.as < std::shared_ptr<dli::Expression> > () = dli::make_assign_expr(yystack_[3].value.as < dli::Token > ().lexeme, yystack_[1].value.as < std::shared_ptr<dli::Expression> > ()); }
#line 1292 "lexer/parser.cpp"
    break;

  case 66: // primary: LBRACKET expression_list_nonempty RBRACKET
#line 311 "lexer/parser.y"
                                               { yylhs.value.as < std::shared_ptr<dli::Expression> > () = dli::make_array(yystack_[1].value.as < std::vector<std::shared_ptr<dli::Expression>> > ()); }
#line 1298 "lexer/parser.cpp"
    break;

  case 67: // primary: LBRACKET RBRACKET
#line 312 "lexer/parser.y"
                      { yylhs.value.as < std::shared_ptr<dli::Expression> > () = dli::make_array(std::vector<std::shared_ptr<dli::Expression>>()); }
#line 1304 "lexer/parser.cpp"
    break;

  case 68: // primary: LBRACE tuple_field_list RBRACE
#line 313 "lexer/parser.y"
                                   { yylhs.value.as < std::shared_ptr<dli::Expression> > () = dli::make_tuple(yystack_[1].value.as < std::vector<dli::TupleField> > ()); }
#line 1310 "lexer/parser.cpp"
    break;

  case 69: // primary: LBRACE RBRACE
#line 314 "lexer/parser.y"
                  { yylhs.value.as < std::shared_ptr<dli::Expression> > () = dli::make_tuple(std::vector<dli::TupleField>()); }
#line 1316 "lexer/parser.cpp"
    break;

  case 70: // primary: LBRACE tuple_field_list KW_END
#line 315 "lexer/parser.y"
                                   { yylhs.value.as < std::shared_ptr<dli::Expression> > () = dli::make_tuple(yystack_[1].value.as < std::vector<dli::TupleField> > ()); }
#line 1322 "lexer/parser.cpp"
    break;

  case 71: // primary: LBRACE KW_END
#line 316 "lexer/parser.y"
                  { yylhs.value.as < std::shared_ptr<dli::Expression> > () = dli::make_tuple(std::vector<dli::TupleField>()); }
#line 1328 "lexer/parser.cpp"
    break;

  case 72: // primary: KW_FUNC LPAREN param_list RPAREN KW_IS statement_list KW_END
#line 318 "lexer/parser.y"
      { yylhs.value.as < std::shared_ptr<dli::Expression> > () = dli::make_function(yystack_[4].value.as < std::vector<std::string> > (), yystack_[1].value.as < std::shared_ptr<dli::StatementList> > (), false); }
#line 1334 "lexer/parser.cpp"
    break;

  case 73: // primary: KW_FUNC LPAREN param_list RPAREN ARROW statement
#line 320 "lexer/parser.y"
      { auto stmts = dli::make_stmt_list();
        stmts->push(yystack_[0].value.as < std::shared_ptr<dli::Statement> > ());
        yylhs.value.as < std::shared_ptr<dli::Expression> > () = dli::make_function(yystack_[3].value.as < std::vector<std::string> > (), stmts, true); }
#line 1342 "lexer/parser.cpp"
    break;

  case 74: // expression_list_nonempty: expression
#line 326 "lexer/parser.y"
               { yylhs.value.as < std::vector<std::shared_ptr<dli::Expression>> > () = std::vector<std::shared_ptr<dli::Expression>>(); yylhs.value.as < std::vector<std::shared_ptr<dli::Expression>> > ().push_back(yystack_[0].value.as < std::shared_ptr<dli::Expression> > ()); }
#line 1348 "lexer/parser.cpp"
    break;

  case 75: // expression_list_nonempty: expression_list_nonempty COMMA expression
#line 327 "lexer/parser.y"
                                              { yylhs.value.as < std::vector<std::shared_ptr<dli::Expression>> > () = yystack_[2].value.as < std::vector<std::shared_ptr<dli::Expression>> > (); yylhs.value.as < std::vector<std::shared_ptr<dli::Expression>> > ().push_back(yystack_[0].value.as < std::shared_ptr<dli::Expression> > ()); }
#line 1354 "lexer/parser.cpp"
    break;

  case 76: // type_name: KW_INT
#line 331 "lexer/parser.y"
              { yylhs.value.as < std::shared_ptr<dli::TypeExpr> > () = dli::make_type("int"); }
#line 1360 "lexer/parser.cpp"
    break;

  case 77: // type_name: KW_REAL
#line 332 "lexer/parser.y"
              { yylhs.value.as < std::shared_ptr<dli::TypeExpr> > () = dli::make_type("real"); }
#line 1366 "lexer/parser.cpp"
    break;

  case 78: // type_name: KW_BOOL
#line 333 "lexer/parser.y"
              { yylhs.value.as < std::shared_ptr<dli::TypeExpr> > () = dli::make_type("bool"); }
#line 1372 "lexer/parser.cpp"
    break;

  case 79: // type_name: KW_STRING
#line 334 "lexer/parser.y"
              { yylhs.value.as < std::shared_ptr<dli::TypeExpr> > () = dli::make_type("string"); }
#line 1378 "lexer/parser.cpp"
    break;

  case 80: // type_name: KW_NONE
#line 335 "lexer/parser.y"
              { yylhs.value.as < std::shared_ptr<dli::TypeExpr> > () = dli::make_type("none"); }
#line 1384 "lexer/parser.cpp"
    break;

  case 81: // type_name: KW_FUNC
#line 336 "lexer/parser.y"
              { yylhs.value.as < std::shared_ptr<dli::TypeExpr> > () = dli::make_type("func"); }
#line 1390 "lexer/parser.cpp"
    break;

  case 82: // type_name: LBRACKET RBRACKET
#line 337 "lexer/parser.y"
                      { yylhs.value.as < std::shared_ptr<dli::TypeExpr> > () = dli::make_type("[]"); }
#line 1396 "lexer/parser.cpp"
    break;

  case 83: // type_name: LBRACE RBRACE
#line 338 "lexer/parser.y"
                      { yylhs.value.as < std::shared_ptr<dli::TypeExpr> > () = dli::make_type("{}"); }
#line 1402 "lexer/parser.cpp"
    break;

  case 84: // tuple_field_list: %empty
#line 342 "lexer/parser.y"
                 { yylhs.value.as < std::vector<dli::TupleField> > () = std::vector<dli::TupleField>(); }
#line 1408 "lexer/parser.cpp"
    break;

  case 85: // tuple_field_list: tuple_field_list_nonempty
#line 343 "lexer/parser.y"
                              { yylhs.value.as < std::vector<dli::TupleField> > () = yystack_[0].value.as < std::vector<dli::TupleField> > (); }
#line 1414 "lexer/parser.cpp"
    break;

  case 86: // tuple_field_list_nonempty: tuple_field
#line 347 "lexer/parser.y"
                { yylhs.value.as < std::vector<dli::TupleField> > () = std::vector<dli::TupleField>(); yylhs.value.as < std::vector<dli::TupleField> > ().push_back(yystack_[0].value.as < dli::TupleField > ()); }
#line 1420 "lexer/parser.cpp"
    break;

  case 87: // tuple_field_list_nonempty: tuple_field_list_nonempty COMMA tuple_field
#line 348 "lexer/parser.y"
                                                { yylhs.value.as < std::vector<dli::TupleField> > () = yystack_[2].value.as < std::vector<dli::TupleField> > (); yylhs.value.as < std::vector<dli::TupleField> > ().push_back(yystack_[0].value.as < dli::TupleField > ()); }
#line 1426 "lexer/parser.cpp"
    break;

  case 88: // tuple_field: IDENTIFIER ASSIGN_COLON expression
#line 352 "lexer/parser.y"
                                       { yylhs.value.as < dli::TupleField > () = dli::TupleField(yystack_[2].value.as < dli::Token > ().lexeme, yystack_[0].value.as < std::shared_ptr<dli::Expression> > ()); }
#line 1432 "lexer/parser.cpp"
    break;

  case 89: // tuple_field: expression
#line 353 "lexer/parser.y"
               { yylhs.value.as < dli::TupleField > () = dli::TupleField("", yystack_[0].value.as < std::shared_ptr<dli::Expression> > ()); }
#line 1438 "lexer/parser.cpp"
    break;

  case 90: // param_list: %empty
#line 357 "lexer/parser.y"
                { yylhs.value.as < std::vector<std::string> > () = std::vector<std::string>(); }
#line 1444 "lexer/parser.cpp"
    break;

  case 91: // param_list: param_list_nonempty
#line 358 "lexer/parser.y"
                        { yylhs.value.as < std::vector<std::string> > () = yystack_[0].value.as < std::vector<std::string> > (); }
#line 1450 "lexer/parser.cpp"
    break;

  case 92: // param_list_nonempty: IDENTIFIER
#line 362 "lexer/parser.y"
               { yylhs.value.as < std::vector<std::string> > () = std::vector<std::string>(); yylhs.value.as < std::vector<std::string> > ().push_back(yystack_[0].value.as < dli::Token > ().lexeme); }
#line 1456 "lexer/parser.cpp"
    break;

  case 93: // param_list_nonempty: param_list_nonempty COMMA IDENTIFIER
#line 363 "lexer/parser.y"
                                         { yylhs.value.as < std::vector<std::string> > () = yystack_[2].value.as < std::vector<std::string> > (); yylhs.value.as < std::vector<std::string> > ().push_back(yystack_[0].value.as < dli::Token > ().lexeme); }
#line 1462 "lexer/parser.cpp"
    break;

  case 94: // var_decl_list: var_decl_list_nonempty
#line 367 "lexer/parser.y"
                           { yylhs.value.as < std::vector<std::pair<std::string, std::shared_ptr<dli::Expression>>> > () = yystack_[0].value.as < std::vector<std::pair<std::string, std::shared_ptr<dli::Expression>>> > (); }
#line 1468 "lexer/parser.cpp"
    break;

  case 95: // var_decl_list_nonempty: var_decl_item
#line 372 "lexer/parser.y"
      { yylhs.value.as < std::vector<std::pair<std::string, std::shared_ptr<dli::Expression>>> > () = std::vector<std::pair<std::string, std::shared_ptr<dli::Expression>>>(); 
        yylhs.value.as < std::vector<std::pair<std::string, std::shared_ptr<dli::Expression>>> > ().push_back(yystack_[0].value.as < std::pair<std::string, std::shared_ptr<dli::Expression>> > ()); }
#line 1475 "lexer/parser.cpp"
    break;

  case 96: // var_decl_list_nonempty: var_decl_list_nonempty COMMA var_decl_item
#line 375 "lexer/parser.y"
      { yylhs.value.as < std::vector<std::pair<std::string, std::shared_ptr<dli::Expression>>> > () = yystack_[2].value.as < std::vector<std::pair<std::string, std::shared_ptr<dli::Expression>>> > (); yylhs.value.as < std::vector<std::pair<std::string, std::shared_ptr<dli::Expression>>> > ().push_back(yystack_[0].value.as < std::pair<std::string, std::shared_ptr<dli::Expression>> > ()); }
#line 1481 "lexer/parser.cpp"
    break;

  case 97: // var_decl_item: IDENTIFIER ASSIGN_COLON expression
#line 380 "lexer/parser.y"
      { yylhs.value.as < std::pair<std::string, std::shared_ptr<dli::Expression>> > () = std::make_pair(yystack_[2].value.as < dli::Token > ().lexeme, yystack_[0].value.as < std::shared_ptr<dli::Expression> > ()); }
#line 1487 "lexer/parser.cpp"
    break;


#line 1491 "lexer/parser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  Parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // Parser::context.
  Parser::context::context (const Parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  Parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }






  int
  Parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char Parser::yypact_ninf_ = -34;

  const signed char Parser::yytable_ninf_ = -30;

  const short
  Parser::yypact_[] =
  {
     646,   -27,   -34,   -34,   -34,   -34,   -34,   -34,    10,   735,
     -34,   735,   735,   735,    12,   735,    16,   646,   -22,   754,
     673,   596,    33,   568,   -34,   -12,   -34,   735,    36,   -34,
     -10,   -34,   -34,   735,   816,   816,   816,    -3,   -34,    96,
     170,   -34,   104,   109,   109,    41,   109,    35,   146,    40,
     244,    98,    65,    17,   -34,    19,    70,   -34,   -34,   109,
      -8,    42,   -34,   -34,   646,   -34,   735,   704,   735,    86,
     109,   735,   102,     9,   -34,   -34,   -34,   646,   816,   816,
     816,   646,    58,   816,   816,   816,   816,   816,   816,   816,
     816,   816,   816,   816,   816,   735,    98,   646,   735,   -34,
     -34,    62,    59,   735,   -34,   -34,   735,   -34,   -34,   766,
     -34,   109,   -34,    -2,   -20,   -34,   -34,   109,    36,   -34,
     735,   190,    96,    96,    96,   -34,   -34,   -34,   -34,   -34,
     -34,   -34,    63,    66,   -34,   170,   170,   170,   170,   170,
     170,   170,   -34,   -34,   -34,   -34,   -34,   109,    71,   298,
     196,    29,   124,    48,   109,   -34,   -34,   -34,    85,   646,
     -34,   -34,   -34,   137,   -34,   646,   646,   646,   -34,   -34,
     785,   352,   646,   406,   460,   -34,   735,    92,   -34,   514,
     -34,   -34,    24,   -34,   -34,   735,    61,   785,   -34,   112,
     115
  };

  const signed char
  Parser::yydefact_[] =
  {
       2,    63,    57,    58,    59,    60,    61,    62,     0,     0,
      21,    23,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     3,     4,    12,    51,     0,     9,     8,
      94,    95,    63,     0,     0,     0,     0,     0,    25,    24,
      32,    41,    47,    22,    74,    16,    17,     0,     0,     0,
       0,    90,    63,     0,    67,     0,    63,    71,    69,    89,
       0,    85,    86,     1,     0,     6,     0,     0,     0,     0,
      10,     0,     0,     0,    50,    49,    48,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    90,     0,     0,    20,
      92,     0,    91,     0,    64,    66,     0,    70,    68,     0,
       5,    11,    53,     0,     0,    55,    56,    97,     0,    96,
       0,     0,    27,    26,    28,    13,    80,    76,    77,    78,
      79,    81,     0,     0,    40,    37,    38,    33,    34,    35,
      36,    39,    42,    43,    44,    45,    46,    75,     0,     0,
       0,     0,     0,     0,    88,    87,    54,    52,     0,     0,
      14,    82,    83,     0,    18,     0,     0,     0,    93,    65,
       0,     0,     0,     0,     0,    73,     0,     0,    15,     0,
      19,    72,     0,    29,     7,     0,     0,     0,    30,     0,
      31
  };

  const short
  Parser::yypgoto_[] =
  {
     -34,   -34,    -9,   -19,     5,   -34,   142,    99,   -33,     0,
     -34,   -15,   -34,   -34,   -34,    53,    32,   -34,   -34,   -34,
      97
  };

  const unsigned char
  Parser::yydefgoto_[] =
  {
       0,    22,    23,    24,    44,    38,    39,    40,    41,    42,
      26,    45,   134,    60,    61,    62,   101,   102,    29,    30,
      31
  };

  const short
  Parser::yytable_[] =
  {
      25,    74,    75,    76,    65,    55,   107,    27,    50,    77,
      78,    79,    80,    28,    37,    47,    43,    25,    46,    49,
      48,   120,    66,    25,    53,    51,    59,    78,    79,    80,
     157,    65,    70,    63,    81,    67,   185,    68,    73,    78,
      79,    80,    69,    72,   108,   110,   156,    78,    79,    80,
      25,    95,   113,   166,    78,    79,    80,   142,   143,   144,
     145,   146,   125,    98,    25,   104,   167,   126,   121,   105,
      71,   111,    95,   114,   187,   188,   117,    25,    78,    79,
      80,    25,    96,   127,   128,   129,   130,   131,   149,   115,
     116,    78,    79,    80,    95,   109,   169,    25,   170,   103,
     147,   100,    65,   150,   106,   118,   183,   132,   153,   133,
     151,   154,   152,   161,    59,    78,    79,    80,   162,   163,
      82,    25,    78,    79,    80,   158,   190,   168,   148,   -29,
      65,    83,    84,     0,    85,    86,    87,    88,    89,    78,
      79,    80,    78,    79,    80,   -29,   -29,   -29,   175,    25,
     171,    67,    65,    68,    65,    65,   173,   174,    69,    25,
      65,   172,   155,   179,     0,    25,    25,    25,    97,   119,
       0,    25,    25,    25,    25,   177,    78,    79,    80,    25,
       0,   182,   135,   136,   137,   138,   139,   140,   141,     0,
     186,     0,   189,     1,     2,     3,     4,     5,     6,     7,
       8,     9,     0,   159,   160,    10,    11,    12,    13,    14,
      15,    16,    17,    90,    91,    92,    93,     0,   165,    18,
     122,   123,   124,     0,     0,    94,    78,    79,    80,     0,
       0,     0,     0,     0,     0,     0,     0,    19,     0,    20,
       0,    21,     0,     0,     0,     0,    64,     1,     2,     3,
       4,     5,     6,     7,     8,     9,     0,     0,    99,    10,
      11,    12,    13,    14,    15,    16,    17,     0,     0,     0,
       0,     0,     0,    18,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    19,     0,    20,     0,    21,     0,     0,     0,     0,
      64,     1,     2,     3,     4,     5,     6,     7,     8,     9,
       0,     0,   164,    10,    11,    12,    13,    14,    15,    16,
      17,     0,     0,     0,     0,     0,     0,    18,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    19,     0,    20,     0,    21,
       0,     0,     0,     0,    64,     1,     2,     3,     4,     5,
       6,     7,     8,     9,     0,     0,   178,    10,    11,    12,
      13,    14,    15,    16,    17,     0,     0,     0,     0,     0,
       0,    18,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    19,
       0,    20,     0,    21,     0,     0,     0,     0,    64,     1,
       2,     3,     4,     5,     6,     7,     8,     9,     0,     0,
     180,    10,    11,    12,    13,    14,    15,    16,    17,     0,
       0,     0,     0,     0,     0,    18,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    19,     0,    20,     0,    21,     0,     0,
       0,     0,    64,     1,     2,     3,     4,     5,     6,     7,
       8,     9,     0,     0,   181,    10,    11,    12,    13,    14,
      15,    16,    17,     0,     0,     0,     0,     0,     0,    18,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    19,     0,    20,
       0,    21,     0,     0,     0,     0,    64,     1,     2,     3,
       4,     5,     6,     7,     8,     9,     0,     0,   184,    10,
      11,    12,    13,    14,    15,    16,    17,     0,     0,     0,
       0,     0,     0,    18,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    19,     0,    20,     0,    21,     0,     0,     0,     0,
      64,     1,     2,     3,     4,     5,     6,     7,     8,     9,
       0,     0,     0,    10,    11,    12,    13,    14,    15,    16,
      17,     0,     0,     0,     0,     0,     0,    18,     0,    56,
       2,     3,     4,     5,     6,     7,     0,    33,     0,     0,
      57,     0,     0,     0,     0,    19,     0,    20,     0,    21,
       0,     0,     0,     0,    64,    18,     0,     0,     0,    34,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    35,
      36,     0,     0,    19,     0,    20,     0,    21,    58,     1,
       2,     3,     4,     5,     6,     7,     8,     9,     0,     0,
       0,    10,    11,    12,    13,    14,    15,    16,    17,     0,
       0,     0,     0,     0,     0,    18,    32,     2,     3,     4,
       5,     6,     7,     0,    33,     0,     0,     0,     0,     0,
       0,     0,     0,    19,     0,    20,     0,    21,     0,     0,
       0,     0,    18,     0,     0,     0,    34,    32,     2,     3,
       4,     5,     6,     7,     0,    33,    35,    36,     0,     0,
      19,     0,    20,    54,    21,     0,     0,     0,     0,     0,
       0,     0,     0,    18,     0,     0,     0,    34,    32,     2,
       3,     4,     5,     6,     7,     0,    33,    35,    36,     0,
       0,    19,   112,    20,     0,    21,     0,    52,     2,     3,
       4,     5,     6,     7,    18,    33,     0,     0,    34,    56,
       2,     3,     4,     5,     6,     7,     0,    33,    35,    36,
       0,     0,    19,    18,    20,     0,    21,    34,    32,     2,
       3,     4,     5,     6,     7,    18,   176,    35,    36,    34,
       0,    19,     0,    20,     0,    21,     0,     0,     0,    35,
      36,     0,     0,    19,    18,    20,     0,    21,    34,    32,
       2,     3,     4,     5,     6,     7,     0,     0,    35,    36,
       0,     0,    19,     0,    20,     0,    21,     0,     0,     0,
       0,     0,     0,     0,     0,    18,     0,     0,     0,    34,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    35,
      36,     0,     0,    19,     0,    20,     0,    21
  };

  const short
  Parser::yycheck_[] =
  {
       0,    34,    35,    36,    23,    20,    14,    34,    17,    12,
      30,    31,    32,     3,     9,     3,    11,    17,    13,     3,
      15,    12,    34,    23,    19,    47,    21,    30,    31,    32,
      50,    50,    27,     0,    37,    47,    12,    49,    33,    30,
      31,    32,    54,    53,    52,    64,    48,    30,    31,    32,
      50,    53,    67,    24,    30,    31,    32,    90,    91,    92,
      93,    94,    81,    23,    64,    48,    37,     9,    77,    50,
      34,    66,    53,    68,    13,    14,    71,    77,    30,    31,
      32,    81,    47,    25,    26,    27,    28,    29,    97,     3,
       4,    30,    31,    32,    53,    53,    48,    97,    13,    34,
      95,     3,   121,    98,    34,     3,    14,    49,   103,    51,
      48,   106,    53,    50,   109,    30,    31,    32,    52,    48,
      24,   121,    30,    31,    32,   120,    14,     3,    96,    14,
     149,    35,    36,    -1,    38,    39,    40,    41,    42,    30,
      31,    32,    30,    31,    32,    30,    31,    32,   167,   149,
     159,    47,   171,    49,   173,   174,   165,   166,    54,   159,
     179,    24,   109,   172,    -1,   165,   166,   167,    22,    72,
      -1,   171,   172,   173,   174,   170,    30,    31,    32,   179,
      -1,   176,    83,    84,    85,    86,    87,    88,    89,    -1,
     185,    -1,   187,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    -1,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    43,    44,    45,    46,    -1,    22,    29,
      78,    79,    80,    -1,    -1,    55,    30,    31,    32,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    -1,    49,
      -1,    51,    -1,    -1,    -1,    -1,    56,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    -1,    -1,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    29,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    -1,    49,    -1,    51,    -1,    -1,    -1,    -1,
      56,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      -1,    -1,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    47,    -1,    49,    -1,    51,
      -1,    -1,    -1,    -1,    56,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    -1,    -1,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    -1,    -1,    -1,    -1,    -1,
      -1,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,
      -1,    49,    -1,    51,    -1,    -1,    -1,    -1,    56,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    -1,    -1,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    -1,
      -1,    -1,    -1,    -1,    -1,    29,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    -1,    49,    -1,    51,    -1,    -1,
      -1,    -1,    56,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    -1,    -1,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    -1,    -1,    -1,    -1,    -1,    -1,    29,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    -1,    49,
      -1,    51,    -1,    -1,    -1,    -1,    56,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    -1,    -1,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    29,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    -1,    49,    -1,    51,    -1,    -1,    -1,    -1,
      56,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      -1,    -1,    -1,    15,    16,    17,    18,    19,    20,    21,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,     3,
       4,     5,     6,     7,     8,     9,    -1,    11,    -1,    -1,
      14,    -1,    -1,    -1,    -1,    47,    -1,    49,    -1,    51,
      -1,    -1,    -1,    -1,    56,    29,    -1,    -1,    -1,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      44,    -1,    -1,    47,    -1,    49,    -1,    51,    52,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    -1,    -1,
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    -1,
      -1,    -1,    -1,    -1,    -1,    29,     3,     4,     5,     6,
       7,     8,     9,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    -1,    49,    -1,    51,    -1,    -1,
      -1,    -1,    29,    -1,    -1,    -1,    33,     3,     4,     5,
       6,     7,     8,     9,    -1,    11,    43,    44,    -1,    -1,
      47,    -1,    49,    50,    51,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    29,    -1,    -1,    -1,    33,     3,     4,
       5,     6,     7,     8,     9,    -1,    11,    43,    44,    -1,
      -1,    47,    48,    49,    -1,    51,    -1,     3,     4,     5,
       6,     7,     8,     9,    29,    11,    -1,    -1,    33,     3,
       4,     5,     6,     7,     8,     9,    -1,    11,    43,    44,
      -1,    -1,    47,    29,    49,    -1,    51,    33,     3,     4,
       5,     6,     7,     8,     9,    29,    11,    43,    44,    33,
      -1,    47,    -1,    49,    -1,    51,    -1,    -1,    -1,    43,
      44,    -1,    -1,    47,    29,    49,    -1,    51,    33,     3,
       4,     5,     6,     7,     8,     9,    -1,    -1,    43,    44,
      -1,    -1,    47,    -1,    49,    -1,    51,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    29,    -1,    -1,    -1,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      44,    -1,    -1,    47,    -1,    49,    -1,    51
  };

  const signed char
  Parser::yystos_[] =
  {
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      15,    16,    17,    18,    19,    20,    21,    22,    29,    47,
      49,    51,    59,    60,    61,    67,    68,    34,     3,    76,
      77,    78,     3,    11,    33,    43,    44,    62,    63,    64,
      65,    66,    67,    62,    62,    69,    62,     3,    62,     3,
      60,    47,     3,    62,    50,    69,     3,    14,    52,    62,
      71,    72,    73,     0,    56,    61,    34,    47,    49,    54,
      62,    34,    53,    62,    66,    66,    66,    12,    30,    31,
      32,    37,    24,    35,    36,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    55,    53,    47,    22,    23,    14,
       3,    74,    75,    34,    48,    50,    34,    14,    52,    53,
      61,    62,    48,    69,    62,     3,     4,    62,     3,    78,
      12,    60,    64,    64,    64,    61,     9,    25,    26,    27,
      28,    29,    49,    51,    70,    65,    65,    65,    65,    65,
      65,    65,    66,    66,    66,    66,    66,    62,    74,    60,
      62,    48,    53,    62,    62,    73,    48,    50,    62,    13,
      14,    50,    52,    48,    14,    22,    24,    37,     3,    48,
      13,    60,    24,    60,    60,    61,    11,    62,    14,    60,
      14,    14,    62,    14,    14,    12,    62,    13,    14,    62,
      14
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    58,    59,    59,    60,    60,    60,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    62,    62,    62,    62,    62,    63,
      63,    63,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    65,    65,    65,    65,    65,    65,    66,    66,    66,
      66,    67,    67,    67,    67,    67,    67,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    69,    69,    70,    70,    70,    70,
      70,    70,    70,    70,    71,    71,    72,    72,    73,    73,
      74,    74,    75,    75,    76,    77,    77,    78
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     0,     1,     1,     3,     2,     8,     2,     2,
       3,     3,     1,     4,     5,     7,     2,     2,     5,     7,
       3,     1,     2,     1,     1,     1,     3,     3,     3,     7,
      10,    12,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     3,     3,     3,     3,     3,     1,     2,     2,
       2,     1,     4,     3,     4,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     3,     5,     3,     2,     3,     2,
       3,     2,     7,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     2,     2,     0,     1,     1,     3,     3,     1,
       0,     1,     1,     3,     1,     1,     3,     3
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER",
  "INTEGER", "REAL", "STRING", "KW_TRUE", "KW_FALSE", "KW_NONE", "KW_VAR",
  "KW_IF", "KW_THEN", "KW_ELSE", "KW_END", "KW_EXIT", "KW_RETURN",
  "KW_PRINT", "KW_ASSERT", "KW_TEST", "KW_WHILE", "KW_FOR", "KW_LOOP",
  "KW_IN", "KW_IS", "KW_INT", "KW_REAL", "KW_BOOL", "KW_STRING", "KW_FUNC",
  "KW_AND", "KW_OR", "KW_XOR", "KW_NOT", "ASSIGN_COLON", "EQUAL",
  "EQUAL_EQUAL", "ARROW", "LESS", "LESS_EQUAL", "GREATER", "GREATER_EQUAL",
  "NOT_EQUAL_SLASH", "PLUS", "MINUS", "STAR", "SLASH", "LPAREN", "RPAREN",
  "LBRACKET", "RBRACKET", "LBRACE", "RBRACE", "COMMA", "DOT", "DOT_DOT",
  "SEMICOLON", "UMINUS", "$accept", "translation_unit", "statement_list",
  "statement", "expression", "if_expression", "relation", "term", "unary",
  "postfix", "primary", "expression_list_nonempty", "type_name",
  "tuple_field_list", "tuple_field_list_nonempty", "tuple_field",
  "param_list", "param_list_nonempty", "var_decl_list",
  "var_decl_list_nonempty", "var_decl_item", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   208,   208,   209,   213,   214,   215,   219,   222,   228,
     230,   231,   232,   233,   234,   235,   237,   238,   239,   240,
     241,   242,   243,   244,   248,   249,   250,   251,   252,   256,
     258,   260,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   277,   278,   279,   280,   281,   282,   286,   287,   288,
     289,   293,   294,   295,   296,   297,   298,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   319,   326,   327,   331,   332,   333,   334,
     335,   336,   337,   338,   342,   343,   347,   348,   352,   353,
     357,   358,   362,   363,   367,   371,   374,   379
  };

  void
  Parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  Parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 5 "lexer/parser.y"
} // dli
#line 2224 "lexer/parser.cpp"

#line 383 "lexer/parser.y"

