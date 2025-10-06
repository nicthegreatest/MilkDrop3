#ifndef YY_Y_TAB_H_INCLUDED
# define YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    VALUE = 258,
    IDENTIFIER = 259,
	TOKEN_SHL = 260,
	TOKEN_SHR = 261,
	TOKEN_LTE = 262,
	TOKEN_GTE = 263,
	TOKEN_EQ = 264,
	TOKEN_EQ_EXACT = 265,
	TOKEN_NE = 266,
	TOKEN_NE_EXACT = 267,
	TOKEN_LOGICAL_AND = 268,
	TOKEN_LOGICAL_OR = 269,
	TOKEN_ADD_OP = 270,
	TOKEN_SUB_OP = 271,
	TOKEN_MOD_OP = 272,
	TOKEN_OR_OP = 273,
	TOKEN_AND_OP = 274,
	TOKEN_XOR_OP = 275,
	TOKEN_DIV_OP = 276,
	TOKEN_MUL_OP = 277,
	TOKEN_POW_OP = 278,
	STRING_LITERAL = 279,
	STRING_IDENTIFIER = 280
  };
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
  opcodeRec* value;
  eelStringSegmentRec* string;
} YYSTYPE;
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

int yyparse (void *ctx);

#endif /* !YY_Y_TAB_H_INCLUDED  */