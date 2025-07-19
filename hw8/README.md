bison -d -o y.tab.c --defines=y.tab.h ch3-04.y
flex ch3-04.l
gcc lex.yy.c y.tab.c -L/opt/homebrew/opt/bison/lib -ly -L/opt/homebrew/Cellar/flex/2.6.4_2/lib -lfl
