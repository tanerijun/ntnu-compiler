CC = gcc
CFLAGS = -Wall -g

all: microex

microex: lex.yy.c y.tab.c microex.h
	$(CC) $(CFLAGS) -o microex lex.yy.c y.tab.c -L/opt/homebrew/opt/bison/lib -ly -L/opt/homebrew/Cellar/flex/2.6.4_2/lib -lfl

y.tab.c y.tab.h: microex.y
	bison -d -o y.tab.c --defines=y.tab.h microex.y

lex.yy.c: microex.l y.tab.h
	flex microex.l

clean:
	rm -f microex lex.yy.c y.tab.c y.tab.h
