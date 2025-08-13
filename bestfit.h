#ifndef BESTFIT_H
#define BESTFIT_H

#include "memory_manager.h"

// Best fit memory allocation class
class BestFitMemory : public MemoryManager {
public:
    BestFitMemory(int total_units);
    ~BestFitMemory();

    int allocate_mem(int process_id, int num_units) override;
};

#endif
