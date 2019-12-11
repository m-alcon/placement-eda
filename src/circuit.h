#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

#define DIMS 2
#define DISTANCE euclidean2

typedef vector<int> Vector;
typedef vector<Vector> Matrix;

class Perturbation {
    uint u, v, cost;
    Perturbation(const uint &u_, const uint &v_, const uint &cost_)
        : u(u_), v(v_), cost(cost_) {}
};

class Circuit {
    public:
        // Circuit (const uint &n_nodes)   
        //     : n(n_nodes), 
        //       adjacency(n_nodes, Vector (n_nodes)) {}
        Circuit (istream &input);
        void print(ostream &output);
        void graphviz(ostream &output);
        //void place_cells(float temperature);
        void place_randomly(mt19937 &generator);
        float perturb_cost();
        void apply_perturb();
        uint cost = INT32_MAX;
    private:
        uint n, w, h;
        Matrix adjacency, positions;
        Perturbation last_perturb;

        Matrix generate_all_positions(mt19937 &generator);
        uint euclidean2 (const int &i, const int &j);
        uint manhattan (const int &i, const int &j);
        void compute_cost();
};