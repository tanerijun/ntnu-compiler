%{
#include <stdio.h>
int yylex(void);
void yyerror(char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
%}

%token NAME NUMBER
%%
statement:  NAME '=' expression     { printf("YACC (rule 1): reduced to statement (NAME = expression)\n"); }
	|	expression     {
            printf("YACC (rule 2): reduced to statement (expression)\n");
            printf("= %d\n", $1);
        }
	;

expression:	expression '+' NUMBER	{
            $$ = $1 + $3;
            printf("YACC (rule 3): reduced expression + NUMBER to %d\n", $$);
        }
	|	expression '-' NUMBER	{
            $$ = $1 - $3;
            printf("YACC (rule 4): reduced expression - NUMBER to %d\n", $$);
        }
	|	NUMBER			{
            $$ = $1;
            printf("YACC (rule 5): reduced NUMBER to expression: %d\n", $$);
        }
	;
