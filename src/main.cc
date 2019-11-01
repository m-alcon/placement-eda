#include "circuit.h"

int main () {
    Circuit c = Circuit(cin);
    c.graphviz(cout);
    return 0;
}