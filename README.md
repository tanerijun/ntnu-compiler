# NTNU Compiler

All code written during NTNU Compiler Design class

## Other

Compile lex program:

bison -d -o y.tab.c --defines=y.tab.h yacc_file.y
flex lex_file.l

gcc lex.yy.c -L/opt/homebrew/Cellar/flex/2.6.4_2/lib -lfl

gcc lex.yy.c y.tab.c -L/opt/homebrew/opt/bison/lib -ly -L/opt/homebrew/Cellar/flex/2.6.4_2/lib -lfl
