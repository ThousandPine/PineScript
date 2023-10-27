TAR=pine
DEBUG_TAR=pine.d
CC=g++
CFLAGS=-Wall -O2
DEBUG_FLAGS=-Wall -g
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

%.debug.o: %.cpp
	$(CC) $(DEBUG_CFLAGS) -c $< -o $@ -MMD -MF $*.d -MP 

$(TAR): $(FLEX) $(BISON) $(OBJ) $(GEN_OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TAR)

$(DEBUG_TAR): $(FLEX) $(BISON) $(OBJ:.o=.debug.o) $(GEN_OBJ:.o=.debug.o)
	$(CC) $(DEBUG_CFLAGS) $(OBJ:.o=.debug.o) -o $(DEBUG_TAR)

debug: $(DEBUG_TAR)

build: $(TAR)

clean:
	rm -rf $(TAR) $(DEBUG_TAR) $(BISON_HEAD) $(BISON) $(FLEX) $(OBJ) $(OBJ:.o=.debug.o) $(DEPS)

.PHONY: clean