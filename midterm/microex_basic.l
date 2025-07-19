%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* --- Token Enumeration --- */
typedef enum {
    BEGIN_TOKEN = 1, END_TOKEN, READ_TOKEN, WRITE_TOKEN, ID_TOKEN,
    INT_LIT_TOKEN, FLOAT_LIT_TOKEN, EXPFLOAT_LIT_TOKEN, STRING_LIT_TOKEN,
    LPAREN_TOKEN, RPAREN_TOKEN, SEMICOLON_TOKEN, COMMA_TOKEN,
    ASSIGN_OP_TOKEN, PLUS_OP_TOKEN, MINUS_OP_TOKEN, MULT_OP_TOKEN, DIV_OP_TOKEN,
    NOT_EQ_OP_TOKEN, GT_OP_TOKEN, LT_OP_TOKEN, GE_OP_TOKEN, LE_OP_TOKEN, EQ_OP_TOKEN,
    IF_TOKEN, THEN_TOKEN, ELSE_TOKEN, ENDIF_TOKEN,
    FOR_TOKEN, TO_TOKEN, ENDFOR_TOKEN,
    WHILE_TOKEN, ENDWHILE_TOKEN,
    DECLARE_TOKEN, AS_TOKEN, INTEGER_TOKEN, REAL_TOKEN,
    SCANEOF_TOKEN
} TokenType;

/* --- Helper Function --- */
// Print token details
void print_token(TokenType token_type, const char* value) {
    printf("Token number = %d, value is \"%s\"\n", token_type, value);
}
%}

/* --- Flex Options --- */
%option noyywrap yylineno

/* --- Regular Expression Definitions --- */
DIGIT       [0-9]
LETTER      [a-zA-Z]
ID          {LETTER}({LETTER}|{DIGIT})*

/* Integer literal: sequence of digits */
INTEGER     {DIGIT}+

/* Float literal: handles 12.345, 123., .456 */
FLOAT       ({DIGIT}+\.{DIGIT}*)|({DIGIT}*\.{DIGIT}+)

/* Exponential float literal: handles forms like 1.2e3, 12E-5, .5e+10, 5.E6 */
EXPFLOAT    ({FLOAT}|{INTEGER})[eE][-+]?{DIGIT}+

/* String literal: double quotes, anything inside except newline or quote */
/* More robust would handle escaped quotes \" TODO: Make it handle escaped quotes*/
STRING      \"[^\"\n]*\"

/* Comment: Starts with %% and goes to the end of the line */
COMMENT     %%[^\n]*

/* Whitespace: spaces and tabs */
WHITESPACE  [ \t]+

/* Newline */
NEWLINE     \n

%%
 /* --- Lex Rules --- */

{WHITESPACE} { /* Ignore whitespace */ }
{NEWLINE}    { /* Ignore newline, line number tracked by %option yylineno */ }
{COMMENT}    { /* Ignore comments */ }

 /* Keywords (must come before ID rule) */
"begin"     { print_token(BEGIN_TOKEN, yytext); }
"end"       { print_token(END_TOKEN, yytext); }
"read"      { print_token(READ_TOKEN, yytext); }
"write"     { print_token(WRITE_TOKEN, yytext); }
"if"        { print_token(IF_TOKEN, yytext); }
"then"      { print_token(THEN_TOKEN, yytext); }
"else"      { print_token(ELSE_TOKEN, yytext); }
"endif"     { print_token(ENDIF_TOKEN, yytext); }
"for"       { print_token(FOR_TOKEN, yytext); }
"to"        { print_token(TO_TOKEN, yytext); }
"endfor"    { print_token(ENDFOR_TOKEN, yytext); }
"while"     { print_token(WHILE_TOKEN, yytext); }
"endwhile"  { print_token(ENDWHILE_TOKEN, yytext); }
"declare"   { print_token(DECLARE_TOKEN, yytext); }
"as"        { print_token(AS_TOKEN, yytext); }
"integer"   { print_token(INTEGER_TOKEN, yytext); }
"real"      { print_token(REAL_TOKEN, yytext); }

 /* Literals (Order: EXPFLOAT > FLOAT > INTEGER) */
{EXPFLOAT}  { print_token(EXPFLOAT_LIT_TOKEN, yytext); }
{FLOAT}     { print_token(FLOAT_LIT_TOKEN, yytext); }
{INTEGER}   { print_token(INT_LIT_TOKEN, yytext); }
{STRING}    { print_token(STRING_LIT_TOKEN, yytext); }

 /* Operators (Order: multi-char first) */
":="        { print_token(ASSIGN_OP_TOKEN, yytext); }
"!="        { print_token(NOT_EQ_OP_TOKEN, yytext); }
">="        { print_token(GE_OP_TOKEN, yytext); }
"<="        { print_token(LE_OP_TOKEN, yytext); }
"=="        { print_token(EQ_OP_TOKEN, yytext); }
"+"         { print_token(PLUS_OP_TOKEN, yytext); }
"-"         { print_token(MINUS_OP_TOKEN, yytext); }
"*"         { print_token(MULT_OP_TOKEN, yytext); }
"/"         { print_token(DIV_OP_TOKEN, yytext); }
">"         { print_token(GT_OP_TOKEN, yytext); }
"<"         { print_token(LT_OP_TOKEN, yytext); }

 /* Punctuation (Escape parentheses) */
"("         { print_token(LPAREN_TOKEN, yytext); }
")"         { print_token(RPAREN_TOKEN, yytext); }
";"         { print_token(SEMICOLON_TOKEN, yytext); }
","         { print_token(COMMA_TOKEN, yytext); }

 /* Identifier (after keywords) */
{ID}        { print_token(ID_TOKEN, yytext); }

 /* End of File */
<<EOF>>     { print_token(SCANEOF_TOKEN, "EOF"); return 0; /* Signal successful end */ }

 /* Lexical Error - Catch any other character */
.           {
              fprintf(stderr, "Lexical Error on line %d: Illegal token '%s'\n", yylineno, yytext);
              exit(1); // terminate on lexical error
            }

%%

int main(int argc, char *argv[]) {
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            perror(argv[1]);
            return 1;
        }
        yyin = file; // point flex to the input file
    } else {
        yyin = stdin; // read from stdin if no file is given
        fprintf(stderr, "Reading from standard input...\n");
    }

    yylex();

    printf("End of the execution\n");

    if (yyin != stdin && yyin != NULL) {
       fclose(yyin);
    }

    return 0;
}