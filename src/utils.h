#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void parse (istream &input) {
    uint n, w, h;
    input >> w >> h >> n;
    int node, right, left;
    for (int i = 0; i < n; ++i) {
        input >> node >> right >> left;    
    }
}