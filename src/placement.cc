#include "circuit.h"

void simulated_annealing(const float &t_0, const float &t_min, const float &alpha, const uint &it_max, Circuit &c) {
    random_device device;
    mt19937 generator(device());
    uniform_real_distribution<float> real_distr(0,1);
    uniform_int_distribution<uint> size_distr(0, c.size() - 1);
    uniform_int_distribution<uint> nodes_distr(0, c.nodes() - 1);

    float t = t_0;
    c.place_randomly(generator);
    
    while (t > t_min) {
        uint not_upgrade_max = pow(c.size(),3)*(1-t+t_min);
        //cerr << t << " " << not_upgrade_max << " " << it_max;
        int it = 0;
        int not_upgrade = 0;
        while (not_upgrade < not_upgrade_max and it < it_max) {
            int diff_cost = c.perturb(generator, size_distr, nodes_distr) - c.get_cost();
            if (diff_cost < 0) {
                not_upgrade = 0;
                c.apply_perturb();
            } else {
                ++not_upgrade;
                float r = real_distr(generator);
                if (r < exp(-diff_cost/t))
                    c.apply_perturb();
            }
            ++it;
            //cerr << c.get_cost() << endl;
        }
        //cerr << " " << it << endl;
        
        t = alpha * t;
    }
    cerr << c.get_cost() << endl;
    //c.compute_cost();
    //cerr << c.get_cost() << endl;
}

int main () {
    Circuit c = Circuit(false,cin);
    simulated_annealing(0.8, 0.05, 0.9, c.max_dimension()*pow(c.size(),3), c);
    c.graphviz(cout);
    return 0;
}