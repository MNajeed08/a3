#include "firstfit.h"
#include <cstddef> // For NULL

// Constructor
FirstFitMemory::FirstFitMemory(int total_units) : MemoryManager(total_units) {}

// Destructor
FirstFitMemory::~FirstFitMemory() {}

// Allocate using first fit
int FirstFitMemory::allocate_mem(int process_id, int num_units) {
    Block* curr = head;
    int nodes_traversed = 0;

    while (curr != NULL) {
        nodes_traversed++;
        if (curr->process_id == -1 && curr->size >= num_units) {
            if (curr->size == num_units) {
                curr->process_id = process_id;
            } else {
                Block* nb = new Block;
                nb->start = curr->start + num_units;
                nb->size = curr->size - num_units;
                nb->process_id = -1;
                nb->next = curr->next;

                curr->size = num_units;
                curr->process_id = process_id;
                curr->next = nb;
            }
            return nodes_traversed;
        }
        curr = curr->next;
    }
    return -1;
}
