#include "circuit.h"

int main() {
    Circuit c(true, cin);
    c.graphviz(cout);
    cerr << c.get_cost() << endl;
}