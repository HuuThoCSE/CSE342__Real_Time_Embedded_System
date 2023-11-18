#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

struct Process {
    int pid;
    int priority;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    int response_time;
};

struct Processor {
    bool isBusy;
    int currentTask;
    int idle_time;
};

class MultipleQueueScheduler {
    vector<queue<Process>> queues; // Queues for each priority level
    vector<Processor> processors;  // Processors
    vector<Process> completed_processes; // List of completed processes for metrics calculation

public:
    MultipleQueueScheduler(int numPriorities, int numProcessors) {
        queues.resize(numPriorities);
        processors.resize(numProcessors, {false, -1, 0});
    }

    void addProcess(Process p) {
        queues[p.priority].push(p);
    }

    void schedule() {
        int currentTime = 0;
        while (anyQueueNotEmpty()) {
            for (auto& processor : processors) {
                if (!processor.isBusy) {
                    for (auto& q : queues) {
                        if (!q.empty()) {
                            Process p = q.front();
                            p.start_time = currentTime;
                            p.completion_time = currentTime + p.burst_time;
                            p.waiting_time = p.start_time - p.arrival_time;
                            p.turnaround_time = p.completion_time - p.arrival_time;
                            p.response_time = p.start_time - p.arrival_time;

                            processor.currentTask = p.pid;
                            processor.isBusy = true;

                            cout << "Processor " << &processor - &processors[0] << " is executing process " << p.pid << " at time " << currentTime << endl;

                            completed_processes.push_back(p);

                            q.pop();
                            break;
                        }
                    }
                }
            }

            // Update processors' state and increment time
            for (auto& processor : processors) {
                if (processor.isBusy) {
                    // Assuming each process completes in one unit of time
                    processor.isBusy = false;
                } else {
                    processor.idle_time++; // Increment idle time for idle processors
                }
            }

            currentTime++;
        }
    }

    const vector<Processor>& getProcessors() const {
        return processors;
    }

    const vector<Process>& getCompletedProcesses() const {
        return completed_processes;
    }

private:
    bool anyQueueNotEmpty() {
        return any_of(queues.begin(), queues.end(), [](const queue<Process>& q) { return !q.empty(); });
    }
};

int main() {
    int numPriorities, numProcessors, numProcesses;
    cout << "Enter the number of priority levels: ";
    cin >> numPriorities;
    cout << "Enter the number of CPUs: ";
    cin >> numProcessors;

    MultipleQueueScheduler scheduler(numPriorities, numProcessors);

    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    for (int i = 0; i < numProcesses; ++i) {
        Process p;
        p.pid = i + 1;
        cout << "Enter arrival time, burst time, and priority for process " << p.pid << ": ";
        cin >> p.arrival_time >> p.burst_time >> p.priority;
        p.priority = min(p.priority, numPriorities - 1); // Ensure priority is within bounds
        scheduler.addProcess(p);
    }

    scheduler.schedule();

    // Metrics calculation
    float total_turnaround_time = 0, total_waiting_time = 0, total_response_time = 0, total_idle_time = 0;
    int max_completion_time = 0, min_arrival_time = INT_MAX;

    for (const auto& processor : scheduler.getProcessors()) {
        total_idle_time += processor.idle_time;
    }

    for (const auto& process : scheduler.getCompletedProcesses()) {
        total_turnaround_time += process.turnaround_time;
        total_waiting_time += process.waiting_time;
        total_response_time += process.response_time;
        max_completion_time = max(max_completion_time, process.completion_time);
        min_arrival_time = min(min_arrival_time, process.arrival_time);
    }

    int n = scheduler.getCompletedProcesses().size();
    float avg_turnaround_time = total_turnaround_time / n;
    float avg_waiting_time = total_waiting_time / n;
    float avg_response_time = total_response_time / n;
    float cpu_utilisation = ((max_completion_time - total_idle_time) / (float)max_completion_time) * 100;
    float throughput = float(n) / (max_completion_time - min_arrival_time);

    // Display metrics
    cout << "\n#P\tAT\tBT\tST\tCT\tTAT\tWT\tRT\n" << endl;
    for (const auto& process : scheduler.getCompletedProcesses()) {
        cout << process.pid << "\t" << process.arrival_time << "\t" << process.burst_time << "\t" << process.start_time << "\t" << process.completion_time << "\t" << process.turnaround_time << "\t" << process.waiting_time << "\t" << process.response_time << "\n" << endl;
    }

    cout << "Average Turnaround Time = " << avg_turnaround_time << endl;
    cout << "Average Waiting Time = " << avg_waiting_time << endl;
    cout << "Average Response Time = " << avg_response_time << endl;
    cout << "CPU Utilization = " << cpu_utilisation << "%" << endl;
    cout << "Throughput = " << throughput << " processes/unit time" << endl;

    return 0;
}
