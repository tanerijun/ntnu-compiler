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

        for(int i = 0; i < current_decl.count; i++) {
            current_decl.ids[i]->type = $4;

            // Output assembly code
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
