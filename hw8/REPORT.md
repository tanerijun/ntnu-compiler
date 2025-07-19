## Compiler HW8

Name: 陳偉俊
Student ID: 61347090S

## Code After Modification

Lex:

```l
%{
#include "y.tab.h"
#include "ch3hdr.h"
#include <math.h>
%}

%%
([0-9]+|([0-9]*\.[0-9]+)([eE][-+]?[0-9]+)?) {
        printf("LEX: Found NUMBER token: %s\n", yytext);
		yylval.dval = atof(yytext);
		return NUMBER;
	}

[ \t]	;		 /* ignore white space */

[A-Za-z][A-Za-z0-9]*	{	/* return symbol pointer */
        printf("LEX: Found NAME token: %s\n", yytext);
		yylval.symp = symlook(yytext);
		return NAME;
	}

"$"	{ printf("LEX: Found EOF token: $\n"); return 0; }

\n      { printf("LEX: Found NEWLINE\n"); return yytext[0]; }
.       { printf("LEX: Found token: %c\n", yytext[0]); return yytext[0]; }
```

Yacc:

```y
%{
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

```

## Trace Result:

```
abc=5
LEX: Found NAME token: abc
LEX: Found token: =
LEX: Found NUMBER token: 5
YACC: Reduced NUMBER to expression (=5)
LEX: Found NEWLINE
YACC: Reduced NAME = expression to statement
YACC: Reduced statement '\n' to statement_list
z5=abc*1.23
LEX: Found NAME token: z5
LEX: Found token: =
LEX: Found NAME token: abc
YACC: Reduced NAME to expression (=5)
LEX: Found token: *
LEX: Found NUMBER token: 1.23
YACC: Reduced NUMBER to expression (=1.23)
YACC: Reduced expression * expression to expression (=6.15)
LEX: Found NEWLINE
YACC: Reduced NAME = expression to statement
YACC: Reduced statement_list statement '\n' to statement_list
xy=1-(abc/3-6)*z5
LEX: Found NAME token: xy
LEX: Found token: =
LEX: Found NUMBER token: 1
YACC: Reduced NUMBER to expression (=1)
LEX: Found token: -
LEX: Found token: (
LEX: Found NAME token: abc
YACC: Reduced NAME to expression (=5)
LEX: Found token: /
LEX: Found NUMBER token: 3
YACC: Reduced NUMBER to expression (=3)
YACC: Reduced expression / expression to expression (=1.66667)
LEX: Found token: -
LEX: Found NUMBER token: 6
YACC: Reduced NUMBER to expression (=6)
LEX: Found token: )
YACC: Reduced expression - expression to expression (=-4.33333)
YACC: Reduced (expression) to expression (=-4.33333)
LEX: Found token: *
LEX: Found NAME token: z5
YACC: Reduced NAME to expression (=6.15)
YACC: Reduced expression * expression to expression (=-26.65)
LEX: Found NEWLINE
YACC: Reduced expression - expression to expression (=27.65)
YACC: Reduced NAME = expression to statement
YACC: Reduced statement_list statement '\n' to statement_list
xy
LEX: Found NAME token: xy
LEX: Found NEWLINE
YACC: Reduced NAME to expression (=27.65)
= 27.65
YACC: Reduced expression to statement
YACC: Reduced statement_list statement '\n' to statement_list
$
LEX: Found EOF token: $
```
