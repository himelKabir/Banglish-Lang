
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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

/* "%code requires" blocks.  */

/* Line 1676 of yacc.c  */
#line 2 "test.y"

typedef struct { int *vals; int count; } IntList;



/* Line 1676 of yacc.c  */
#line 46 "test.tab.h"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     MYTYPE = 258,
     SHOW = 259,
     SWAP = 260,
     FUNCTION = 261,
     RETURN = 262,
     STRLEN = 263,
     CONCAT = 264,
     INTTYPE = 265,
     FLOATTYPE = 266,
     CHARTYPE = 267,
     STRINGTYPE = 268,
     IF = 269,
     ELSE = 270,
     WHILE = 271,
     ARRAYTYPE = 272,
     IDENTIFIER = 273,
     STRING_LITERAL = 274,
     CHAR_LITERAL = 275,
     NUMBER = 276,
     PLUS = 277,
     MINUS = 278,
     TIMES = 279,
     DIVIDE = 280,
     AND = 281,
     OR = 282,
     NOT = 283,
     BAND = 284,
     BOR = 285,
     BXOR = 286,
     BNOT = 287,
     LSHIFT = 288,
     RSHIFT = 289,
     EQ = 290,
     NE = 291,
     GE = 292,
     LE = 293,
     UMINUS = 294
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 87 "test.y"

    int num;
    char* str;
    struct Statement* stmt;
    struct Expression* expr; // Added to hold expression trees
    IntList* ilist;



/* Line 1676 of yacc.c  */
#line 112 "test.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


