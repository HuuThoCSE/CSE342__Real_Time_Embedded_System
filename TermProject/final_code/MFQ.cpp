#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Structure for each process
struct Process {
    int pid; // Process ID
    int arrival_time; // Arrival time
    int burst_time; // Burst time (total execution time needed)
    int remaining_time; // Remaining burst time
    int start_time; // Start time
    int completion_time; // Completion time
    int waiting_time; // Waiting time
    int turnaround_time; // Turnaround time
    int response_time; // Response time
};

class MultilevelFeedbackQueueScheduler {
    vector<queue<Process>> queues; // Queues for different levels
    vector<Process> processes; // List of processes
    int num_levels; // Number of levels in the MFQ

public:
    MultilevelFeedbackQueueScheduler(int levels) : num_levels(levels) {
        queues.resize(levels); // Set up queues for each level
    }

    void addProcess(const Process& process) {
        processes.push_back(process); // Add process to list
        queues[0].push(process); // Add process to first level queue
    }

    void schedule() {
        // Assuming each level represents one time unit of execution before demotion
        int currentTime = 0;
        bool allQueuesEmpty = false;
        while (!allQueuesEmpty) {
            allQueuesEmpty = true;
            for (int level = 0; level < num_levels; ++level) {
                if (!queues[level].empty()) {
                    allQueuesEmpty = false;
                    Process& p = queues[level].front();
                    if (level == 0 || p.start_time != -1) { // If first level or process has started
                        if (p.start_time == -1) p.start_time = currentTime; // Set start time if not started
                        p.remaining_time--; // Decrease remaining time
                        if (p.remaining_time == 0) { // Process is complete
                            p.completion_time = currentTime + 1;
                            p.turnaround_time = p.completion_time - p.arrival_time;
                            p.waiting_time = p.turnaround_time - p.burst_time;
                            p.response_time = p.start_time - p.arrival_time;
                            for (auto &proc : processes) { // Update process in list
                                if (proc.pid == p.pid) {
                                    proc = p;
                                    break;
                                }
                            }
                            queues[level].pop(); // Remove process from queue
                        } else if (level < num_levels - 1) { // Move to next level if not last level
                            queues[level + 1].push(p); // Add to next level queue
                            queues[level].pop(); // Remove from current level
                        }
                    }
                    break; // Only process one process per time unit
                }
            }
            currentTime++;
        }
    }

    vector<Process> getProcesses() const {
        return processes;
    }
};

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    MultilevelFeedbackQueueScheduler scheduler(3); // Example: 3 levels in MFQ

    for (int i = 0; i < n; i++) {
        Process p;
        cout << "Enter arrival time of process " << i + 1 << ": ";
        cin >> p.arrival_time;
        cout << "Enter burst time of process " << i + 1 << ": ";
        cin >> p.burst_time;
        p.pid = i + 1;
        p.start_time = -1; // -1 indicates not started
        p.remaining_time = p.burst_time;
        scheduler.addProcess(p);
        cout << endl;
    }

    scheduler.schedule();

    vector<Process> completed_processes = scheduler.getProcesses();

    // Calculate metrics
    float total_turnaround_time = 0, total_waiting_time = 0, total_response_time = 0, cpu_utilisation = 0;
    int max_completion_time = 0;

    for (const auto& process : completed_processes) {
        total_turnaround_time += process.turnaround_time;
        total_waiting_time += process.waiting_time;
        total_response_time += process.response_time;
        max_completion_time = max(max_completion_time, process.completion_time);
    }

    float avg_turnaround_time = total_turnaround_time / n;
    float avg_waiting_time = total_waiting_time / n;
    float avg_response_time = total_response_time / n;
    float throughput = float(n) / max_completion_time;

    // Display results
    cout << "#P\tAT\tBT\tST\tCT\tTAT\tWT\tRT\t\n" << endl;
    for (const auto& process : completed_processes) {
        cout << process.pid << "\t"
             << process.arrival_time << "\t"
             << process.burst_time << "\t"
             << process.start_time << "\t"
             << process.completion_time << "\t"
             << process.turnaround_time << "\t"
             << process.waiting_time << "\t"
             << process.response_time << "\t"
             << "\n" << endl;
    }

    cout << "Average Turnaround Time = " << avg_turnaround_time << endl;
    cout << "Average Waiting Time = " << avg_waiting_time << endl;
    cout << "Average Response Time = " << avg_response_time << endl;
    cout << "Throughput = " << throughput << " process/unit time" << endl;

    return 0;
}