#include <iostream>
#include <vector>
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
        void graphviz(ostream &output);
    private:
        uint n, w, h;
        Matrix adjacency, positions;
};