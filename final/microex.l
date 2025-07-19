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
    // printf("LEX: Found %s token: \"%s\" at line %d, column %d\n", token_type, value, yylineno, column);
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

":="                    { print_token("ASSIGN_OP", yytext); update_column(); return ASSIGN_OP; }
">="                    { print_token("GE_OP", yytext); update_column(); return GE_OP; }
"<="                    { print_token("LE_OP", yytext); update_column(); return LE_OP; }
"=="                    { print_token("EQ_OP", yytext); update_column(); return EQ_OP; }
"!="                    { print_token("NE_OP", yytext); update_column(); return NE_OP; }

[Ii][Ff]                { print_token("IF", yytext); update_column(); return IF_TOKEN; }
[Tt][Hh][Ee][Nn]        { print_token("THEN", yytext); update_column(); return THEN_TOKEN; }
[Ee][Ll][Ss][Ee]        { print_token("ELSE", yytext); update_column(); return ELSE_TOKEN; }
[Ee][Nn][Dd][Ii][Ff]    { print_token("ENDIF", yytext); update_column(); return ENDIF_TOKEN; }

[Ff][Oo][Rr]            { print_token("FOR", yytext); update_column(); return FOR_TOKEN; }
[Tt][Oo]                { print_token("TO", yytext); update_column(); return TO_TOKEN; }
[Dd][Oo][Ww][Nn][Tt][Oo] { print_token("DOWNTO", yytext); update_column(); return DOWNTO_TOKEN; }
[Ee][Nn][Dd][Ff][Oo][Rr] { print_token("ENDFOR", yytext); update_column(); return ENDFOR_TOKEN; }
[Ss][Tt][Ee][Pp]         { print_token("STEP", yytext); update_column(); return STEP_TOKEN; }

[Ww][Hh][Ii][Ll][Ee]             { print_token("WHILE", yytext); update_column(); return WHILE_TOKEN; }
[Ee][Nn][Dd][Ww][Hh][Ii][Ll][Ee] { print_token("ENDWHILE", yytext); update_column(); return ENDWHILE_TOKEN; }

[Pp][Rr][Ii][Nn][Tt]             { print_token("PRINT", yytext); update_column(); return PRINT_TOKEN; }
[Ww][Rr][Ii][Tt][Ee]             { print_token("WRITE", yytext); update_column(); return WRITE_TOKEN; }

[,;]                     { print_token("PUNCTUATION", yytext); update_column(); return yytext[0]; }
[\(\)\[\]]               { print_token("BRACKET", yytext); update_column(); return yytext[0]; }

[0-9]+                   {
                           print_token("INT_LITERAL", yytext);
                           update_column();
                           yylval.ival = atoi(yytext);
                           return INT_LITERAL;
                         }

[0-9]+\.[0-9]+           {
                           print_token("FLOAT_LITERAL", yytext);
                           update_column();
                           yylval.fval = atof(yytext);
                           return FLOAT_LITERAL;
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

[-+*/><]                 {
                           print_token("OPERATOR", yytext);
                           update_column();
                           return yytext[0];
                         }

.                        {
                           printf("LEX: Error - Unrecognized character: '%c' at line %d, column %d\n",
                                  yytext[0], yylineno, column);
                           update_column();
                           return yytext[0];
                         }
%%
