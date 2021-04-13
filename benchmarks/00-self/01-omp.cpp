#include "../../include/barry/barry.hpp"
#include <chrono>

int main() {

    using namespace barry::counters;
    network::Network a(5, 5);

    a.set_data(new network::NetworkData({1.0, 1.5, 0.0, 2.0, 1.0}, true), true);

    network::NetModel netmod(1);
    
    network::rules_zerodiag(&netmod.rules);
    network::counter_edges(&netmod.counters);
    network::counter_ttriads(&netmod.counters);
    network::counter_idegree(&netmod.counters, {0});
    network::counter_nodeicov(&netmod.counters, 0u);

    netmod.add_array(a);

    auto params = {-.5, .5, .2, 2.0};

    auto start = std::chrono::system_clock::now();
    double ll = netmod.likelihood_total(params, true);
    auto end = std::chrono::system_clock::now();

    std::chrono::duration< double > diff = end - start;

    #ifdef BARRY_USE_OMP
        printf("With OMP\n");
        #pragma omp parallel
        {
            #pragma omp single
            {
                printf("Running with %i threads\n", omp_get_num_threads());
                printf("Max number of threads: %i\n", omp_get_max_threads());
            }
        }
    #else
        printf("Without OMP\n");
    #endif

    printf("Likelihood: %.4f, duration: %.6f\n", ll, diff.count());

    auto z = netmod.support_fun.data.get_data(); 
    barry::CountsType dat(z);

    return 0;

}