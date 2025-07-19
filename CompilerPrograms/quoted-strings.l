%%
[\n\t ]	;

\"[^"\n]*["\n] { printf("The quoted string is %s\n",yytext); }

.	ECHO;
%%
main()
{
	yylex();
}
