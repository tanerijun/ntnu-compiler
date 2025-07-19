## Compiler HW9

Name: 陳偉俊

Student ID: 61347090S

## Code

Lex:

```l
%{
#include "y.tab.h"
#include "microex.h"
#include <stdio.h>
#include <string.h>

int column = 1;
extern int yylineno;

void update_column() {
    column += yyleng;
}

void print_token(const char* token_type, const char* value) {
    printf("LEX: Found %s token: \"%s\" at line %d, column %d\n",
           token_type, value, yylineno, column);
}
%}

%option yylineno
%option noyywrap

%%
[Pp][Rr][Oo][Gg][Rr][Aa][Mm]   { print_token("PROGRAM", yytext); update_column(); return PROGRAM_TOKEN; }
[Bb][Ee][Gg][Ii][Nn]     { print_token("BEGIN", yytext); update_column(); return BEGIN_TOKEN; }
[Ee][Nn][Dd]             { print_token("END", yytext); update_column(); return END_TOKEN; }
[Dd][Ee][Cc][Ll][Aa][Rr][Ee] { print_token("DECLARE", yytext); update_column(); return DECLARE_TOKEN; }
[Aa][Ss]                 { print_token("AS", yytext); update_column(); return AS_TOKEN; }
[Ii][Nn][Tt][Ee][Gg][Ee][Rr] { print_token("INTEGER_TYPE", yytext); update_column(); return INTEGER_TOKEN; }
[Rr][Ee][Aa][Ll]         { print_token("REAL_TYPE", yytext); update_column(); return REAL_TOKEN; }

[,;]                     { print_token("PUNCTUATION", yytext); update_column(); return yytext[0]; }
[\(\)\[\]]               { print_token("BRACKET", yytext); update_column(); return yytext[0]; }

[0-9]+                   {
                           print_token("INTEGER", yytext);
                           update_column();
                           yylval.ival = atoi(yytext);
                           return INT_LITERAL;
                         }

[A-Za-z][A-Za-z0-9]*     {
                           print_token("IDENTIFIER", yytext);
                           update_column();
                           yylval.symp = symlook(yytext);
                           return ID;
                         }

"%%".*                   { /* Comments are ignored */ update_column(); }

[ \t]+                   { update_column(); /* ignore whitespace */ }
\n                       { column = 1; /* Reset column on newline */ }

.                        {
                           printf("LEX: Error - Unrecognized character: '%c' at line %d, column %d\n",
                                  yytext[0], yylineno, column);
                           update_column();
                           return yytext[0];
                         }
%%
```

Yacc:

```y
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "microex.h"

void yyerror(const char *s);
int yylex(void);
extern int yylineno;

struct symtab symtab[NSYMS];
int symtab_count = 0;

// Temp storage for declaration processing
struct {
    struct symtab *ids[100];
    int count;
    int type;  // 0=INTEGER, 1=REAL
} current_decl;
%}

%union {
    int ival;
    struct symtab *symp;
}

%token PROGRAM_TOKEN BEGIN_TOKEN END_TOKEN DECLARE_TOKEN AS_TOKEN INTEGER_TOKEN REAL_TOKEN
%token <ival> INT_LITERAL
%token <symp> ID

%type <ival> type
%start program

%%

program:
    program_header BEGIN_TOKEN stmt_list END_TOKEN
    { printf("YACC: Reduced program_header BEGIN stmt_list END to program\n"); }
    ;

program_header:
    PROGRAM_TOKEN ID
    {
        printf("YACC: Reduced PROGRAM ID to program_header\n");
        printf("Target code: START %s\n", $2->name);
    }
    ;

stmt_list:
    stmt
    { printf("YACC: Reduced stmt to stmt_list\n"); }
    | stmt_list stmt
    { printf("YACC: Reduced stmt_list stmt to stmt_list\n"); }
    ;

stmt:
    declaration_stmt
    { printf("YACC: Reduced declaration_stmt to stmt\n"); }
    ;

declaration_stmt:
    DECLARE_TOKEN id_list AS_TOKEN type ';'
    {
        printf("YACC: Reduced DECLARE id_list AS type ';' to declaration_stmt\n");
        printf("YACC: Processing declaration with type: %s\n", $4 == 0 ? "INTEGER" : "REAL");

        // Process the declaration by setting the type for all IDs in the list
        for(int i = 0; i < current_decl.count; i++) {
            current_decl.ids[i]->type = $4;

            if (current_decl.ids[i]->isArray) {
                printf("Target code: Declare %s, %s_array,%d\n",
                      current_decl.ids[i]->name,
                      $4 == 0 ? "Integer" : "Float",
                      current_decl.ids[i]->size);
            } else {
                printf("Target code: Declare %s, %s\n",
                      current_decl.ids[i]->name,
                      $4 == 0 ? "Integer" : "Float");
            }
        }

        // Reset for next declaration
        current_decl.count = 0;
    }
    ;

id_list:
    id_decl
    {
        printf("YACC: Reduced id_decl to id_list\n");
    }
    | id_list ',' id_decl
    {
        printf("YACC: Reduced id_list ',' id_decl to id_list\n");
    }
    ;

id_decl:
    ID
    {
        printf("YACC: Reduced ID to id_decl (scalar: %s)\n", $1->name);
        $1->isArray = 0;
        $1->size = 0;
        current_decl.ids[current_decl.count++] = $1;
    }
    | ID '(' INT_LITERAL ')'
    {
        printf("YACC: Reduced ID '(' INT_LITERAL ')' to id_decl (array: %s[%d])\n", $1->name, $3);
        $1->isArray = 1;
        $1->size = $3;
        current_decl.ids[current_decl.count++] = $1;
    }
    ;

type:
    INTEGER_TOKEN
    {
        printf("YACC: Reduced INTEGER_TOKEN to type\n");
        $$ = 0;
    }
    | REAL_TOKEN
    {
        printf("YACC: Reduced REAL_TOKEN to type\n");
        $$ = 1;
    }
    ;

%%

struct symtab *symlook(char *s) {
    for(int i = 0; i < symtab_count; i++) {
        if(strcmp(symtab[i].name, s) == 0) {
            return &symtab[i];
        }
    }

    // Not found, enter a new symbol
    if(symtab_count >= NSYMS) {
        fprintf(stderr, "Symbol table full, too many symbols\n");
        exit(1);
    }

    symtab[symtab_count].name = strdup(s);
    return &symtab[symtab_count++];
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s at line %d\n", s, yylineno);
}

int main() {
    // Initialize symbol table
    memset(symtab, 0, sizeof(symtab));
    symtab_count = 0;

    // Declaration tracking
    current_decl.count = 0;

    printf("Starting MicroEx parser...\n\n");
    int result = yyparse();

    if(result == 0) {
        printf("\nParsing completed successfully.\n");
    } else {
        printf("\nParsing failed.\n");
    }

    return result;
}
```

microex.h (declared here for tidiness):

```h
#ifndef MICROEX_H
#define MICROEX_H

#define NSYMS 100 /* maximum number of symbols */

struct symtab {
    char *name;
    int type;      // 0=INTEGER, 1=REAL
    int isArray;   // 0=scalar, 1=array
    int size;      // array size if isArray=1
};

extern struct symtab symtab[NSYMS];
extern int symtab_count;

struct symtab *symlook(char *s);

#endif
```

## Input File (Test file):

The inconsistent casing, indentations, and spacing are intentional.

```
%%the beginning of an test data for Micro/Ex

Program Mypro

Begin

 declare A,I as integer;

 Declare B,C,D,size, LLL(100)   as Real;


end
```

## Trace Result:

```
hw9 % ./microex < input.txt
Starting MicroEx parser...

LEX: Found PROGRAM token: "Program" at line 3, column 1
LEX: Found IDENTIFIER token: "Mypro" at line 3, column 9
YACC: Reduced PROGRAM ID to program_header
Target code: START Mypro
LEX: Found BEGIN token: "Begin" at line 5, column 1
LEX: Found DECLARE token: "declare" at line 7, column 2
LEX: Found IDENTIFIER token: "A" at line 7, column 10
LEX: Found PUNCTUATION token: "," at line 7, column 11
YACC: Reduced ID to id_decl (scalar: A)
YACC: Reduced id_decl to id_list
LEX: Found IDENTIFIER token: "I" at line 7, column 12
LEX: Found AS token: "as" at line 7, column 14
YACC: Reduced ID to id_decl (scalar: I)
YACC: Reduced id_list ',' id_decl to id_list
LEX: Found INTEGER_TYPE token: "integer" at line 7, column 17
YACC: Reduced INTEGER_TOKEN to type
LEX: Found PUNCTUATION token: ";" at line 7, column 24
YACC: Reduced DECLARE id_list AS type ';' to declaration_stmt
YACC: Processing declaration with type: INTEGER
Target code: Declare A, Integer
Target code: Declare I, Integer
YACC: Reduced declaration_stmt to stmt
YACC: Reduced stmt to stmt_list
LEX: Found DECLARE token: "Declare" at line 9, column 2
LEX: Found IDENTIFIER token: "B" at line 9, column 10
LEX: Found PUNCTUATION token: "," at line 9, column 11
YACC: Reduced ID to id_decl (scalar: B)
YACC: Reduced id_decl to id_list
LEX: Found IDENTIFIER token: "C" at line 9, column 12
LEX: Found PUNCTUATION token: "," at line 9, column 13
YACC: Reduced ID to id_decl (scalar: C)
YACC: Reduced id_list ',' id_decl to id_list
LEX: Found IDENTIFIER token: "D" at line 9, column 14
LEX: Found PUNCTUATION token: "," at line 9, column 15
YACC: Reduced ID to id_decl (scalar: D)
YACC: Reduced id_list ',' id_decl to id_list
LEX: Found IDENTIFIER token: "size" at line 9, column 16
LEX: Found PUNCTUATION token: "," at line 9, column 20
YACC: Reduced ID to id_decl (scalar: size)
YACC: Reduced id_list ',' id_decl to id_list
LEX: Found IDENTIFIER token: "LLL" at line 9, column 22
LEX: Found BRACKET token: "(" at line 9, column 25
LEX: Found INTEGER token: "100" at line 9, column 26
LEX: Found BRACKET token: ")" at line 9, column 29
YACC: Reduced ID '(' INT_LITERAL ')' to id_decl (array: LLL[100])
YACC: Reduced id_list ',' id_decl to id_list
LEX: Found AS token: "as" at line 9, column 33
LEX: Found REAL_TYPE token: "Real" at line 9, column 36
YACC: Reduced REAL_TOKEN to type
LEX: Found PUNCTUATION token: ";" at line 9, column 40
YACC: Reduced DECLARE id_list AS type ';' to declaration_stmt
YACC: Processing declaration with type: REAL
Target code: Declare B, Float
Target code: Declare C, Float
Target code: Declare D, Float
Target code: Declare size, Float
Target code: Declare LLL, Float_array,100
YACC: Reduced declaration_stmt to stmt
YACC: Reduced stmt_list stmt to stmt_list
LEX: Found END token: "end" at line 12, column 1
YACC: Reduced program_header BEGIN stmt_list END to program

Parsing completed successfully.
```

## Generated Assembly Code:

```
START Mypro
Declare A, Integer
Declare I, Integer
Declare B, Float
Declare C, Float
Declare D, Float
Declare size, Float
Declare LLL, Float_array,100
```
