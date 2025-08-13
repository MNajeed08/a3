#include "memory_request.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// Helper to fill schedule with paired alloc/dealloc with short lifetimes
MemoryRequest::MemoryRequest(int total_requests) {
    srand(static_cast<unsigned int>(time(0)));

    int requests = total_requests;
    schedule.resize(requests);
    index = 0;

    // Number of pairs we will create; keep some extra deallocs/idle slots
    int num_pairs = requests / 2;

    // Create a vector of available positions
    vector<int> avail;
    avail.reserve(requests);
    for (int i = 0; i < requests; i++) {
        avail.push_back(i);
    }

    // For each pid, pick an alloc position and a dealloc later position with short lifetime
    for (int pid = 1; pid <= num_pairs; pid++) {
        if (avail.size() < 2) {
            break;
        }

        // Pick alloc index from the first 70% of available slots to leave room
        int limit = static_cast<int>(avail.size() * 0.7);
        if (limit < 1) {
            limit = 1;
        }
        int pick_alloc_pos = rand() % limit;
        int alloc_idx = avail[pick_alloc_pos];
        avail.erase(avail.begin() + pick_alloc_pos);

        // Pick dealloc from a range after alloc with a preference for short lifetime
        int chosen_dealloc_idx = -1;
        for (size_t k = 0; k < avail.size(); k++) {
            if (avail[k] > alloc_idx) {
                chosen_dealloc_idx = static_cast<int>(k);
                break;
            }
        }

        if (chosen_dealloc_idx == -1) {
            // Fallback: pick the last element
            chosen_dealloc_idx = static_cast<int>(avail.size()) - 1;
        }

        // Pick a dealloc position within a short window after alloc if possible
        int start_pos = chosen_dealloc_idx;
        int end_pos = chosen_dealloc_idx;
        int dealloc_choice = start_pos + (rand() % (end_pos - start_pos + 1 + 1));
        if (dealloc_choice < 0) {
            dealloc_choice = 0;
        }
        if (dealloc_choice >= static_cast<int>(avail.size())) {
            dealloc_choice = static_cast<int>(avail.size()) - 1;
        }

        int dealloc_idx = avail[dealloc_choice];
        avail.erase(avail.begin() + dealloc_choice);

        // Record allocation
        schedule[alloc_idx].allocate = true;
        schedule[alloc_idx].process_id = pid;
        schedule[alloc_idx].num_units = 3 + (rand() % 8);

        // Record deallocation
        schedule[dealloc_idx].allocate = false;
        schedule[dealloc_idx].process_id = pid;
        schedule[dealloc_idx].num_units = 0;
    }

    // Fill any empty slots with harmless dealloc 0
    for (int i = 0; i < requests; i++) {
        if (schedule[i].process_id == 0 && schedule[i].num_units == 0) {
            schedule[i].allocate = false;
            schedule[i].process_id = 0;
            schedule[i].num_units = 0;
        }
    }
}

// Return next scheduled request
Request MemoryRequest::generate_request() {
    if (index >= static_cast<int>(schedule.size())) {
        Request r;
        r.allocate = false;
        r.process_id = 0;
        r.num_units = 0;
        return r;
    }
    return schedule[index++];
}
