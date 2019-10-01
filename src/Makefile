CXX  = g++ -std=c++11
OBJ = ./
BIN = ../bin/

SRC = $(wildcard *.cc)
TAR = $(SRC:.cc=.o)

.PHONY: all program

all: $(TAR)
	$(CXX) -o $(BIN)placement $^
    
%.o: %.cc
	$(CXX) -c $^ -o $@

clean:
	rm -rf $(OBJ)*.o $(BIN)*
