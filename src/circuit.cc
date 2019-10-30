#include "circuit.h"

Circuit::Circuit (istream &input) {
    int m, v;
    cin >> n >> w >> h;
    adjacency = Matrix(n);
    for (int i = 0; i < n; ++i) {
        cin >> m;
        adjacency[i] = Vector(m);
        for (int j = 0; j < m; ++j) {
            cin >> v;
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

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            output << "\t" << i*w + j << " [pos=\"" << j << "," << -i << "\"];" << endl;
        }
    }
    output << "}" << endl;
}