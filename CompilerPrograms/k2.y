%token NAME NUMBER
%left '-' '+'
%left '*' '/'
%nonassoc UMINUS

%%

statement:	NAME '=' expression
	|	expression		{ printf("= %d\n", $1); }
	;

expression:	expression '+' expression { $$ = $1 + $3; 
                printf("Reduce +\n"); }
	|	expression '-' expression { $$ = $1 - $3;
                printf("Reduce -\n"); }
	|	expression '*' expression { $$ = $1 * $3;
                printf("Reduce *\n"); }
	|	expression '/' expression
				{	if($3 == 0)
						yyerror("divide by zero");
					else
						$$ = $1 / $3;
				}
	|	'-' expression %prec UMINUS	{ $$ = -$2;
                     printf("Reduce unary minus\n"); }
 
	|	'(' expression ')'	{ $$ = $2; }
	|	NUMBER			{ $$ = $1; }
	;
%%
