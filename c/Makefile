CC = g++ -std=c++17
CFLAGS = -Wall -Werror -Wpedantic -Werror -Wno-register -Ofast

JSON = fwjson
PARSER = fwparser
EXECS = $(JSON) $(PARSER)

FLEXSRC = lexer.l
FLEXCPP = yylex.cpp
FLEXOBJ = $(FLEXCPP:%.cpp=%.o)

YACCSRC = parser.y
YACCCPP = yyparse.cpp
YACCHDR = $(YACCCPP:%.cpp=%.hpp)
YACCOBJ = $(YACCCPP:%.cpp=%.o) lexyacc.o

LYSRC = lexyacc.cpp
LYOBJ = $(LYSRC:%.cpp=%.o)

MODULES = newick.o

all: $(EXECS)

$(JSON): $(MODULES) $(JSON).o
	$(CC) -o $@ $^

$(PARSER): $(LYOBJ) $(YACCOBJ) $(FLEXOBJ) $(MODULES) $(PARSER).o
	$(CC) -o $@ $^

$(FLEXCPP): $(FLEXSRC)
	flex --outfile=$@ $<

$(YACCCPP): $(YACCSRC)
	yacc -Wno-yacc --defines=$(YACCHDR) --output=$@ $<

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(EXECS) $(FLEXCPP) $(YACCCPP) $(YACCHDR) *.o
