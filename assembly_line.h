#ifndef ASSEMBLY_LINE_H
#define ASSEMBLY_LINE_H

#define RAW_MATERIAL 0
#define PARTIAL_PRODUCT 1
#define FINAL_PRODUCT 2
#define TYPE_A true
#define TYPE_B false

class Worker {
    public:
    bool type; // true:A==0 false:B==1
    int pos;
    bool has_prod=false;
    int count_down=0;
    Worker(bool type, int pos): type(type),pos(pos),has_prod(false), count_down(0) {}
};

struct Node {
    std::vector<int> items_hold;
    Node* prev;
    Node* next;
    
    // Constructor to initialize a node
    Node() : prev(nullptr), next(nullptr) {}
    Node(const std::vector<int>& data) : items_hold(data), prev(nullptr), next(nullptr) {}

};

int assembly_line(int num_simulated_cycles, int length_assembly_line, int num_workers, const int& input_rate, std::vector<Worker> &workerList);

#endif // ASSEMBLY_LINE_H

