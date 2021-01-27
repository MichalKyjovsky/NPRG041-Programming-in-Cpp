#include "data_aggregator.hpp"

int main() {
//    std::cout << "******************** DATA-AGGREGATOR - VERSION - 1.0 ********************" << std::endl;

    DataAggregator dataAggregator;

    dataAggregator.aggregator_load_data();
//    std::cout << "******************** LOADING DONE - VERSION - 1.0 ********************" << std::endl;
//    std::cout << "******************** COMPUTING - START - VERSION - 1.0 ********************" << std::endl;

    dataAggregator.evaluate_query_over_dataset();
//    std::cout << "******************** COMPUTING - END - VERSION - 1.0 ********************" << std::endl;
    return 0;
}
