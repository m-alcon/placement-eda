#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

#define DIMS 2

typedef vector<int> Vector;
typedef vector<Vector> Matrix;

class Circuit {
    public:
        Circuit (const uint &n_nodes)   
            : n(n_nodes), 
              adjacency(n_nodes, Vector (n_nodes)) {}
        Circuit (istream &input);
        void print(ostream &output);
        void place_cells(float temperature);
        void graphviz(ostream &output);
    private:
        uint n, w, h;
        float min_temperature = 0.1;
        Matrix adjacency, positions;
        void place_randomly();
        Matrix generate_all_positions();
};