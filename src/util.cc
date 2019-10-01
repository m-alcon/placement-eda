#include "util.h"

void parse(istream &input) {
    uint n, w, h;
    input >> w >> h >> n;
    int node, right, left;
    for (int i = 0; i < n; ++i) {
        input >> node >> right >> left;  
        cout << node << endl;  
    }
}