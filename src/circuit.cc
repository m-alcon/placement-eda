#include "circuit.h"

void Perturbation::set (const uint &u_, const uint &v_, const uint &cost_) {
    u = u_;
    v = v_;
    cost = cost_;
}

Circuit::Circuit (const bool &known_positions, istream &input) {
    int m, v;
    input >> n >> w >> h;
    adjacency = Matrix(n);
    positions = Matrix(w*h, Vector(DIMS, 0));
    if (not known_positions) {
        for (int i = 0; i < n; ++i) {
            input >> m;
            adjacency[i] = Vector(m);
            for (int j = 0; j < m; ++j) {
                input >> v;
                adjacency[i][j] = v;
            }
        }
        initialize_all_positions();
    } else {
        for (int i = 0; i < n; ++i) {
            input >> positions[i][0] >> positions[i][1] >> m; // Read known positions
            adjacency[i] = Vector(m);
            for (int j = 0; j < m; ++j) {
                input >> v;
                adjacency[i][j] = v;
            }
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

void Circuit::initialize_all_positions() {
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            positions[i*w + j] = {i,j};
        }
    }
    
}


void Circuit::place_randomly(mt19937 &generator) {
    shuffle(positions.begin(), positions.end() , generator);
    compute_cost();
}

uint Circuit::euclidean2 (const int &i, const int &j) {
    uint distance = 0;
    for (int k = 0; k < DIMS; ++k) {
        distance += pow(positions[j][k] -  positions[i][k], 2);
    }
    return distance;
}

uint Circuit::size() {
    return w*h;
}

uint Circuit::nodes() {
    return n;
}

uint Circuit::max_dimension() {
    return max(w,h);
}

uint Circuit::get_cost() {
    return cost;
}

uint Circuit::manhattan (const int &i, const int &j) {
    uint distance = 0;
    for (int k = 0; k < DIMS; ++k) {
        distance += abs(positions[j][k] -  positions[i][k]);
    }
    //cerr << "d([" << positions[i][0] << " " << positions[i][1] << "], [" << positions[j][0] << " " << positions[j][1] << "]) = " << distance << endl;
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

uint Circuit::perturb(mt19937 &generator, uniform_int_distribution<uint> &size_distr, uniform_int_distribution<uint> &nodes_distr) {
    last_perturb.u = nodes_distr(generator);
    last_perturb.v = size_distr(generator);
    while (last_perturb.u == last_perturb.v)
        last_perturb.v = size_distr(generator);
    last_perturb.cost = cost;
    //cerr << last_perturb.u << " - " << last_perturb.v << endl;
    //cerr << positions[last_perturb.u][0] << "," << positions[last_perturb.u][1] << "  " << positions[last_perturb.v][0] << "," << positions[last_perturb.v][1] << endl;
    
    uint count_edge = 2;
    //if (adjacency[last_perturb.u].size() == 0 or adjacency[last_perturb.v].size() == 0)
    //   count_edge = 1;
    
    for (uint s : adjacency[last_perturb.u]) {
        if (last_perturb.v != s) {
            last_perturb.cost += count_edge*DISTANCE(last_perturb.v, s);
            last_perturb.cost -= count_edge*DISTANCE(last_perturb.u, s);
        }            
    }
    if (last_perturb.v < n) {
        for (uint t : adjacency[last_perturb.v]) {
            if (last_perturb.u != t) {
                last_perturb.cost += count_edge*DISTANCE(last_perturb.u, t);
                last_perturb.cost -= count_edge*DISTANCE(last_perturb.v, t);
            }
        }
    }
    //cerr << adjacency[last_perturb.u].size() << " " << adjacency[last_perturb.v].size() << " - " << last_perturb.cost << " " << cost << endl;
    return last_perturb.cost;
}

void Circuit::apply_perturb() {
    if (last_perturb.cost != INT32_MAX) {
        swap(positions[last_perturb.u], positions[last_perturb.v]);
        cost = last_perturb.cost;
        //cerr << last_perturb.cost << " == " << cost << endl;
    }
 }