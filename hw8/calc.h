#ifndef CALC_H
#define CALC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function declarations
int yylex(void);
int yyparse(void);
void yyerror(const char *s);
struct symtab *symlook(char *s);

#endif
