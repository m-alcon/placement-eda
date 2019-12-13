#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

#define DIMS 2
#define DISTANCE manhattan

typedef vector<int> Vector;
typedef vector<Vector> Matrix;

class Perturbation {
    public:
        uint u, v, cost;
        Perturbation() 
            : u(0), v(0), cost(INT32_MAX) {}
        Perturbation(const uint &u_, const uint &v_, const uint &cost_)
            : u(u_), v(v_), cost(cost_) {}
        void set(const uint &u_, const uint &v_, const uint &cost_);

};

class Circuit {
    public:
        Circuit (const bool &known_positions, istream &input);
        void print(ostream &output);
        void graphviz(ostream &output);
        void place_randomly(mt19937 &generator);
        uint perturb(mt19937 &generator, uniform_int_distribution<uint> &size_distr, uniform_int_distribution<uint> &nodes_distr);
        uint size();
        uint nodes();
        uint max_dimension();
        uint get_cost();
        void apply_perturb();
        void compute_cost();
    private:
        uint n, w, h;
        uint cost = INT32_MAX;
        Matrix adjacency, positions, all_positions;
        Perturbation last_perturb;

        void initialize_all_positions();
        uint euclidean2 (const int &i, const int &j);
        uint manhattan (const int &i, const int &j);
        
};