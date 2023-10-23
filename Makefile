TAR=pine
CC=g++
CFLAGS=-W -g
FLEX=lex.yy.cpp
BISON=y.tab.cpp y.tab.h
SRC=$(wildcard ./*.cpp ./*/*.cpp)
DEPS=$(SRC:.cpp=.d)
OBJ=$(SRC:.cpp=.o)
GEN_OBJ=$(BISON:.cpp=.o) $(FLEX:.cpp=.o)

-include $(DEPS)

$(FLEX): lex.l
	flex -o lex.yy.cpp lex.l

$(BISON): parse.y
	bison parse.y -dv -Wcounterexamples -o y.tab.cpp --header=y.tab.h

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@ -MMD -MF $*.d -MP 

$(TAR): $(FLEX) $(BISON) $(OBJ) $(GEN_OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TAR)

all: $(TAR)

run: all
	./$(TAR)

clean:
	rm -rf $(TAR) $(BISON_HEAD) $(BISON) $(FLEX) $(OBJ) $(DEPS)

rebuild: clean all

.PHONY: clean