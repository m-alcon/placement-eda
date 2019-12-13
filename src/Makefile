CXX  = g++ -std=c++11
OBJ = ./
BIN = ../bin/

SRC = $(wildcard *.cc)
TAR = $(SRC:.cc=.o)

.PHONY: all

all: placement visualization

placement: placement.o circuit.o
	$(CXX) -o $(BIN)placement $^

visualization: visualization.o circuit.o
	$(CXX) -o $(BIN)visualization $^
    
%.o: %.cc
	$(CXX) -c $^ -o $@

clean:
	rm -rf $(OBJ)*.o $(BIN)*
