#include "circuit.h"

Circuit::Circuit (istream &input) {
    int m, v;
    input >> n >> w >> h;
    adjacency = Matrix(n);
    positions = Matrix(n, Vector(DIMS));
    for (int i = 0; i < n; ++i) {
        input >> positions[i][0] >> positions[i][1] >> m;
        adjacency[i] = Vector(m);
        for (int j = 0; j < m; ++j) {
            input >> v;
            adjacency[i][j] = v;
        }
    }
}

void Circuit::print(ostream &output) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < adjacency[i].size(); ++j) {
            output << adjacency[i][j] << " ";
        }
        output << endl;
    }
}

void Circuit::graphviz(ostream &output) {
    output << "graph G {" << endl << "\tnode[pin=true];" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < adjacency[i].size(); ++j) {
            if (i <= adjacency[i][j])
                output << "\t" << i << " -- " << adjacency[i][j] << ";" << endl;
        }
    }
    for (int i = 0; i < n; ++i) {
        output << "\t" << i << " [pos=\"" << positions[i][1];
        output << "," << -positions[i][0] << "\"];" << endl;
    }
    output << "}" << endl;
}