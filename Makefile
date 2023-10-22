TAR=pine
CC=g++
CFLAGS=-W -g
SRC=$(wildcard ./*.cpp ./*/*.cpp)
DEPS=$(wildcard ./*.h ./*/*.h)
GEN_SRC=lex.yy.cpp y.tab.cpp
GEN_DEPS=y.tab.h
OBJ=$(patsubst %.cpp, %.o, $(SRC))
GEN_OBJ=$(patsubst %.cpp, %.o, $(GEN_SRC))

lex.yy.cpp: lex.l
	flex -o lex.yy.cpp lex.l

y.tab.cpp y.tab.h: parse.y
	bison parse.y -dv -Wcounterexamples -o y.tab.cpp --header=y.tab.h

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@ 

$(TAR): $(DEPS) $(GEN_DEPS) $(OBJ) $(GEN_OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TAR)

all: $(TAR)

run: all
	./$(TAR)

clean:
	rm -rf $(TAR) $(GEN_SRC) $(GEN_DEPS) $(OBJ)

rebuild: clean all

.PHONY: clean