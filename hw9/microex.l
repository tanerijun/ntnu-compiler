%{
#include "y.tab.h"
#include "microex.h"
#include <stdio.h>
#include <string.h>

int column = 1;
extern int yylineno;

void update_column() {
    column += yyleng;
}

void print_token(const char* token_type, const char* value) {
    printf("LEX: Found %s token: \"%s\" at line %d, column %d\n",
           token_type, value, yylineno, column);
}
%}

%option yylineno
%option noyywrap

%%
[Pp][Rr][Oo][Gg][Rr][Aa][Mm]   { print_token("PROGRAM", yytext); update_column(); return PROGRAM_TOKEN; }
[Bb][Ee][Gg][Ii][Nn]     { print_token("BEGIN", yytext); update_column(); return BEGIN_TOKEN; }
[Ee][Nn][Dd]             { print_token("END", yytext); update_column(); return END_TOKEN; }
[Dd][Ee][Cc][Ll][Aa][Rr][Ee] { print_token("DECLARE", yytext); update_column(); return DECLARE_TOKEN; }
[Aa][Ss]                 { print_token("AS", yytext); update_column(); return AS_TOKEN; }
[Ii][Nn][Tt][Ee][Gg][Ee][Rr] { print_token("INTEGER_TYPE", yytext); update_column(); return INTEGER_TOKEN; }
[Rr][Ee][Aa][Ll]         { print_token("REAL_TYPE", yytext); update_column(); return REAL_TOKEN; }

[,;]                     { print_token("PUNCTUATION", yytext); update_column(); return yytext[0]; }
[\(\)\[\]]               { print_token("BRACKET", yytext); update_column(); return yytext[0]; }

[0-9]+                   {
                           print_token("INTEGER", yytext);
                           update_column();
                           yylval.ival = atoi(yytext);
                           return INT_LITERAL;
                         }

[A-Za-z][A-Za-z0-9]*     {
                           print_token("IDENTIFIER", yytext);
                           update_column();
                           yylval.symp = symlook(yytext);
                           return ID;
                         }

"%%".*                   { /* Comments are ignored */ update_column(); }

[ \t]+                   { update_column(); /* ignore whitespace */ }
\n                       { column = 1; /* Reset column on newline */ }

.                        {
                           printf("LEX: Error - Unrecognized character: '%c' at line %d, column %d\n",
                                  yytext[0], yylineno, column);
                           update_column();
                           return yytext[0];
                         }
%%
