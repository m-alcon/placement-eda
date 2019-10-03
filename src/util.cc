#include "util.h"

void parse(istream &input) {
    uint n, w, h;
    input >> n >> w >> h;
    int node, right, left;
    for (int i = 0; i < n; ++i) {
        input >> node >> right >> left;  
        cout << node << endl;  
    }
}