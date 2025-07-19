# About

This project is the final project for my "Compiler Design" course. The objective is to build a compiler including scanner and parser using Lex and Yacc for a custom programming language called "Micro/Ex". For my midterm project, I built a scanner using Lex for the "Micro" programming language. Note that "Micro/Ex" is an extension of "Micro" with additional features.

## Midterm Project Result

Below is the code for the scanner I created before:

```lex
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
```

The report I submitted:

```markdown
## Features

1. Recognition of the 38 tokens shown in the PPT slide.
2. Supports case-insensitive keywords (begin, BEGIN, etc.)
3. Handle the keyword "print" as a WRITE token (as provided in test case).
4. Handle lexical error:
   - Shows line number
   - Shows column number (char)
   - Shows illegal token
5. Identify unterminated string due to newline before closing quote (Unterminated string literal on line x column y)
6. Identify unterminated string due to EOF before closing quote (Unterminated string literal on line 3, column 9 (reached EOF))

## Explanation:

From the test data provided by professor, we can see that the scanner have to be **case_insensitive**. We can also see that the string `"Good!"` is written using `print` instead of `write`. Therefore, we can also assume that `print` is another way to write in micro/ex. I registered `print` as another WRITE_TOKEN in the scanner

We also improve the scanner's UX by showing line number, column number, and the illegal token on error. This is done by keeping track of the current line and current column as the scanner matches the tokens.

We also give the scanner the ability to detect unterminated string (no closing quote), showing a descriptive error, like where the string start. We did this by tracking the starting line and column numbers (string_start_line and string_start_col) when encountering an opening quote. When entering string mode using BEGIN(STRING_STATE), we enter an exclusive lexer state that handles string content differently. If a newline or EOF is encountered before finding a closing quote, we report the error with the exact position where the unterminated string began.
```

## About Final Project

Below are the slides provided by the professors:

#### Slide 1

- Use Lex and Yacc to generate a compiler for Micro/Ex
- Micro/Ex is an extension of Micro
- Sample program:

  ```microex
  %%the beginning of an test data for Micro/Ex
  Program testP
  Begin
    declare I as integer;
    declare A,B,C,D, LLL[100] as float;

    FOR (I:=1 TO 100)
      A:=-LLL[I]+B*D-C;
    ENDFOR

    IF (A>=10000.0) THEN
      print(1);
    ELSE
      print(2,1.4);
    ENDIF
  End
  ```

#### Slide 2

- Variables must be declared before referenced
- FOR construct

  ```microex
  FOR (I:=1 TO 100)
    A:=-LLL[I]+B*D-C;
  ENDFOR

  FOR (I:=100 DOWNTO 1)
    A:=-LLL[I]+B*D-C;
  ENDFOR
  ```

#### Slide 3

- IF-ENDIF and IF-ELSE_ENDIF construct
- Example:

  ```microex
  IF (A>=10000.0) THEN
    print(5*3+1);
  ENDIF

  IF (A>=10000.0) THEN
    print(1);
  ELSE
    print(2,1.4);
  ENDIF
  ```

### Slide 4

- Subroutine call
- Example:

  ```microex
  IF (A>=10000.0) THEN
    print(5*3+1); // Each actual parameter can be an expression.
  ENDIF

  IF (A>=10000.0) THEN
    print(1);
  ELSE
    print(2,1.4); // It can have multiple parameters
  ENDIF
  ```

### Slide 5

- Target language: Three address machine
  - Variable declaration instruction
    – Declare A, Integer
    – Declare A, Integer_array,20
    – Declare B, Float
    – Declare B, Float_array,20
  - Arithmetic instruction
    - I_SUB i1,i2,t
      – I_ADD i1,i2,t
      – I_DIV i1,i2,t
      – I_MUL i1,i2,t
      – I_UMINUS i1,t
      – INC I
      - I=I+1
        – DEC I
      - I=I-1
        – F_SUB f1,f2,t
        – F_ADD f1,f2,t
        – F_DIV f1,f2,t
        – F_MUL f1,f2,t
        – F_UMINUS f1,t
  - Assignment instruction
    – I_Store i1,t
    – F_Store f1,t
  - Compare instruction
    – I_CMP i1,i2
    – F_CMP f1,f2
  - Jump instruction
    – J,JE, JG, JGE, JL, JLE, JNE
  - Subroutine operation
    – CALL rn,a1,a2
    - rn: the name of the subroutine
    - a1 and a2 could be integer literal, float point literal, or id.
  - Logical instruction
    – AND b1,b2,t
    - t will be 0 or 1 after the execution of this instruction
      – OR b1,b2,t
    - t will be 0 or 1 after the execution of this instruction
      – NOT b, t
    - b will be 0 or 1 after the execution of this instruction

### Slide 6

Compilation example:

```microex
%%the beginning of an test data for Micro/Ex
Program testP
Begin
  declare I as integer;
  declare A,B,C,D, LLL[100] as float;

  FOR (I:=1 TO 100)
    A:=-LLL[I]+B*D-C;
    ENDFOR

  IF (A>=10000.0) THEN
    print(A+3.14);
  ELSE
    print(2,1.4);
  ENDIF
End
```

```assembly
START testP
Declare I, Integer
Declare A, Float
Declare B, Float
Declare C, Float
Declare D, Float
Declare LLL, Float_array,100
I_STORE 1,I
lb&1: F_UMINUS LLL[I],T&1
F_MUL B,D,T&2
F_ADD T&2, T&1, T&3
F_SUB T&3,C,T&4
F_STORE T&4,A
INC I
I_CMP I,100
JLE lb&1
F_CMP A,100000.0
JL lb&2
F_ADD A, 3.14, T&5
CALL print, T&5
J lb&3
lb&2: CALL print,2,1.4
lb&3: HALT testP
Declare T&1, Float
Declare T&2, Float
Declare T&3, Float
Declare T&4, Float
Declare T&5, Float
```

### Slide 7

- Support FOR construct

  ```microex
  FOR (I:=1 TO 100*J+6 STEP 5)
    A:=-LLL[I]+B*D-C;
  ENDFOR

  FOR (I:=2*J-4 DOWNTO 5 STEP 4)
    A:=-LLL[I]+B*D-C;
  ENDFOR
  ```

### Slide 8

- Support WHILE construct

  ```microex
  %%the beginning of an test data for Micro/Ex
  Program testP
  Begin
    declare I as integer;
    declare A,B,C,D, LLL[100] as float;

  I:=1;
  WHILE (I<=100)
    A:=-LLL[I]+B*D-C;
    I:=1+1;
  ENDWHILE

  IF (A>=10000.0) THEN
    print(A+3.14);
  ELSE
    print(2,1.4);
  ENDIF
  End
  ```

### Slide 9

- Support Nested structure

  ```microex
  %%the beginning of an test data for Micro/Ex
  Program testP
  Begin
    declare I,J as integer;
    declare A,B,C,D, LLL[100] as float;

    I:=1;
    WHILE (I<=100)
      A:=-LLL[I]+B*D-C;
      I:=1+1;
      FOR (I:=1 TO 100)
        A:=A*3.0;
      ENDFOR
    ENDWHILE

    IF (A>=10000.0) THEN
      IF (B<=0.0) THEN
        print(A+3.14);
      ELSE
        print(A+3.14*10);
      ENDIF
    ELSE
      print(2,1.4);
    ENDIF
  End
  ```

### Slide 10

- Support sophisticated logical expression

  ```microex
  WHILE ((I<=100) &&(A>10))
    A:=-LLL[I]+B*D-C;
    I:=1+1;
  ENDWHILE

  IF (!((A>=10000)|| (C<100))) THEN
    print(A+3.14);
  ELSE
    print(2,1.4);
  ENDIF
  ```

### Slide 11

- Support user-defined function and static type checking

  ```microex
  %%the beginning of an test data for Micro/Ex
  Program testP
    Function integer Cal_Something(integer I, float f)
      Begin
        declare k as integer;
        ……….
        return k;
      End

    Begin
      declare I,J as integer;
      declare A,B,C,D, LLL[100] as float;
      FOR (I:=1 TO 100)
        A:=-LLL[I]+B*D-C;
        J:=Cal_Something(I,A);
      ENDFOR
  End
  ```

  ```assembly (note that dot symbol here stands for ellipsis)
  START testP
  Declare Cal_Something, Function,I,f
  Declare k, integer;
  .
  .
  Return k
  Declare I, Integer
  Declare J,Integer
  Declare A, Float
  Declare B, Float
  Declare C, Float
  Declare D, Float
  Declare LLL, Float_array,100
  I_STORE 1,I
  lb&1: F_MUL B,D,T&1
  F_UMINUS LLL[I],T&2
  F_ADD T&2, T&1, T&3
  F_SUB T&3,C,T&4
  F_STORE T&4,A
  I_STORE Cal_Something(I,A),J
  INC I
  I_CMP I,100
  JL lb&1
  HALT testP
  Declare T&1, Float
  Declare T&2, Float
  Declare T&3, Float
  Declare T&4, Float
  ```
