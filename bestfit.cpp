#include "bestfit.h"
#include <cstddef> // For NULL

// Constructor
BestFitMemory::BestFitMemory(int total_units) : MemoryManager(total_units) {}

// Destructor
BestFitMemory::~BestFitMemory() {}

// Allocate using best fit
int BestFitMemory::allocate_mem(int process_id, int num_units) {
    Block* curr = head;
    Block* best = NULL;
    int nodes_traversed = 0;
    int best_size = total_units + 1;

    while (curr != NULL) {
        nodes_traversed++;
        if (curr->process_id == -1 && curr->size >= num_units) {
            if (curr->size < best_size) {
                best_size = curr->size;
                best = curr;
            }
        }
        curr = curr->next;
    }

    if (best == NULL) {
        return -1;
    }

    if (best->size == num_units) {
        best->process_id = process_id;
    } else {
        Block* nb = new Block;
        nb->start = best->start + num_units;
        nb->size = best->size - num_units;
        nb->process_id = -1;
        nb->next = best->next;

        best->size = num_units;
        best->process_id = process_id;
        best->next = nb;
    }
    return nodes_traversed;
}
