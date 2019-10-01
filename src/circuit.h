#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> Vector;
typedef vector<Vector> Matrix;

class Circuit {
    public:
        Circuit (const uint &n_nodes)   
            : n(n_nodes), 
              adjacency(n_nodes, Vector (n_nodes)) {}
    private:
        uint n;
        Matrix adjacency;
};