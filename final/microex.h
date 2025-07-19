#ifndef MICROEX_H
#define MICROEX_H

#include <stdio.h> // For FILE* if yyin is to be known here (though typically extern in .y)

#define NSYMS 100 /* maximum number of symbols */

// data type definitions
#define TYPE_INT 0
#define TYPE_FLOAT 1

// symbol table entry
struct symtab {
    char *name;
    int type;      // 0=INTEGER, 1=REAL
    int isArray;   // 0=scalar, 1=array
    int size;      // array size if applicable
    int is_declared; // 0=not_declared, 1=declared
};

// temporary vars for code generation
extern int temp_counter;
extern int label_counter;

// for keeping track of nested control structures
struct label_stack {
    int begin_label;
    int end_label;
    char *var_name;    // For FOR loops, store loop variable name
    char *end_expr;    // For FOR loops, store end expression
    char *step_expr;   // For FOR loops, store step expression
    int is_downto;     // 1 for counting down, 0 for counting up
};

extern struct label_stack if_stack[20];
extern int if_stack_ptr;

extern struct label_stack for_stack[20];
extern int for_stack_ptr;

extern struct symtab symtab[NSYMS];
extern int symtab_count;

struct symtab *symlook(char *s);
char *new_temp(int type);
int new_label();

int yylex(void);
extern FILE *yyin;

#endif
