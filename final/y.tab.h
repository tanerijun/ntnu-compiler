/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     BEGIN_TOKEN = 258,
     END_TOKEN = 259,
     DECLARE_TOKEN = 260,
     AS_TOKEN = 261,
     INTEGER_TOKEN = 262,
     REAL_TOKEN = 263,
     PROGRAM_TOKEN = 264,
     IF_TOKEN = 265,
     THEN_TOKEN = 266,
     ELSE_TOKEN = 267,
     ENDIF_TOKEN = 268,
     FOR_TOKEN = 269,
     TO_TOKEN = 270,
     DOWNTO_TOKEN = 271,
     ENDFOR_TOKEN = 272,
     STEP_TOKEN = 273,
     WHILE_TOKEN = 274,
     ENDWHILE_TOKEN = 275,
     PRINT_TOKEN = 276,
     WRITE_TOKEN = 277,
     ASSIGN_OP = 278,
     GE_OP = 279,
     LE_OP = 280,
     EQ_OP = 281,
     NE_OP = 282,
     INT_LITERAL = 283,
     FLOAT_LITERAL = 284,
     ID = 285,
     UMINUS = 286
   };
#endif
/* Tokens.  */
#define BEGIN_TOKEN 258
#define END_TOKEN 259
#define DECLARE_TOKEN 260
#define AS_TOKEN 261
#define INTEGER_TOKEN 262
#define REAL_TOKEN 263
#define PROGRAM_TOKEN 264
#define IF_TOKEN 265
#define THEN_TOKEN 266
#define ELSE_TOKEN 267
#define ENDIF_TOKEN 268
#define FOR_TOKEN 269
#define TO_TOKEN 270
#define DOWNTO_TOKEN 271
#define ENDFOR_TOKEN 272
#define STEP_TOKEN 273
#define WHILE_TOKEN 274
#define ENDWHILE_TOKEN 275
#define PRINT_TOKEN 276
#define WRITE_TOKEN 277
#define ASSIGN_OP 278
#define GE_OP 279
#define LE_OP 280
#define EQ_OP 281
#define NE_OP 282
#define INT_LITERAL 283
#define FLOAT_LITERAL 284
#define ID 285
#define UMINUS 286




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 36 "microex.y"
{
    int ival;
    float fval;
    struct symtab *symp;
    struct {
        struct symtab *place;
        int type;
    } expr;
}
/* Line 1529 of yacc.c.  */
#line 121 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

