#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include "assembly_line.h"

// a pipeline constructed by a doubly linked list  
void pipelineMove(Node*& head, Node*& tail, const int& input_rate) {
    if (head == nullptr) {
        std::cout << "Doubly-linked list is empty." << std::endl;
        return;
    }

    // Remove the final node
    Node* currentTail = tail;
    if (currentTail->prev != nullptr) {
        currentTail->prev->next = nullptr;
        tail = currentTail->prev;
        delete currentTail;
    } 
    else {
        // If there was only one node in the list
        delete head;
        head = nullptr;
    }

    // Add a new node at the head
    std::vector<int> newData = {};
    for(int i=0;i<input_rate;i++) newData.push_back(RAW_MATERIAL);
    Node* newNode = new Node(newData);
    newNode->next = head;
    if (head != nullptr) {
        head->prev = newNode;
    }
    head = newNode;
}

// Function to display the doubly-linked list
void displayDoublyLinkedList(Node* head, int time, bool done_proc) {
    Node* current = head;
    if(!done_proc) std::cout << std::endl <<"time:" << time << ": displaying all Node Data before: "<<std::endl;
    else           std::cout << std::endl <<"time:" << time << ": displaying all Node Data after: "<<std::endl;
    int i=0;
    while (current != nullptr) {
        std::cout << "Node" << i << " Data: " ;
        for (int value : current->items_hold) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
        current = current->next;
        i=i+1;
    }
        std::cout << std::endl;
}

// pipeline ready, each worker to work on the pipeline 
void workerProcess(Node* head, std::vector<Worker>& workerList, int num_workers, int worker_thru) {
    Node* current = head;
    int currentPosition = 0; // Start position from 1
    int currentWorker=0;
    for (int i=0;i<num_workers;i++ )

    while (current != nullptr) {
        while (currentPosition < workerList[currentWorker].pos) {
          current = current->next;
          currentPosition++;
        }
        while (currentPosition == workerList[currentWorker].pos && currentWorker<num_workers) {
            if(workerList[currentWorker].type == TYPE_A) {
                if(workerList[currentWorker].has_prod) {
                    if(workerList[currentWorker].count_down==0) { // only start a new one when worker is ready
                        current->items_hold.push_back(PARTIAL_PRODUCT);
                        workerList[currentWorker].has_prod=false;
                        for(int i=0;i<current->items_hold.size();i++) {
                             if(current->items_hold[i]==RAW_MATERIAL) {
                                 current->items_hold.erase(current->items_hold.begin() + i);
                                 workerList[currentWorker].count_down = worker_thru;
                                 workerList[currentWorker].has_prod = true; 
                                 break;
                             }
                        }
                    }
                 }
                 else {
                    for(int i=0;i<current->items_hold.size();i++) {
                         if(current->items_hold[i]==RAW_MATERIAL) {
                             current->items_hold.erase(current->items_hold.begin() + i);
                             workerList[currentWorker].count_down = worker_thru;
                             workerList[currentWorker].has_prod = true; 
                             break;
                         }
                    }
                 }
            }
            else { // workerList[currentWorker].type == TYPE_B
                if(workerList[currentWorker].has_prod) {
                    if(workerList[currentWorker].count_down==0) { // only start a new one when worker is ready
                        current->items_hold.push_back(FINAL_PRODUCT);
                        workerList[currentWorker].has_prod=false;
                        for(int i=0;i<current->items_hold.size();i++) {
                             if(current->items_hold[i]==PARTIAL_PRODUCT) {
                                 current->items_hold.erase(current->items_hold.begin() + i);
                                 workerList[currentWorker].count_down = worker_thru;
                                 workerList[currentWorker].has_prod = true; 
                                 break;
                             }
                        }
                    }
                 }
                 else {
                    std::cout << "current pos" <<  currentPosition <<std::endl;
                    std::cout << "before erase all contents in current node" << std::endl;
                    for (int item : current->items_hold) {
                        std::cout << item << " ";
                    }
                    std::cout << std::endl;
                    for(int i=0;i<current->items_hold.size();i++) {
                         if(current->items_hold[i]==PARTIAL_PRODUCT) {
                             current->items_hold.erase(current->items_hold.begin() + i);
                             workerList[currentWorker].count_down = worker_thru;
                             workerList[currentWorker].has_prod = true; 
                             break;
                         }
                    }
                    std::cout << "print out all contents in current node" << std::endl;
                    for (int item : current->items_hold) {
                        std::cout << item << " ";
                    }
                    std::cout << std::endl;
                 }
            }
            
            //std::cout << "Node Data (Position " << currentPosition << "): ";
            //for (int item : current->items_hold) {
            //    std::cout << item << " ";
            //}
            //std::cout << std::endl;
            currentWorker+=1;
        }
        current = current->next;
        currentPosition++;
    }
}

void worker_busy_countdown(std::vector<Worker> &workerList, int num_workers){
    for(int i=0;i<num_workers;i++) {
        std::cout << "worker"; 
        if(workerList[i].type) std::cout << "A";
        else                   std::cout << "B";
        std::cout << " pos" << workerList[i].pos << " count down: " << workerList[i].count_down <<std::endl;
        if(workerList[i].count_down>0) workerList[i].count_down = workerList[i].count_down - 1;
    }
}

int assembly_line(int num_simulated_cycles, int length_assembly_line, int num_workers, const int& input_rate, std::vector<Worker> &workerList) {
    //build a sim pipeline, and monitor the output of last stage
    Node* newNode = new Node();
    Node* head = newNode;
    Node* tail = newNode;
    for(int i = 0; i < length_assembly_line-1; i++){
        Node* newNode = new Node();
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    //sort the worker
    std::sort(workerList.begin(), workerList.end(), [](const Worker& a, const Worker& b) {
        return a.pos < b.pos;
    });
    int completed_prod_cnt=0;
    int worker_thru = 2;
    for(int i = 0; i < num_simulated_cycles; i++){
        for(int item : tail->items_hold){
            if(item == FINAL_PRODUCT) completed_prod_cnt+=1;
        }
        pipelineMove(head, tail, input_rate);
        worker_busy_countdown(workerList, num_workers); //count down for woker to match worker throughput def
        displayDoublyLinkedList(head,i, false);
        workerProcess(head, workerList, num_workers, worker_thru); // move pipeline forward, add a new raw material at the front
        displayDoublyLinkedList(head,i, true);
    }
    return completed_prod_cnt;

}
