%{
%}

digit [0-9]+

%%

{digit}              {printf("Token %s is a integer.\n",yytext); return 1;}
{digit}\.{digit} |
\.{digit}            {printf("Token %s is a float.\n",yytext); return 2;}
{digit}\.            {printf("Token %s is a float.\n",yytext); return 2;}
{digit}/(\.\.)       {printf("Token %s is a integer.\n",yytext); return 1;}

\.\.                 {printf("Token %s is double point\n",yytext); return 3;}

.                    {return 4;}

%%
main(int argc,char** argv){
        int i;
        FILE *fp;
        while(i=yylex()){
        }
}

