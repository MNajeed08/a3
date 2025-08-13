#include "simulation.h"
#include "firstfit.h"
#include "bestfit.h"
#include "memory_request.h"
#include <iostream>
#include <iomanip> // For setprecision

using namespace std;

// Run the full simulation and print stats
void run_simulation() {
    const int total_units = 128;    // 256 KB / 2 KB = 128 units
    const int requests = 10000;     // Number of requests to simulate

    // Create memory managers
    FirstFitMemory first_fit(total_units);
    BestFitMemory best_fit(total_units);

    // Create request generator that pre-schedules requests
    MemoryRequest generator(requests);

    // First fit stats
    double ff_total_fragments = 0.0;
    double ff_total_nodes = 0.0;
    int ff_alloc_requests = 0;
    int ff_denied_requests = 0;

    // Best fit stats
    double bf_total_fragments = 0.0;
    double bf_total_nodes = 0.0;
    int bf_alloc_requests = 0;
    int bf_denied_requests = 0;

    // Process each request
    for (int i = 0; i < requests; i++) {
        Request r = generator.generate_request();

        if (r.allocate) {
            // First fit allocation
            ff_alloc_requests++;
            int nodes_ff = first_fit.allocate_mem(r.process_id, r.num_units);
            if (nodes_ff == -1) {
                ff_denied_requests++;
            } else {
                ff_total_nodes += nodes_ff;
            }

            // Best fit allocation
            bf_alloc_requests++;
            int nodes_bf = best_fit.allocate_mem(r.process_id, r.num_units);
            if (nodes_bf == -1) {
                bf_denied_requests++;
            } else {
                bf_total_nodes += nodes_bf;
            }
        } else {
            // Deallocate from both managers
            first_fit.deallocate_mem(r.process_id);
            best_fit.deallocate_mem(r.process_id);
        }

        // Track fragments after each request
        ff_total_fragments += first_fit.fragment_count();
        bf_total_fragments += best_fit.fragment_count();
    }

    // Compute successful allocation counts
    int ff_success = ff_alloc_requests - ff_denied_requests;
    int bf_success = bf_alloc_requests - bf_denied_requests;

    cout << endl;
    cout << "End of First Fit Allocation" << endl;
    cout << fixed << setprecision(6);
    cout << "Average External Fragments Each Request: " << (ff_total_fragments / requests) << endl;
    cout << "Average Nodes Transversed Each Allocation: " << (ff_success > 0 ? ff_total_nodes / ff_success : 0.0) << endl;
    cout << "Percentage Allocation Requests Denied Overall: "
         << (ff_alloc_requests > 0 ? (static_cast<double>(ff_denied_requests) / ff_alloc_requests) * 100.0 : 0.0)
         << "%" << endl;

    cout << endl;
    cout << "End of Best Fit Allocation" << endl;
    cout << fixed << setprecision(6);
    cout << "Average External Fragments Each Request: " << (bf_total_fragments / requests) << endl;
    cout << "Average Nodes Transversed Each Allocation: " << (bf_success > 0 ? bf_total_nodes / bf_success : 0.0) << endl;
    cout << "Percentage Allocation Requests Denied Overall: "
         << (bf_alloc_requests > 0 ? (static_cast<double>(bf_denied_requests) / bf_alloc_requests) * 100.0 : 0.0)
         << "%" << endl;
}
