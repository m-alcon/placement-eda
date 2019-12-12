#include "circuit.h"

void Perturbation::set (const uint &u_, const uint &v_, const uint &cost_) {
    u = u_;
    v = v_;
    cost = cost_;
}

Circuit::Circuit (istream &input) {
    int m, v;
    input >> n >> w >> h;
    adjacency = Matrix(n);
    positions = Matrix(n, Vector(DIMS, 0));
    for (int i = 0; i < n; ++i) {
        //input >> positions[i][0] >> positions[i][1] >> m; // Read known positions
        input >> m;
        adjacency[i] = Vector(m);
        for (int j = 0; j < m; ++j) {
            input >> v;
            adjacency[i][j] = v;
        }
    }
    compute_cost();
    last_perturb.set(n+1, n+1, INT32_MAX);
}

void Circuit::print(ostream &output) {
    output << n << " " << adjacency.size() << endl;
    for (int i = 0; i < n; ++i) {
        output << i << ")";
        for (int j = 0; j < adjacency[i].size(); ++j) {
            output << " " << adjacency[i][j];
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

Matrix Circuit::generate_all_positions(mt19937 &generator) {
    Matrix all_positions = Matrix(w*h, Vector(DIMS));
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            all_positions[i*w + j] = {i,j};
        }
    }
    shuffle(all_positions.begin(), all_positions.end() , generator);
    return all_positions;
}


void Circuit::place_randomly(mt19937 &generator) {
    Matrix all_poistions = generate_all_positions(generator);
    positions = Matrix(all_poistions.begin(), all_poistions.begin() + n);
    compute_cost();
}

uint Circuit::euclidean2 (const int &i, const int &j) {
    uint distance = 0;
    for (int k = 0; k < DIMS; ++k) {
        distance += pow(positions[j][k] -  positions[i][k], 2);
    }
    return distance;
}

int Circuit::size() {
    return n;
}

uint Circuit::get_cost() {
    return cost;
}

uint Circuit::manhattan (const int &i, const int &j) {
    uint distance = 0;
    for (int k = 0; k < DIMS; ++k) {
        distance += abs(positions[j][k] -  positions[i][k]);
    }
    return distance;
}

void Circuit::compute_cost() {
    cost = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < adjacency[i].size(); ++j) {
            cost += DISTANCE(i, adjacency[i][j]);
        }
    }
}

uint Circuit::perturb(mt19937 &generator, uniform_int_distribution<uint> &distribution) {
    last_perturb.u = distribution(generator);
    last_perturb.v = distribution(generator);
    while (last_perturb.u == last_perturb.v)
        last_perturb.v = distribution(generator);
    last_perturb.cost = cost;
    cerr << last_perturb.cost << endl;
    for (int i = 0; i < adjacency[last_perturb.u].size(); ++i) {
        last_perturb.cost -= DISTANCE(last_perturb.u, adjacency[last_perturb.u][i]);
        last_perturb.cost += DISTANCE(last_perturb.v, adjacency[last_perturb.u][i]);
    }
    cerr << last_perturb.cost << endl;
    for (int i = 0; i < adjacency[last_perturb.v].size(); ++i) {
        last_perturb.cost -= DISTANCE(last_perturb.v, adjacency[last_perturb.v][i]);
        last_perturb.cost += DISTANCE(last_perturb.u, adjacency[last_perturb.v][i]);
    }
    cerr << last_perturb.cost << endl;
}

void Circuit::apply_perturb() {
    if (last_perturb.u < n) {
        cost = last_perturb.cost;
        swap(positions[last_perturb.u], positions[last_perturb.v]);
    }
 }

// void Circuit::place_cells(float temperature) {
//     place_randomly();
//     while (temperature > min_temperature) {
        
//     }
// }