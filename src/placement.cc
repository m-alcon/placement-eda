#include "circuit.h"
#include <fstream>
#include <string>

void save_state(uint &count, Circuit &c) {
    ofstream save("data/sequence/" + to_string(count) + ".out");
    c.graphviz(save);
    ++count;
}

void simulated_annealing(const float &t_0, const float &t_min, const float &alpha, const uint &it_max, const uint &equilibrium_base, Circuit &c) {
    random_device device;
    mt19937 generator(device());
    uniform_real_distribution<float> real_distr(0,1);
    uniform_int_distribution<uint> size_distr(0, c.size() - 1);
    uniform_int_distribution<uint> nodes_distr(0, c.nodes() - 1);
    //uint saved = 0;
    float t = t_0;
    c.place_randomly(generator);
    //save_state(saved, c);
    while (t > t_min) {
        uint equilibrium = equilibrium_base*(1-t+t_min);
        cerr << t << " " << equilibrium << " " << it_max;
        int it = 0;
        int equilibrium_counter = 0;
        while (equilibrium_counter < equilibrium and it < it_max) {
            int diff_cost = c.perturb(generator, size_distr, nodes_distr) - c.get_cost();
            if (diff_cost < 0) {
                equilibrium_counter = 0;
                c.apply_perturb();
                //save_state(saved, c);
            } else {
                ++equilibrium_counter;
                float r = real_distr(generator);
                if (r < exp(-diff_cost/t)) {
                    c.apply_perturb();
                    //save_state(saved, c);
                }
            }
            ++it;
        }
        cerr << " " << it << " " << c.get_cost() << endl;
        t = alpha * t;
    }
    cerr << c.get_cost() << endl;
}

int main (int argc, char *argv[]) {
    float t_0 = 0.9;
    float t_min = 0.05;
    float alpha = 0.95;
    if (argc == 4) {
        ifstream input("data/input/" + string(argv[1]) + ".in");
        ofstream output("data/output/graphviz/" + string(argv[1]) + ".out");
        uint equilibrium = atoi(argv[2]);
        uint it_max = atoi(argv[3]);
        Circuit c = Circuit(false, input);
        simulated_annealing(0.8, 0.05, 0.9, it_max, equilibrium, c);
        //c.graphviz(output);
    } else {
        Circuit c = Circuit(false, cin);
        simulated_annealing(t_0, t_min, alpha, c.max_dimension()*pow(c.size(), 3), pow(c.size(),3), c);
        c.graphviz(cout);
    }
    return 0;
    
}