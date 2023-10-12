TAR=lexer.bin
CC=gcc
CFLAGS=
SRC=$(wildcard ./*.c)
DEPS=$(wildcard ./*.h)

lex.yy.c: lex.l
	flex lex.l

$(TAR): $(SRC) $(DEPS) lex.yy.c
	$(CC) $(CFLAGS) $(SRC) -o $(TAR)

all: $(TAR)

run: all
	./$(TAR)