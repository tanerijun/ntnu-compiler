%{
#include "y.tab.h"
#include "ch3hdr.h"
#include <math.h>
extern int numline;
%}

%%
([0-9]+|([0-9]*\.[0-9]+)([eE][-+]?[0-9]+)?) {
		yylval.dval = atof(yytext);
		return NUMBER;
	}

[ \t]	;		 /* ignore white space */

[A-Za-z][A-Za-z0-9]*	{	/* return symbol pointer */
             /*   printf("I got token=%s\n",yytext); */
		yylval.symp = symlook(yytext);
		return NAME;
	}

"$"	{ return 0; }


\%[A-Za-z][A-Za-z0-9]*	{  printf("I got wrong token=%s\n", yytext);

                            yyless(1);}

\n	{ numline++; return yytext[0];}
.       { return yytext[0];}
