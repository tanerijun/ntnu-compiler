%{
#include "y.tab.h"
extern int yylval;
%}

%%
[0-9]+	{
    yylval = atoi(yytext);
    printf("LEX: recognized NUMBER: %s\n", yytext);
    return NUMBER;
}
[ \t]	;		/* ignore white space */
\n	{
    printf("LEX: recognized NEWLINE\n");
    return 0;   /* logical EOF */
}
.	{
    printf("LEX: recognized SYMBOL: %c\n", yytext[0]);
    return yytext[0];
}
%%
