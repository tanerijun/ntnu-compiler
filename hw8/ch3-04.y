%{
#include "calc.h"
#include "ch3hdr.h"
#include <string.h>
%}

%union {
	double dval;
	struct symtab *symp;
}
%token <symp> NAME
%token <dval> NUMBER
%left '-' '+'
%left '*' '/'
%nonassoc UMINUS

%type <dval> expression
%%
statement_list:	statement '\n'
			{ printf("YACC: Reduced statement '\\n' to statement_list\n"); }
	|	statement_list statement '\n'
			{ printf("YACC: Reduced statement_list statement '\\n' to statement_list\n"); }
	;

statement:	NAME '=' expression
			{
				$1->value = $3;
				printf("YACC: Reduced NAME = expression to statement\n");
			}
	|	expression
			{
				printf("= %g\n", $1);
				printf("YACC: Reduced expression to statement\n");
			}
	;

expression:	expression '+' expression
			{
				$$ = $1 + $3;
				printf("YACC: Reduced expression + expression to expression (=%g)\n", $$);
			}
	|	expression '-' expression
			{
				$$ = $1 - $3;
				printf("YACC: Reduced expression - expression to expression (=%g)\n", $$);
			}
	|	expression '*' expression
			{
				$$ = $1 * $3;
				printf("YACC: Reduced expression * expression to expression (=%g)\n", $$);
			}
	|	expression '/' expression
				{
					if($3 == 0.0)
						yyerror("divide by zero");
					else
						$$ = $1 / $3;
					printf("YACC: Reduced expression / expression to expression (=%g)\n", $$);
				}
	|	'-' expression %prec UMINUS
			{
				$$ = -$2;
				printf("YACC: Reduced -expression to expression (=%g)\n", $$);
			}
	|	'(' expression ')'
			{
				$$ = $2;
				printf("YACC: Reduced (expression) to expression (=%g)\n", $$);
			}
	|	NUMBER
			{
				$$ = $1;
				printf("YACC: Reduced NUMBER to expression (=%g)\n", $$);
			}
	|	NAME
			{
				$$ = $1->value;
				printf("YACC: Reduced NAME to expression (=%g)\n", $$);
			}
	;
%%
/* look up a symbol table entry, add if not present */
struct symtab *
symlook(s)
char *s;
{
	char *p;
	struct symtab *sp;

	for(sp = symtab; sp < &symtab[NSYMS]; sp++) {
		/* is it already here? */
		if(sp->name && !strcmp(sp->name, s))
			return sp;

		/* is it free */
		if(!sp->name) {
			sp->name = strdup(s);
			return sp;
		}
		/* otherwise continue to next */
	}
	yyerror("Too many symbols");
	exit(1);	/* cannot continue */
} /* symlook */
