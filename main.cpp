//
// input 
//
#include <iostream>
#include <vector>
#include <cstdlib> // for std::atoi
#include "assembly_line.h"

int main(int argc, char* argv[]) {
    // Check if the number of command-line arguments is correct
    if (argc % 2 != 1) {
        std::cerr << "Usage: " << argv[0] << std::endl 
                                          << "<num_simulated_cycles: int>" << std::endl
                                          << "<length_assembly_line: int>" << std::endl
                                          << "<input_rate:           int> " << std::endl
                                          << "<num_workers:          int> " << std::endl
                                          << "<type:                 A or B>" << std::endl 
                                          << "<pos:                  int>" << std::endl;
        return 1; // Return error code 1
    }

    // Parse command-line arguments
    int num_simulated_cycles = std::atoi(argv[1]);
    int length_assembly_line = std::atoi(argv[2]);
    int input_rate = std::atoi(argv[3]);
    int num_workers = std::atoi(argv[4]);
    std::cout << "num_simulated_cycles " << num_simulated_cycles << std::endl;
    std::cout << "length_assembly_line " <<length_assembly_line << std::endl;
    std::cout << "input_rate" << input_rate << std::endl;
    std::cout << "num_workers " << num_workers << std::endl;
    std::vector<Worker> workerList;
    for(int i = 5; i < argc; i=i+2) {
        Worker* obj = new Worker(argv[i][0]=='A', std::atoi(argv[i+1]));
        workerList.push_back(*obj);
        std::cout << "Argument 5 (type): " << argv[i] << std::endl;
        std::cout << "Argument 6 (int): " << std::atoi(argv[i+1]) << std::endl;
    }

    int num_processed_elements = assembly_line(num_simulated_cycles, length_assembly_line, num_workers, input_rate, workerList);
    std::cout << num_processed_elements << std::endl;

    return 0; // Return success code 0
}
