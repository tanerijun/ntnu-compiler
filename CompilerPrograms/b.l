%{
#include "y.tab.h"
extern int yylval;
extern int i;
%}

%%
[0-9]+	{ yylval = atoi(yytext); i++;  printf("i=%d\n",i); return NUMBER; }
[ \t]	;		/* ignore white space */
\n	return 0;	/* logical EOF */
.	return yytext[0];
%%
