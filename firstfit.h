#ifndef FIRSTFIT_H
#define FIRSTFIT_H

#include "memory_manager.h"

// First fit memory allocation class
class FirstFitMemory : public MemoryManager {
public:
    FirstFitMemory(int total_units);
    ~FirstFitMemory();

    int allocate_mem(int process_id, int num_units) override;
};

#endif
