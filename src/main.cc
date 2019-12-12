#include "circuit.h"

void simulated_annealing(const float &t_0, const float &t_min, const float &alpha, const int &it_max,  Circuit &c) {
    random_device device;
    mt19937 generator(device());
    uniform_real_distribution<float> r_distribution(0,1);
    uniform_int_distribution<uint> i_distribution(0, c.size() - 1);

    float t = t_0;
    c.place_randomly(generator);
    while (t > t_min) {
        for (int it = 0; it < it_max; ++ it) {
            if (c.get_cost() > 500)
                break;
            uint diff_cost = c.get_cost() - c.perturb(generator, i_distribution);
            if (diff_cost < 0) {
                float r = r_distribution(generator);
                if (r < exp(-diff_cost/t))
                    c.apply_perturb();
            } else {
                c.apply_perturb();
            }
        }
        //break;
        t = alpha * t;
    }
}

int main () {
    // random_device device;
    // mt19937 generator(device());
    // uniform_real_distribution<float> r_distribution(0,1);

    Circuit c = Circuit(cin);
    //c.place_randomly(generator);
    simulated_annealing(0.5, 0.05, 0.9, 10000, c);
    //cerr << c.get_cost() << endl;
    c.graphviz(cout);
    return 0;
}