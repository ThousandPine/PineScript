TAR=parser.bin
CC=gcc
CFLAGS=-W
SRC=$(wildcard ./*.c)
DEPS=$(wildcard ./*.h) y.tab.h

lex.yy.c: lex.l
	flex lex.l

y.tab.c y.tab.h: parse.y
	bison parse.y -d -o y.tab.c

$(TAR): $(SRC) $(DEPS) lex.yy.c y.tab.c
	$(CC) $(CFLAGS) $(SRC) -o $(TAR)

all: $(TAR)

run: all
	./$(TAR)

clean:
	rm -rf *.bin lex.yy.c y.tab.c y.tab.h

rebuild: clear all

.PHONY: clean