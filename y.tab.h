/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    BOOL = 258,
    START = 259,
    CONST = 260,
    END = 261,
    IF = 262,
    THEN = 263,
    ELSE = 264,
    ENDIF = 265,
    WHILE = 266,
    DO = 267,
    ENDWHILE = 268,
    FOR = 269,
    STARTFOR = 270,
    ENDFOR = 271,
    CLASS = 272,
    AND = 273,
    OR = 274,
    EQ = 275,
    ASSIGN = 276,
    NOT = 277,
    NE = 278,
    LT = 279,
    LE = 280,
    GT = 281,
    GE = 282,
    PLUS = 283,
    MINUS = 284,
    MULTIP = 285,
    DIVIDE = 286,
    TIP = 287,
    ID = 288,
    INTEGER = 289,
    CHAR = 290,
    FLOAT = 291,
    STRING = 292,
    NR_INT = 293,
    PRINT = 294,
    SPECIAL_PRINT = 295,
    TXT1 = 296,
    TXT2 = 297,
    NUME_CLASA = 298
  };
#endif
/* Tokens.  */
#define BOOL 258
#define START 259
#define CONST 260
#define END 261
#define IF 262
#define THEN 263
#define ELSE 264
#define ENDIF 265
#define WHILE 266
#define DO 267
#define ENDWHILE 268
#define FOR 269
#define STARTFOR 270
#define ENDFOR 271
#define CLASS 272
#define AND 273
#define OR 274
#define EQ 275
#define ASSIGN 276
#define NOT 277
#define NE 278
#define LT 279
#define LE 280
#define GT 281
#define GE 282
#define PLUS 283
#define MINUS 284
#define MULTIP 285
#define DIVIDE 286
#define TIP 287
#define ID 288
#define INTEGER 289
#define CHAR 290
#define FLOAT 291
#define STRING 292
#define NR_INT 293
#define PRINT 294
#define SPECIAL_PRINT 295
#define TXT1 296
#define TXT2 297
#define NUME_CLASA 298

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 938 "proiect.y"

    int num;
    float fl;
    char* str;
	_Bool bl;
	struct expp
	{
		float val;
		char* exp;
	}expres;

#line 155 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
