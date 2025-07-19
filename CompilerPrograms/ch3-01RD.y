%token NAME NUMBER
%%
statement:	NAME '=' expression
	|	expression		{ printf("= %d\n", $1); }
	;

expression:	expression '+' NUMBER	{ $$ = $1 + $3; 
                                          printf("REDUCE of E+N\n"); }
	|	expression '-' NUMBER	{ $$ = $1 - $3; 
                                          printf("REDUCE of E-N\n"); }
	|	NUMBER			{ $$ = $1; 
                                          printf("REDUCE of N\n"); }
	;
