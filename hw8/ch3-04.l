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
