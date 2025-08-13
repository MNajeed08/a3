#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

// Structure for a memory block in the linked list
struct Block {
    int start;       // Starting unit number
    int size;        // Size in units
    int process_id;  // -1 means block is free
    Block* next;     // Pointer to next block
};

// Base class for memory allocation managers
class MemoryManager {
public:
    MemoryManager(int total_units);
    virtual ~MemoryManager();

    // Allocate memory using a specific strategy
    virtual int allocate_mem(int process_id, int num_units) = 0;

    // Deallocate memory for a process
    int deallocate_mem(int process_id);

    // Count the number of small free fragments
    int fragment_count() const;

protected:
    Block* head;     // Head of linked list
    int total_units; // Total units in memory
};

#endif
