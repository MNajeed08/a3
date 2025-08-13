#include "memory_manager.h"
#include <cstddef> // For NULL

// Constructor sets up one big free block
MemoryManager::MemoryManager(int total_units) {
    this->total_units = total_units;
    head = new Block;
    head->start = 0;
    head->size = total_units;
    head->process_id = -1;
    head->next = NULL;
}

// Destructor frees all blocks
MemoryManager::~MemoryManager() {
    Block* curr = head;
    while (curr != NULL) {
        Block* temp = curr;
        curr = curr->next;
        delete temp;
    }
}

// Deallocate memory for a process id
int MemoryManager::deallocate_mem(int process_id) {
    Block* curr = head;
    bool changed = false;

    while (curr != NULL) {
        if (curr->process_id == process_id) {
            curr->process_id = -1;
            changed = true;
        }
        curr = curr->next;
    }

    if (!changed) {
        return -1;
    }

    // Merge adjacent free blocks
    curr = head;
    while (curr != NULL && curr->next != NULL) {
        if (curr->process_id == -1 && curr->next->process_id == -1) {
            curr->size += curr->next->size;
            Block* temp = curr->next;
            curr->next = curr->next->next;
            delete temp;
        } else {
            curr = curr->next;
        }
    }

    return 1;
}

// Count small fragments (size 1 or 2)
int MemoryManager::fragment_count() const {
    int count = 0;
    Block* curr = head;
    while (curr != NULL) {
        if (curr->process_id == -1 && (curr->size == 1 || curr->size == 2)) {
            count++;
        }
        curr = curr->next;
    }
    return count;
}
