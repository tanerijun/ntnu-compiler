%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// Enumeration for token types
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

int column = 1; // current column position on the line

// String buffer for string literals handling
#define MAX_STR_LEN 1024 // maximum length for string literal content
char string_buffer[MAX_STR_LEN];
int string_buffer_pos = 0;
int string_start_line = 0;
int string_start_col = 0;

void update_column() {
    column += yyleng;
}

void print_token(TokenType token_type, const char* value) {
    printf("Token number = %d, value is \"%s\"\n", token_type, value);
}

void append_string_segment(const char* text, int len) {
    if (string_buffer_pos + len >= MAX_STR_LEN) {
        fprintf(stderr, "Lexical Error on line %d, column %d: String literal exceeds maximum length of %d\n",
                string_start_line, string_start_col, MAX_STR_LEN - 1);
        exit(1);
    }
    memcpy(string_buffer + string_buffer_pos, text, len);
    string_buffer_pos += len;
    string_buffer[string_buffer_pos] = '\0';
}

%}

/* --- Disables automatic input wrapping & automatically maintains line count --- */
%option noyywrap yylineno

/* --- Exclusive state (see <STRING_STATE> below - exclusive processing for string (allow different handling of characters inside strings)) --- */
%x STRING_STATE

/* --- Regular Expression Definitions --- */
DIGIT       [0-9]
LETTER      [a-zA-Z]
ID          {LETTER}({LETTER}|{DIGIT})*
INTEGER     {DIGIT}+
FLOAT       ({DIGIT}+\.{DIGIT}*)|({DIGIT}*\.{DIGIT}+)
EXPFLOAT    ({FLOAT}|{INTEGER})[eE][-+]?{DIGIT}+
COMMENT     %%[^\n]*
WHITESPACE  [ \t]+

/* --- Lex Rules --- */
%%

{WHITESPACE} { update_column(); }
\n           { update_column(); column = 1; /* line count handled by yylineno, just reset column */ }
{COMMENT}    { /* Comments are ignored, column reset happens on next \n */ }

 /* Keywords */
[Bb][Ee][Gg][Ii][Nn]             { print_token(BEGIN_TOKEN, yytext); update_column(); }
[Ee][Nn][Dd]                     { print_token(END_TOKEN, yytext); update_column(); }
[Rr][Ee][Aa][Dd]                 { print_token(READ_TOKEN, yytext); update_column(); }
[Ww][Rr][Ii][Tt][Ee]             { print_token(WRITE_TOKEN, yytext); update_column(); }
[Pp][Rr][Ii][Nn][Tt]             { print_token(WRITE_TOKEN, yytext); update_column(); }
[Ii][Ff]                         { print_token(IF_TOKEN, yytext); update_column(); }
[Tt][Hh][Ee][Nn]                 { print_token(THEN_TOKEN, yytext); update_column(); }
[Ee][Ll][Ss][Ee]                 { print_token(ELSE_TOKEN, yytext); update_column(); }
[Ee][Nn][Dd][Ii][Ff]             { print_token(ENDIF_TOKEN, yytext); update_column(); }
[Ff][Oo][Rr]                     { print_token(FOR_TOKEN, yytext); update_column(); }
[Tt][Oo]                         { print_token(TO_TOKEN, yytext); update_column(); }
[Ee][Nn][Dd][Ff][Oo][Rr]         { print_token(ENDFOR_TOKEN, yytext); update_column(); }
[Ww][Hh][Ii][Ll][Ee]             { print_token(WHILE_TOKEN, yytext); update_column(); }
[Ee][Nn][Dd][Ww][Hh][Ii][Ll][Ee] { print_token(ENDWHILE_TOKEN, yytext); update_column(); }
[Dd][Ee][Cc][Ll][Aa][Rr][Ee]     { print_token(DECLARE_TOKEN, yytext); update_column(); }
[Aa][Ss]                         { print_token(AS_TOKEN, yytext); update_column(); }
[Ii][Nn][Tt][Ee][Gg][Ee][Rr]     { print_token(INTEGER_TOKEN, yytext); update_column(); }
[Rr][Ee][Aa][Ll]                 { print_token(REAL_TOKEN, yytext); update_column(); }

 /* Numbers */
{EXPFLOAT}  { print_token(EXPFLOAT_LIT_TOKEN, yytext); update_column(); }
{FLOAT}     { print_token(FLOAT_LIT_TOKEN, yytext); update_column(); }
{INTEGER}   { print_token(INT_LIT_TOKEN, yytext); update_column(); }

 /* Start of String Literal */
\"          {
              string_start_line = yylineno;
              string_start_col = column;
              string_buffer[0] = '\0'; // clear buffer
              string_buffer_pos = 0;
              update_column(); // update column for the opening quote
              BEGIN(STRING_STATE); // see <STRING_STATE> below
            }

 /* Operators */
":="        { print_token(ASSIGN_OP_TOKEN, yytext); update_column(); }
"!="        { print_token(NOT_EQ_OP_TOKEN, yytext); update_column(); }
">="        { print_token(GE_OP_TOKEN, yytext); update_column(); }
"<="        { print_token(LE_OP_TOKEN, yytext); update_column(); }
"=="        { print_token(EQ_OP_TOKEN, yytext); update_column(); }
"+"         { print_token(PLUS_OP_TOKEN, yytext); update_column(); }
"-"         { print_token(MINUS_OP_TOKEN, yytext); update_column(); }
"*"         { print_token(MULT_OP_TOKEN, yytext); update_column(); }
"/"         { print_token(DIV_OP_TOKEN, yytext); update_column(); }
">"         { print_token(GT_OP_TOKEN, yytext); update_column(); }
"<"         { print_token(LT_OP_TOKEN, yytext); update_column(); }

 /* Punctuation */
"("         { print_token(LPAREN_TOKEN, yytext); update_column(); }
")"         { print_token(RPAREN_TOKEN, yytext); update_column(); }
";"         { print_token(SEMICOLON_TOKEN, yytext); update_column(); }
","         { print_token(COMMA_TOKEN, yytext); update_column(); }

 /* Identifier (after keywords) */
{ID}        { print_token(ID_TOKEN, yytext); update_column(); }

 /* End of File - the <INITIAL> prefix is necessary used to avoid conflict with EOF inside <STRING_STATE>  */
<INITIAL><<EOF>>     { print_token(SCANEOF_TOKEN, "EOF"); return 0; }

 /* Lexical Error - Catch any other character in INITIAL state */
.           {
              fprintf(stderr, "Lexical Error on line %d, column %d: Illegal token '%s'\n", yylineno, column, yytext);
              update_column();
              exit(1);
            }

 /* --- Rules for handling string --- */
<STRING_STATE>{
  /* Match content: Anything except quote or newline */
  [^\"\n]+     {
                  append_string_segment(yytext, yyleng);
                  update_column(); // Update column for string content
               }

  /* Match the closing quote */
  \"           {
                 print_token(STRING_LIT_TOKEN, string_buffer);
                 update_column(); // Update column for the closing quote
                 BEGIN(INITIAL); // back to normal scanning
               }

  /* Error: Newline inside string */
  \n           {
                 update_column();
                 fprintf(stderr, "Lexical Error on line %d, column %d: Unterminated string literal starting on line %d, column %d\n",
                         yylineno, column, string_start_line, string_start_col);
                 column = 1;
                 BEGIN(INITIAL);
                 exit(1);
               }

  /* Error: EOF inside string */
  <<EOF>>      {
                 fprintf(stderr, "Lexical Error: Unterminated string literal starting on line %d, column %d (reached EOF)\n",
                         string_start_line, string_start_col);
                 BEGIN(INITIAL);
                 print_token(SCANEOF_TOKEN, "EOF"); // Optionally print EOF token after error
                 exit(1);
               }
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
        yyin = stdin; // read from standard input if no file is specified
        fprintf(stderr, "Reading from standard input...\n");
    }

    yylex();

    printf("End of the execution\n");

    if (yyin != stdin && yyin != NULL) {
       fclose(yyin);
    }

    return 0;
}
