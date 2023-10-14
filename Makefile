TAR=parser.bin
CC=gcc
CFLAGS=-W
SRC=$(wildcard ./*.c)
DEPS=$(wildcard ./*.h)
GEN_SRC=lex.yy.c y.tab.c
GEN_DEPS=y.tab.h

lex.yy.c: lex.l
	flex lex.l

y.tab.c y.tab.h: parse.y
	bison parse.y -dv -Wcounterexamples -o y.tab.c

$(TAR): $(SRC) $(DEPS) $(GEN_SRC) $(GEN_DEPS)
	$(CC) $(CFLAGS) $(SRC) -o $(TAR)

all: $(TAR)

run: all
	./$(TAR)

clean:
	rm -rf *.bin $(GEN_SRC) $(GEN_DEPS)

rebuild: clean all

.PHONY: clean