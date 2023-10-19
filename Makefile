TAR=parser.bin
CC=g++
CFLAGS=-W
SRC=$(wildcard ./*.c ./*.cpp)
DEPS=$(wildcard ./*.h)
GEN_SRC=lex.yy.c y.tab.cpp
GEN_DEPS=y.tab.h

lex.yy.c: lex.l
	flex lex.l

y.tab.cpp y.tab.h: parse.y
	bison parse.y -dv -Wcounterexamples -o y.tab.cpp --header=y.tab.h

$(TAR): $(SRC) $(DEPS) $(GEN_SRC) $(GEN_DEPS)
	$(CC) $(CFLAGS) $(SRC) -o $(TAR)

all: $(TAR)

run: all
	./$(TAR)

clean:
	rm -rf *.bin $(GEN_SRC) $(GEN_DEPS)

rebuild: clean all

.PHONY: clean