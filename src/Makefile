CXX  = g++ -std=c++11
OBJ = ../bin/
BIN = ../bin/

SRC = $(wildcard *.cc)
TAR = $(SRC:.cc=.o)

.PHONY: all clean

all: $(TAR)
    $(CXX) -c $^ -o $(OBJ)$@
    
%.o: %.cc
    $(CXX) -c $^ -o $(OBJ)$@

clean:
    rm -rf $(OBJ)*.o $(TAR)
