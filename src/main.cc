#include "circuit.h"

void simulated_annealing(const float &t_0, const float &t_min, const float &alpha, Circuit &c) {
    random_device device;
    mt19937 generator(device());
    uniform_int_distribution<float> distribution(0,1);

    float t = t_0;
    c.place_randomly(generator);
    while (t > t_min) {
        float diff_cost = c.perturb_cost();
        if (diff_cost < 0) {
            float r = distribution(generator);
            if (r < exp(-diff_cost/t))
                c.apply_perturb();
        } else {
            c.apply_perturb();
        }

        t = alpha * t;
    }
}

int main () {
    Circuit c = Circuit(cin);
    c.graphviz(cout);
    return 0;
}