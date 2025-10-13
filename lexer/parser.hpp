// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton interface for Bison LALR(1) parsers in C++

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


/**
 ** \file lexer/parser.hpp
 ** Define the dli::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_YY_LEXER_PARSER_HPP_INCLUDED
# define YY_YY_LEXER_PARSER_HPP_INCLUDED
// "%code requires" blocks.
#line 16 "lexer/parser.y"

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

#line 70 "lexer/parser.hpp"


# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
#endif
# include "location.hh"


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

#line 5 "lexer/parser.y"
namespace dli {
#line 206 "lexer/parser.hpp"




  /// A Bison parser.
  class Parser
  {
  public:
#ifdef YYSTYPE
# ifdef __GNUC__
#  pragma GCC message "bison: do not #define YYSTYPE in C++, use %define api.value.type"
# endif
    typedef YYSTYPE value_type;
#else
  /// A buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current parser state.
  class value_type
  {
  public:
    /// Type of *this.
    typedef value_type self_type;

    /// Empty construction.
    value_type () YY_NOEXCEPT
      : yyraw_ ()
    {}

    /// Construct and fill.
    template <typename T>
    value_type (YY_RVREF (T) t)
    {
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    value_type (const self_type&) = delete;
    /// Non copyable.
    self_type& operator= (const self_type&) = delete;
#endif

    /// Destruction, allowed only if empty.
    ~value_type () YY_NOEXCEPT
    {}

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      return *new (yyas_<T> ()) T (t);
    }
# endif

    /// Instantiate an empty \a T in here.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build ()
    {
      return emplace<T> ();
    }

    /// Instantiate a \a T in here from \a t.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build (const T& t)
    {
      return emplace<T> (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as () YY_NOEXCEPT
    {
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      return *yyas_<T> ();
    }

    /// Swap the content with \a that, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsibility.
    /// Swapping between built and (possibly) non-built is done with
    /// self_type::move ().
    template <typename T>
    void
    swap (self_type& that) YY_NOEXCEPT
    {
      std::swap (as<T> (), that.as<T> ());
    }

    /// Move the content of \a that to this.
    ///
    /// Destroys \a that.
    template <typename T>
    void
    move (self_type& that)
    {
# if 201103L <= YY_CPLUSPLUS
      emplace<T> (std::move (that.as<T> ()));
# else
      emplace<T> ();
      swap<T> (that);
# endif
      that.destroy<T> ();
    }

# if 201103L <= YY_CPLUSPLUS
    /// Move the content of \a that to this.
    template <typename T>
    void
    move (self_type&& that)
    {
      emplace<T> (std::move (that.as<T> ()));
      that.destroy<T> ();
    }
#endif

    /// Copy the content of \a that to this.
    template <typename T>
    void
    copy (const self_type& that)
    {
      emplace<T> (that.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
    }

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    value_type (const self_type&);
    /// Non copyable.
    self_type& operator= (const self_type&);
#endif

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ () YY_NOEXCEPT
    {
      void *yyp = yyraw_;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const YY_NOEXCEPT
    {
      const void *yyp = yyraw_;
      return static_cast<const T*> (yyp);
     }

    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // IDENTIFIER
      // INTEGER
      // REAL
      // STRING
      char dummy1[sizeof (dli::Token)];

      // tuple_field
      char dummy2[sizeof (dli::TupleField)];

      // var_decl_item
      char dummy3[sizeof (std::pair<std::string, std::shared_ptr<dli::Expression>>)];

      // expression
      // if_expression
      // relation
      // term
      // unary
      // postfix
      // primary
      char dummy4[sizeof (std::shared_ptr<dli::Expression>)];

      // statement
      char dummy5[sizeof (std::shared_ptr<dli::Statement>)];

      // statement_list
      char dummy6[sizeof (std::shared_ptr<dli::StatementList>)];

      // type_name
      char dummy7[sizeof (std::shared_ptr<dli::TypeExpr>)];

      // tuple_field_list
      // tuple_field_list_nonempty
      char dummy8[sizeof (std::vector<dli::TupleField>)];

      // var_decl_list
      // var_decl_list_nonempty
      char dummy9[sizeof (std::vector<std::pair<std::string, std::shared_ptr<dli::Expression>>>)];

      // expression_list_nonempty
      char dummy10[sizeof (std::vector<std::shared_ptr<dli::Expression>>)];

      // param_list
      // param_list_nonempty
      char dummy11[sizeof (std::vector<std::string>)];
    };

    /// The size of the largest semantic type.
    enum { size = sizeof (union_type) };

    /// A buffer to store semantic values.
    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me_;
      /// A buffer large enough to store any of the semantic values.
      char yyraw_[size];
    };
  };

#endif
    /// Backward compatibility (Bison 3.8).
    typedef value_type semantic_type;

    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m)
        : std::runtime_error (m)
        , location (l)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
        , location (s.location)
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;

      location_type location;
    };

    /// Token kinds.
    struct token
    {
      enum token_kind_type
      {
        YYEMPTY = -2,
    YYEOF = 0,                     // "end of file"
    YYerror = 256,                 // error
    YYUNDEF = 257,                 // "invalid token"
    IDENTIFIER = 258,              // IDENTIFIER
    INTEGER = 259,                 // INTEGER
    REAL = 260,                    // REAL
    STRING = 261,                  // STRING
    KW_TRUE = 262,                 // KW_TRUE
    KW_FALSE = 263,                // KW_FALSE
    KW_NONE = 264,                 // KW_NONE
    KW_VAR = 265,                  // KW_VAR
    KW_IF = 266,                   // KW_IF
    KW_THEN = 267,                 // KW_THEN
    KW_ELSE = 268,                 // KW_ELSE
    KW_END = 269,                  // KW_END
    KW_EXIT = 270,                 // KW_EXIT
    KW_RETURN = 271,               // KW_RETURN
    KW_PRINT = 272,                // KW_PRINT
    KW_ASSERT = 273,               // KW_ASSERT
    KW_TEST = 274,                 // KW_TEST
    KW_WHILE = 275,                // KW_WHILE
    KW_FOR = 276,                  // KW_FOR
    KW_LOOP = 277,                 // KW_LOOP
    KW_IN = 278,                   // KW_IN
    KW_IS = 279,                   // KW_IS
    KW_INT = 280,                  // KW_INT
    KW_REAL = 281,                 // KW_REAL
    KW_BOOL = 282,                 // KW_BOOL
    KW_STRING = 283,               // KW_STRING
    KW_FUNC = 284,                 // KW_FUNC
    KW_AND = 285,                  // KW_AND
    KW_OR = 286,                   // KW_OR
    KW_XOR = 287,                  // KW_XOR
    KW_NOT = 288,                  // KW_NOT
    ASSIGN_COLON = 289,            // ASSIGN_COLON
    EQUAL = 290,                   // EQUAL
    EQUAL_EQUAL = 291,             // EQUAL_EQUAL
    ARROW = 292,                   // ARROW
    LESS = 293,                    // LESS
    LESS_EQUAL = 294,              // LESS_EQUAL
    GREATER = 295,                 // GREATER
    GREATER_EQUAL = 296,           // GREATER_EQUAL
    NOT_EQUAL_SLASH = 297,         // NOT_EQUAL_SLASH
    PLUS = 298,                    // PLUS
    MINUS = 299,                   // MINUS
    STAR = 300,                    // STAR
    SLASH = 301,                   // SLASH
    LPAREN = 302,                  // LPAREN
    RPAREN = 303,                  // RPAREN
    LBRACKET = 304,                // LBRACKET
    RBRACKET = 305,                // RBRACKET
    LBRACE = 306,                  // LBRACE
    RBRACE = 307,                  // RBRACE
    COMMA = 308,                   // COMMA
    DOT = 309,                     // DOT
    DOT_DOT = 310,                 // DOT_DOT
    SEMICOLON = 311,               // SEMICOLON
    UMINUS = 312                   // UMINUS
      };
      /// Backward compatibility alias (Bison 3.6).
      typedef token_kind_type yytokentype;
    };

    /// Token kind, as returned by yylex.
    typedef token::token_kind_type token_kind_type;

    /// Backward compatibility alias (Bison 3.6).
    typedef token_kind_type token_type;

    /// Symbol kinds.
    struct symbol_kind
    {
      enum symbol_kind_type
      {
        YYNTOKENS = 58, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // "end of file"
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_IDENTIFIER = 3,                        // IDENTIFIER
        S_INTEGER = 4,                           // INTEGER
        S_REAL = 5,                              // REAL
        S_STRING = 6,                            // STRING
        S_KW_TRUE = 7,                           // KW_TRUE
        S_KW_FALSE = 8,                          // KW_FALSE
        S_KW_NONE = 9,                           // KW_NONE
        S_KW_VAR = 10,                           // KW_VAR
        S_KW_IF = 11,                            // KW_IF
        S_KW_THEN = 12,                          // KW_THEN
        S_KW_ELSE = 13,                          // KW_ELSE
        S_KW_END = 14,                           // KW_END
        S_KW_EXIT = 15,                          // KW_EXIT
        S_KW_RETURN = 16,                        // KW_RETURN
        S_KW_PRINT = 17,                         // KW_PRINT
        S_KW_ASSERT = 18,                        // KW_ASSERT
        S_KW_TEST = 19,                          // KW_TEST
        S_KW_WHILE = 20,                         // KW_WHILE
        S_KW_FOR = 21,                           // KW_FOR
        S_KW_LOOP = 22,                          // KW_LOOP
        S_KW_IN = 23,                            // KW_IN
        S_KW_IS = 24,                            // KW_IS
        S_KW_INT = 25,                           // KW_INT
        S_KW_REAL = 26,                          // KW_REAL
        S_KW_BOOL = 27,                          // KW_BOOL
        S_KW_STRING = 28,                        // KW_STRING
        S_KW_FUNC = 29,                          // KW_FUNC
        S_KW_AND = 30,                           // KW_AND
        S_KW_OR = 31,                            // KW_OR
        S_KW_XOR = 32,                           // KW_XOR
        S_KW_NOT = 33,                           // KW_NOT
        S_ASSIGN_COLON = 34,                     // ASSIGN_COLON
        S_EQUAL = 35,                            // EQUAL
        S_EQUAL_EQUAL = 36,                      // EQUAL_EQUAL
        S_ARROW = 37,                            // ARROW
        S_LESS = 38,                             // LESS
        S_LESS_EQUAL = 39,                       // LESS_EQUAL
        S_GREATER = 40,                          // GREATER
        S_GREATER_EQUAL = 41,                    // GREATER_EQUAL
        S_NOT_EQUAL_SLASH = 42,                  // NOT_EQUAL_SLASH
        S_PLUS = 43,                             // PLUS
        S_MINUS = 44,                            // MINUS
        S_STAR = 45,                             // STAR
        S_SLASH = 46,                            // SLASH
        S_LPAREN = 47,                           // LPAREN
        S_RPAREN = 48,                           // RPAREN
        S_LBRACKET = 49,                         // LBRACKET
        S_RBRACKET = 50,                         // RBRACKET
        S_LBRACE = 51,                           // LBRACE
        S_RBRACE = 52,                           // RBRACE
        S_COMMA = 53,                            // COMMA
        S_DOT = 54,                              // DOT
        S_DOT_DOT = 55,                          // DOT_DOT
        S_SEMICOLON = 56,                        // SEMICOLON
        S_UMINUS = 57,                           // UMINUS
        S_YYACCEPT = 58,                         // $accept
        S_translation_unit = 59,                 // translation_unit
        S_statement_list = 60,                   // statement_list
        S_statement = 61,                        // statement
        S_expression = 62,                       // expression
        S_if_expression = 63,                    // if_expression
        S_relation = 64,                         // relation
        S_term = 65,                             // term
        S_unary = 66,                            // unary
        S_postfix = 67,                          // postfix
        S_primary = 68,                          // primary
        S_expression_list_nonempty = 69,         // expression_list_nonempty
        S_type_name = 70,                        // type_name
        S_tuple_field_list = 71,                 // tuple_field_list
        S_tuple_field_list_nonempty = 72,        // tuple_field_list_nonempty
        S_tuple_field = 73,                      // tuple_field
        S_param_list = 74,                       // param_list
        S_param_list_nonempty = 75,              // param_list_nonempty
        S_var_decl_list = 76,                    // var_decl_list
        S_var_decl_list_nonempty = 77,           // var_decl_list_nonempty
        S_var_decl_item = 78                     // var_decl_item
      };
    };

    /// (Internal) symbol kind.
    typedef symbol_kind::symbol_kind_type symbol_kind_type;

    /// The number of tokens.
    static const symbol_kind_type YYNTOKENS = symbol_kind::YYNTOKENS;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol kind
    /// via kind ().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol () YY_NOEXCEPT
        : value ()
        , location ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that)
        : Base (std::move (that))
        , value ()
        , location (std::move (that.location))
      {
        switch (this->kind ())
    {
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_INTEGER: // INTEGER
      case symbol_kind::S_REAL: // REAL
      case symbol_kind::S_STRING: // STRING
        value.move< dli::Token > (std::move (that.value));
        break;

      case symbol_kind::S_tuple_field: // tuple_field
        value.move< dli::TupleField > (std::move (that.value));
        break;

      case symbol_kind::S_var_decl_item: // var_decl_item
        value.move< std::pair<std::string, std::shared_ptr<dli::Expression>> > (std::move (that.value));
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_if_expression: // if_expression
      case symbol_kind::S_relation: // relation
      case symbol_kind::S_term: // term
      case symbol_kind::S_unary: // unary
      case symbol_kind::S_postfix: // postfix
      case symbol_kind::S_primary: // primary
        value.move< std::shared_ptr<dli::Expression> > (std::move (that.value));
        break;

      case symbol_kind::S_statement: // statement
        value.move< std::shared_ptr<dli::Statement> > (std::move (that.value));
        break;

      case symbol_kind::S_statement_list: // statement_list
        value.move< std::shared_ptr<dli::StatementList> > (std::move (that.value));
        break;

      case symbol_kind::S_type_name: // type_name
        value.move< std::shared_ptr<dli::TypeExpr> > (std::move (that.value));
        break;

      case symbol_kind::S_tuple_field_list: // tuple_field_list
      case symbol_kind::S_tuple_field_list_nonempty: // tuple_field_list_nonempty
        value.move< std::vector<dli::TupleField> > (std::move (that.value));
        break;

      case symbol_kind::S_var_decl_list: // var_decl_list
      case symbol_kind::S_var_decl_list_nonempty: // var_decl_list_nonempty
        value.move< std::vector<std::pair<std::string, std::shared_ptr<dli::Expression>>> > (std::move (that.value));
        break;

      case symbol_kind::S_expression_list_nonempty: // expression_list_nonempty
        value.move< std::vector<std::shared_ptr<dli::Expression>> > (std::move (that.value));
        break;

      case symbol_kind::S_param_list: // param_list
      case symbol_kind::S_param_list_nonempty: // param_list_nonempty
        value.move< std::vector<std::string> > (std::move (that.value));
        break;

      default:
        break;
    }

      }
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructors for typed symbols.
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, location_type&& l)
        : Base (t)
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const location_type& l)
        : Base (t)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, dli::Token&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const dli::Token& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, dli::TupleField&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const dli::TupleField& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::pair<std::string, std::shared_ptr<dli::Expression>>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::pair<std::string, std::shared_ptr<dli::Expression>>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::shared_ptr<dli::Expression>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::shared_ptr<dli::Expression>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::shared_ptr<dli::Statement>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::shared_ptr<dli::Statement>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::shared_ptr<dli::StatementList>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::shared_ptr<dli::StatementList>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::shared_ptr<dli::TypeExpr>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::shared_ptr<dli::TypeExpr>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<dli::TupleField>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<dli::TupleField>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<std::pair<std::string, std::shared_ptr<dli::Expression>>>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<std::pair<std::string, std::shared_ptr<dli::Expression>>>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<std::shared_ptr<dli::Expression>>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<std::shared_ptr<dli::Expression>>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<std::string>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<std::string>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }



      /// Destroy contents, and record that is empty.
      void clear () YY_NOEXCEPT
      {
        // User destructor.
        symbol_kind_type yykind = this->kind ();
        basic_symbol<Base>& yysym = *this;
        (void) yysym;
        switch (yykind)
        {
       default:
          break;
        }

        // Value type destructor.
switch (yykind)
    {
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_INTEGER: // INTEGER
      case symbol_kind::S_REAL: // REAL
      case symbol_kind::S_STRING: // STRING
        value.template destroy< dli::Token > ();
        break;

      case symbol_kind::S_tuple_field: // tuple_field
        value.template destroy< dli::TupleField > ();
        break;

      case symbol_kind::S_var_decl_item: // var_decl_item
        value.template destroy< std::pair<std::string, std::shared_ptr<dli::Expression>> > ();
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_if_expression: // if_expression
      case symbol_kind::S_relation: // relation
      case symbol_kind::S_term: // term
      case symbol_kind::S_unary: // unary
      case symbol_kind::S_postfix: // postfix
      case symbol_kind::S_primary: // primary
        value.template destroy< std::shared_ptr<dli::Expression> > ();
        break;

      case symbol_kind::S_statement: // statement
        value.template destroy< std::shared_ptr<dli::Statement> > ();
        break;

      case symbol_kind::S_statement_list: // statement_list
        value.template destroy< std::shared_ptr<dli::StatementList> > ();
        break;

      case symbol_kind::S_type_name: // type_name
        value.template destroy< std::shared_ptr<dli::TypeExpr> > ();
        break;

      case symbol_kind::S_tuple_field_list: // tuple_field_list
      case symbol_kind::S_tuple_field_list_nonempty: // tuple_field_list_nonempty
        value.template destroy< std::vector<dli::TupleField> > ();
        break;

      case symbol_kind::S_var_decl_list: // var_decl_list
      case symbol_kind::S_var_decl_list_nonempty: // var_decl_list_nonempty
        value.template destroy< std::vector<std::pair<std::string, std::shared_ptr<dli::Expression>>> > ();
        break;

      case symbol_kind::S_expression_list_nonempty: // expression_list_nonempty
        value.template destroy< std::vector<std::shared_ptr<dli::Expression>> > ();
        break;

      case symbol_kind::S_param_list: // param_list
      case symbol_kind::S_param_list_nonempty: // param_list_nonempty
        value.template destroy< std::vector<std::string> > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }

      /// The user-facing name of this symbol.
      std::string name () const YY_NOEXCEPT
      {
        return Parser::symbol_name (this->kind ());
      }

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      value_type value;

      /// The location.
      location_type location;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_kind
    {
      /// The symbol kind as needed by the constructor.
      typedef token_kind_type kind_type;

      /// Default constructor.
      by_kind () YY_NOEXCEPT;

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_kind (by_kind&& that) YY_NOEXCEPT;
#endif

      /// Copy constructor.
      by_kind (const by_kind& that) YY_NOEXCEPT;

      /// Constructor from (external) token numbers.
      by_kind (kind_type t) YY_NOEXCEPT;



      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_kind& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// The symbol kind.
      /// \a S_YYEMPTY when empty.
      symbol_kind_type kind_;
    };

    /// Backward compatibility for a private implementation detail (Bison 3.6).
    typedef by_kind by_type;

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_kind>
    {
      /// Superclass.
      typedef basic_symbol<by_kind> super_type;

      /// Empty symbol.
      symbol_type () YY_NOEXCEPT {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, location_type l)
        : super_type (token_kind_type (tok), std::move (l))
#else
      symbol_type (int tok, const location_type& l)
        : super_type (token_kind_type (tok), l)
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, dli::Token v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const dli::Token& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {}
    };

    /// Build a parser object.
    Parser (dli::Lexer& lexer_yyarg);
    virtual ~Parser ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    Parser (const Parser&) = delete;
    /// Non copyable.
    Parser& operator= (const Parser&) = delete;
#endif

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

    /// The user-facing name of the symbol whose (internal) number is
    /// YYSYMBOL.  No bounds checking.
    static std::string symbol_name (symbol_kind_type yysymbol);

    // Implementation of make_symbol for each token kind.
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYEOF (location_type l)
      {
        return symbol_type (token::YYEOF, std::move (l));
      }
#else
      static
      symbol_type
      make_YYEOF (const location_type& l)
      {
        return symbol_type (token::YYEOF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYerror (location_type l)
      {
        return symbol_type (token::YYerror, std::move (l));
      }
#else
      static
      symbol_type
      make_YYerror (const location_type& l)
      {
        return symbol_type (token::YYerror, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYUNDEF (location_type l)
      {
        return symbol_type (token::YYUNDEF, std::move (l));
      }
#else
      static
      symbol_type
      make_YYUNDEF (const location_type& l)
      {
        return symbol_type (token::YYUNDEF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IDENTIFIER (dli::Token v, location_type l)
      {
        return symbol_type (token::IDENTIFIER, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_IDENTIFIER (const dli::Token& v, const location_type& l)
      {
        return symbol_type (token::IDENTIFIER, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INTEGER (dli::Token v, location_type l)
      {
        return symbol_type (token::INTEGER, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_INTEGER (const dli::Token& v, const location_type& l)
      {
        return symbol_type (token::INTEGER, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_REAL (dli::Token v, location_type l)
      {
        return symbol_type (token::REAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_REAL (const dli::Token& v, const location_type& l)
      {
        return symbol_type (token::REAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STRING (dli::Token v, location_type l)
      {
        return symbol_type (token::STRING, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_STRING (const dli::Token& v, const location_type& l)
      {
        return symbol_type (token::STRING, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_TRUE (location_type l)
      {
        return symbol_type (token::KW_TRUE, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_TRUE (const location_type& l)
      {
        return symbol_type (token::KW_TRUE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_FALSE (location_type l)
      {
        return symbol_type (token::KW_FALSE, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_FALSE (const location_type& l)
      {
        return symbol_type (token::KW_FALSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_NONE (location_type l)
      {
        return symbol_type (token::KW_NONE, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_NONE (const location_type& l)
      {
        return symbol_type (token::KW_NONE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_VAR (location_type l)
      {
        return symbol_type (token::KW_VAR, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_VAR (const location_type& l)
      {
        return symbol_type (token::KW_VAR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_IF (location_type l)
      {
        return symbol_type (token::KW_IF, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_IF (const location_type& l)
      {
        return symbol_type (token::KW_IF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_THEN (location_type l)
      {
        return symbol_type (token::KW_THEN, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_THEN (const location_type& l)
      {
        return symbol_type (token::KW_THEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_ELSE (location_type l)
      {
        return symbol_type (token::KW_ELSE, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_ELSE (const location_type& l)
      {
        return symbol_type (token::KW_ELSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_END (location_type l)
      {
        return symbol_type (token::KW_END, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_END (const location_type& l)
      {
        return symbol_type (token::KW_END, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_EXIT (location_type l)
      {
        return symbol_type (token::KW_EXIT, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_EXIT (const location_type& l)
      {
        return symbol_type (token::KW_EXIT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_RETURN (location_type l)
      {
        return symbol_type (token::KW_RETURN, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_RETURN (const location_type& l)
      {
        return symbol_type (token::KW_RETURN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_PRINT (location_type l)
      {
        return symbol_type (token::KW_PRINT, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_PRINT (const location_type& l)
      {
        return symbol_type (token::KW_PRINT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_ASSERT (location_type l)
      {
        return symbol_type (token::KW_ASSERT, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_ASSERT (const location_type& l)
      {
        return symbol_type (token::KW_ASSERT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_TEST (location_type l)
      {
        return symbol_type (token::KW_TEST, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_TEST (const location_type& l)
      {
        return symbol_type (token::KW_TEST, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_WHILE (location_type l)
      {
        return symbol_type (token::KW_WHILE, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_WHILE (const location_type& l)
      {
        return symbol_type (token::KW_WHILE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_FOR (location_type l)
      {
        return symbol_type (token::KW_FOR, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_FOR (const location_type& l)
      {
        return symbol_type (token::KW_FOR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_LOOP (location_type l)
      {
        return symbol_type (token::KW_LOOP, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_LOOP (const location_type& l)
      {
        return symbol_type (token::KW_LOOP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_IN (location_type l)
      {
        return symbol_type (token::KW_IN, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_IN (const location_type& l)
      {
        return symbol_type (token::KW_IN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_IS (location_type l)
      {
        return symbol_type (token::KW_IS, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_IS (const location_type& l)
      {
        return symbol_type (token::KW_IS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_INT (location_type l)
      {
        return symbol_type (token::KW_INT, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_INT (const location_type& l)
      {
        return symbol_type (token::KW_INT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_REAL (location_type l)
      {
        return symbol_type (token::KW_REAL, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_REAL (const location_type& l)
      {
        return symbol_type (token::KW_REAL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_BOOL (location_type l)
      {
        return symbol_type (token::KW_BOOL, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_BOOL (const location_type& l)
      {
        return symbol_type (token::KW_BOOL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_STRING (location_type l)
      {
        return symbol_type (token::KW_STRING, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_STRING (const location_type& l)
      {
        return symbol_type (token::KW_STRING, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_FUNC (location_type l)
      {
        return symbol_type (token::KW_FUNC, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_FUNC (const location_type& l)
      {
        return symbol_type (token::KW_FUNC, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_AND (location_type l)
      {
        return symbol_type (token::KW_AND, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_AND (const location_type& l)
      {
        return symbol_type (token::KW_AND, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_OR (location_type l)
      {
        return symbol_type (token::KW_OR, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_OR (const location_type& l)
      {
        return symbol_type (token::KW_OR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_XOR (location_type l)
      {
        return symbol_type (token::KW_XOR, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_XOR (const location_type& l)
      {
        return symbol_type (token::KW_XOR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KW_NOT (location_type l)
      {
        return symbol_type (token::KW_NOT, std::move (l));
      }
#else
      static
      symbol_type
      make_KW_NOT (const location_type& l)
      {
        return symbol_type (token::KW_NOT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ASSIGN_COLON (location_type l)
      {
        return symbol_type (token::ASSIGN_COLON, std::move (l));
      }
#else
      static
      symbol_type
      make_ASSIGN_COLON (const location_type& l)
      {
        return symbol_type (token::ASSIGN_COLON, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EQUAL (location_type l)
      {
        return symbol_type (token::EQUAL, std::move (l));
      }
#else
      static
      symbol_type
      make_EQUAL (const location_type& l)
      {
        return symbol_type (token::EQUAL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EQUAL_EQUAL (location_type l)
      {
        return symbol_type (token::EQUAL_EQUAL, std::move (l));
      }
#else
      static
      symbol_type
      make_EQUAL_EQUAL (const location_type& l)
      {
        return symbol_type (token::EQUAL_EQUAL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ARROW (location_type l)
      {
        return symbol_type (token::ARROW, std::move (l));
      }
#else
      static
      symbol_type
      make_ARROW (const location_type& l)
      {
        return symbol_type (token::ARROW, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LESS (location_type l)
      {
        return symbol_type (token::LESS, std::move (l));
      }
#else
      static
      symbol_type
      make_LESS (const location_type& l)
      {
        return symbol_type (token::LESS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LESS_EQUAL (location_type l)
      {
        return symbol_type (token::LESS_EQUAL, std::move (l));
      }
#else
      static
      symbol_type
      make_LESS_EQUAL (const location_type& l)
      {
        return symbol_type (token::LESS_EQUAL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GREATER (location_type l)
      {
        return symbol_type (token::GREATER, std::move (l));
      }
#else
      static
      symbol_type
      make_GREATER (const location_type& l)
      {
        return symbol_type (token::GREATER, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GREATER_EQUAL (location_type l)
      {
        return symbol_type (token::GREATER_EQUAL, std::move (l));
      }
#else
      static
      symbol_type
      make_GREATER_EQUAL (const location_type& l)
      {
        return symbol_type (token::GREATER_EQUAL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NOT_EQUAL_SLASH (location_type l)
      {
        return symbol_type (token::NOT_EQUAL_SLASH, std::move (l));
      }
#else
      static
      symbol_type
      make_NOT_EQUAL_SLASH (const location_type& l)
      {
        return symbol_type (token::NOT_EQUAL_SLASH, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PLUS (location_type l)
      {
        return symbol_type (token::PLUS, std::move (l));
      }
#else
      static
      symbol_type
      make_PLUS (const location_type& l)
      {
        return symbol_type (token::PLUS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MINUS (location_type l)
      {
        return symbol_type (token::MINUS, std::move (l));
      }
#else
      static
      symbol_type
      make_MINUS (const location_type& l)
      {
        return symbol_type (token::MINUS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STAR (location_type l)
      {
        return symbol_type (token::STAR, std::move (l));
      }
#else
      static
      symbol_type
      make_STAR (const location_type& l)
      {
        return symbol_type (token::STAR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SLASH (location_type l)
      {
        return symbol_type (token::SLASH, std::move (l));
      }
#else
      static
      symbol_type
      make_SLASH (const location_type& l)
      {
        return symbol_type (token::SLASH, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LPAREN (location_type l)
      {
        return symbol_type (token::LPAREN, std::move (l));
      }
#else
      static
      symbol_type
      make_LPAREN (const location_type& l)
      {
        return symbol_type (token::LPAREN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RPAREN (location_type l)
      {
        return symbol_type (token::RPAREN, std::move (l));
      }
#else
      static
      symbol_type
      make_RPAREN (const location_type& l)
      {
        return symbol_type (token::RPAREN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LBRACKET (location_type l)
      {
        return symbol_type (token::LBRACKET, std::move (l));
      }
#else
      static
      symbol_type
      make_LBRACKET (const location_type& l)
      {
        return symbol_type (token::LBRACKET, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RBRACKET (location_type l)
      {
        return symbol_type (token::RBRACKET, std::move (l));
      }
#else
      static
      symbol_type
      make_RBRACKET (const location_type& l)
      {
        return symbol_type (token::RBRACKET, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LBRACE (location_type l)
      {
        return symbol_type (token::LBRACE, std::move (l));
      }
#else
      static
      symbol_type
      make_LBRACE (const location_type& l)
      {
        return symbol_type (token::LBRACE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RBRACE (location_type l)
      {
        return symbol_type (token::RBRACE, std::move (l));
      }
#else
      static
      symbol_type
      make_RBRACE (const location_type& l)
      {
        return symbol_type (token::RBRACE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COMMA (location_type l)
      {
        return symbol_type (token::COMMA, std::move (l));
      }
#else
      static
      symbol_type
      make_COMMA (const location_type& l)
      {
        return symbol_type (token::COMMA, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DOT (location_type l)
      {
        return symbol_type (token::DOT, std::move (l));
      }
#else
      static
      symbol_type
      make_DOT (const location_type& l)
      {
        return symbol_type (token::DOT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DOT_DOT (location_type l)
      {
        return symbol_type (token::DOT_DOT, std::move (l));
      }
#else
      static
      symbol_type
      make_DOT_DOT (const location_type& l)
      {
        return symbol_type (token::DOT_DOT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SEMICOLON (location_type l)
      {
        return symbol_type (token::SEMICOLON, std::move (l));
      }
#else
      static
      symbol_type
      make_SEMICOLON (const location_type& l)
      {
        return symbol_type (token::SEMICOLON, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UMINUS (location_type l)
      {
        return symbol_type (token::UMINUS, std::move (l));
      }
#else
      static
      symbol_type
      make_UMINUS (const location_type& l)
      {
        return symbol_type (token::UMINUS, l);
      }
#endif


    class context
    {
    public:
      context (const Parser& yyparser, const symbol_type& yyla);
      const symbol_type& lookahead () const YY_NOEXCEPT { return yyla_; }
      symbol_kind_type token () const YY_NOEXCEPT { return yyla_.kind (); }
      const location_type& location () const YY_NOEXCEPT { return yyla_.location; }

      /// Put in YYARG at most YYARGN of the expected tokens, and return the
      /// number of tokens stored in YYARG.  If YYARG is null, return the
      /// number of expected tokens (guaranteed to be less than YYNTOKENS).
      int expected_tokens (symbol_kind_type yyarg[], int yyargn) const;

    private:
      const Parser& yyparser_;
      const symbol_type& yyla_;
    };

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    Parser (const Parser&);
    /// Non copyable.
    Parser& operator= (const Parser&);
#endif


    /// Stored state numbers (used for stacks).
    typedef unsigned char state_type;

    /// The arguments of the error message.
    int yy_syntax_error_arguments_ (const context& yyctx,
                                    symbol_kind_type yyarg[], int yyargn) const;

    /// Generate an error message.
    /// \param yyctx     the context in which the error occurred.
    virtual std::string yysyntax_error_ (const context& yyctx) const;
    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT;

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT;

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token kind \a t to a symbol kind.
    /// In theory \a t should be a token_kind_type, but character literals
    /// are valid, yet not members of the token_kind_type enum.
    static symbol_kind_type yytranslate_ (int t) YY_NOEXCEPT;

    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *yystr);

    /// For a symbol, its name in clear.
    static const char* const yytname_[];


    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const short yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const signed char yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const short yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const unsigned char yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const short yytable_[];

    static const short yycheck_[];

    // YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
    // state STATE-NUM.
    static const signed char yystos_[];

    // YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.
    static const signed char yyr1_[];

    // YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.
    static const signed char yyr2_[];


#if YYDEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r) const;
    /// Print the state stack on the debug stream.
    virtual void yy_stack_print_ () const;

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol kind, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state () YY_NOEXCEPT;

      /// The symbol kind as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_state& that);

      /// The symbol kind (corresponding to \a state).
      /// \a symbol_kind::S_YYEMPTY when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      /// We use the initial state, as it does not have a value.
      enum { empty_state = 0 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);

      /// Assignment, needed by push_back by other implementations.
      /// Needed by some other old implementations.
      stack_symbol_type& operator= (const stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::iterator iterator;
      typedef typename S::const_iterator const_iterator;
      typedef typename S::size_type size_type;
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200) YY_NOEXCEPT
        : seq_ (n)
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Non copyable.
      stack (const stack&) = delete;
      /// Non copyable.
      stack& operator= (const stack&) = delete;
#endif

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (index_type i) const
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (index_type i)
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (std::ptrdiff_t n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      index_type
      size () const YY_NOEXCEPT
      {
        return index_type (seq_.size ());
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.begin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.end ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, index_type range) YY_NOEXCEPT
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (index_type i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        index_type range_;
      };

    private:
#if YY_CPLUSPLUS < 201103L
      /// Non copyable.
      stack (const stack&);
      /// Non copyable.
      stack& operator= (const stack&);
#endif
      /// The wrapped container.
      S seq_;
    };


    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1) YY_NOEXCEPT;

    /// Constants.
    enum
    {
      yylast_ = 867,     ///< Last index in yytable_.
      yynnts_ = 21,  ///< Number of nonterminal symbols.
      yyfinal_ = 63 ///< Termination state number.
    };


    // User arguments.
    dli::Lexer& lexer;

  };

  inline
  Parser::symbol_kind_type
  Parser::yytranslate_ (int t) YY_NOEXCEPT
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57
    };
    // Last valid token kind.
    const int code_max = 312;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

  // basic_symbol.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->kind ())
    {
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_INTEGER: // INTEGER
      case symbol_kind::S_REAL: // REAL
      case symbol_kind::S_STRING: // STRING
        value.copy< dli::Token > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_tuple_field: // tuple_field
        value.copy< dli::TupleField > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_var_decl_item: // var_decl_item
        value.copy< std::pair<std::string, std::shared_ptr<dli::Expression>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_if_expression: // if_expression
      case symbol_kind::S_relation: // relation
      case symbol_kind::S_term: // term
      case symbol_kind::S_unary: // unary
      case symbol_kind::S_postfix: // postfix
      case symbol_kind::S_primary: // primary
        value.copy< std::shared_ptr<dli::Expression> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement: // statement
        value.copy< std::shared_ptr<dli::Statement> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement_list: // statement_list
        value.copy< std::shared_ptr<dli::StatementList> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_name: // type_name
        value.copy< std::shared_ptr<dli::TypeExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_tuple_field_list: // tuple_field_list
      case symbol_kind::S_tuple_field_list_nonempty: // tuple_field_list_nonempty
        value.copy< std::vector<dli::TupleField> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_var_decl_list: // var_decl_list
      case symbol_kind::S_var_decl_list_nonempty: // var_decl_list_nonempty
        value.copy< std::vector<std::pair<std::string, std::shared_ptr<dli::Expression>>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expression_list_nonempty: // expression_list_nonempty
        value.copy< std::vector<std::shared_ptr<dli::Expression>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_param_list: // param_list
      case symbol_kind::S_param_list_nonempty: // param_list_nonempty
        value.copy< std::vector<std::string> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }




  template <typename Base>
  Parser::symbol_kind_type
  Parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_INTEGER: // INTEGER
      case symbol_kind::S_REAL: // REAL
      case symbol_kind::S_STRING: // STRING
        value.move< dli::Token > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_tuple_field: // tuple_field
        value.move< dli::TupleField > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_var_decl_item: // var_decl_item
        value.move< std::pair<std::string, std::shared_ptr<dli::Expression>> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_if_expression: // if_expression
      case symbol_kind::S_relation: // relation
      case symbol_kind::S_term: // term
      case symbol_kind::S_unary: // unary
      case symbol_kind::S_postfix: // postfix
      case symbol_kind::S_primary: // primary
        value.move< std::shared_ptr<dli::Expression> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_statement: // statement
        value.move< std::shared_ptr<dli::Statement> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_statement_list: // statement_list
        value.move< std::shared_ptr<dli::StatementList> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_type_name: // type_name
        value.move< std::shared_ptr<dli::TypeExpr> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_tuple_field_list: // tuple_field_list
      case symbol_kind::S_tuple_field_list_nonempty: // tuple_field_list_nonempty
        value.move< std::vector<dli::TupleField> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_var_decl_list: // var_decl_list
      case symbol_kind::S_var_decl_list_nonempty: // var_decl_list_nonempty
        value.move< std::vector<std::pair<std::string, std::shared_ptr<dli::Expression>>> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_expression_list_nonempty: // expression_list_nonempty
        value.move< std::vector<std::shared_ptr<dli::Expression>> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_param_list: // param_list
      case symbol_kind::S_param_list_nonempty: // param_list_nonempty
        value.move< std::vector<std::string> > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_kind.
  inline
  Parser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  inline
  Parser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  inline
  Parser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  inline
  Parser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  inline
  void
  Parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  inline
  void
  Parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  inline
  Parser::symbol_kind_type
  Parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  inline
  Parser::symbol_kind_type
  Parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


#line 5 "lexer/parser.y"
} // dli
#line 2632 "lexer/parser.hpp"


// "%code provides" blocks.
#line 125 "lexer/parser.y"

    // Provide Parser::error implementation after class declaration
    inline void dli::Parser::error(const dli::Parser::location_type& loc, const std::string& msg) {
        std::cerr << loc << ": " << msg << '\n';
    }

#line 2643 "lexer/parser.hpp"


#endif // !YY_YY_LEXER_PARSER_HPP_INCLUDED
