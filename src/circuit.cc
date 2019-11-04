#include "circuit.h"

Circuit::Circuit (istream &input) {
    int m, v;
    input >> n >> w >> h;
    adjacency = Matrix(n);
    //positions = Matrix(n, Vector(DIMS));
    for (int i = 0; i < n; ++i) {
        //input >> positions[i][0] >> positions[i][1] >> m;
        input >> m;
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

Matrix Circuit::generate_all_positions() {
    Matrix all_positions = Matrix(w*h, Vector(DIMS));
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            all_positions[i*w + j] = {i,j};
        }
    }
    shuffle(all_positions.begin(), all_positions.end() , default_random_engine(1234));
    return all_positions;
}


void Circuit::place_randomly() {
    Matrix all_poistions = generate_all_positions();
    positions = Matrix(all_poistions.begin(), all_poistions.begin() + n);
}

void Circuit::place_cells(float temperature) {
    place_randomly();
    while (temperature > min_temperature) {
        
    }
}