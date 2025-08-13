#ifndef MEMORY_REQUEST_H
#define MEMORY_REQUEST_H

#include <vector>

// Request record
struct Request {
    bool allocate;    // True for allocate, false for deallocate
    int process_id;   // Id of process
    int num_units;    // Units requested for allocate
};

// Request generator that pre-schedules pairs
class MemoryRequest {
public:
    MemoryRequest(int total_requests = 10000);
    Request generate_request();

private:
    std::vector<Request> schedule; // Preplanned schedule
    int index;                     // Next index to return
};

#endif
