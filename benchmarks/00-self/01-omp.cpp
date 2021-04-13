#include "../../include/barry/barry.hpp"
#include <chrono>

int main() {

    using namespace barry::counters;
    network::Network a(5, 5);

    a.set_data(new network::NetworkData(), true);
    a.D()->directed = true;

    network::NetModel netmod(1);
    
    network::rules_zerodiag(&netmod.rules);
    network::counter_edges(&netmod.counters);
    network::counter_ttriads(&netmod.counters);
    network::counter_idegree(&netmod.counters, {0});

    netmod.add_array(a);

    auto params = {-.5, .5, .2};

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

    printf("Likelihood: %.4f, duration: %.4f\n", ll, diff.count());

    return 0;

}