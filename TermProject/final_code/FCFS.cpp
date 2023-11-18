#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    int response_time;
};

struct Processor {
    bool isAvailable;
    int availableAtTime;
};

void calculateMetrics(vector<Process>& processes, float& avg_turnaround_time, float& avg_waiting_time, float& avg_response_time, float& cpu_utilisation, float& throughput) {
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int total_response_time = 0;
    int max_completion_time = 0;
    int total_idle_time = 0;
    int min_arrival_time = processes[0].arrival_time;

    for (auto& process : processes) {
        process.turnaround_time = process.completion_time - process.arrival_time;
        process.waiting_time = process.turnaround_time - process.burst_time;
        process.response_time = process.start_time - process.arrival_time;

        total_turnaround_time += process.turnaround_time;
        total_waiting_time += process.waiting_time;
        total_response_time += process.response_time;

        max_completion_time = max(max_completion_time, process.completion_time);
    }

    int n = processes.size();
    avg_turnaround_time = (float)total_turnaround_time / n;
    avg_waiting_time = (float)total_waiting_time / n;
    avg_response_time = (float)total_response_time / n;
    cpu_utilisation = ((max_completion_time - total_idle_time) / (float)max_completion_time) * 100;
    throughput = float(n) / (max_completion_time - min_arrival_time);
}

void fcfsScheduling(vector<Process>& processes, vector<Processor>& processors) {
    queue<int> processQueue; // Queue to hold process indices

    // Sort processes based on arrival time
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrival_time < b.arrival_time;
    });

    // Initialize queue with process indices
    for (int i = 0; i < processes.size(); ++i) {
        processQueue.push(i);
    }

    int currentTime = 0;
    while (!processQueue.empty()) {
        for (auto& processor : processors) {
            if (processor.isAvailable && !processQueue.empty()) {
                int processIndex = processQueue.front();
                Process& currentProcess = processes[processIndex];

                if (currentProcess.arrival_time <= currentTime) {
                    currentProcess.start_time = currentTime;
                    currentProcess.completion_time = currentTime + currentProcess.burst_time;
                    currentTime = currentProcess.completion_time;

                    processor.isAvailable = false;
                    processor.availableAtTime = currentProcess.completion_time;

                    processQueue.pop();
                }
            }

            // Check if the processor has completed executing its process
            if (!processor.isAvailable && currentTime >= processor.availableAtTime) {
                processor.isAvailable = true;
            }
        }

        // Increment time
        currentTime++;
    }
}

int main() {
    int numProcesses;
    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    vector<Process> processes(numProcesses);
    vector<int> burst_remaining(numProcesses);
    vector<Processor> processors(1, {true, 0}); // Assuming single processor for FCFS

    for (int i = 0; i < numProcesses; i++) {
        cout << "Enter arrival time of process " << i + 1 << ": ";
        cin >> processes[i].arrival_time;
        cout << "Enter burst time of process " << i + 1 << ": ";
        cin >> processes[i].burst_time;
        processes[i].pid = i + 1;
        burst_remaining[i] = processes[i].burst_time;
        cout << endl;
    }

    fcfsScheduling(processes, processors);

    float avg_turnaround_time, avg_waiting_time, avg_response_time, cpu_utilisation, throughput;
    calculateMetrics(processes, avg_turnaround_time, avg_waiting_time, avg_response_time, cpu_utilisation, throughput);

    // Print the results
    cout << "\n#P\tAT\tBT\tST\tCT\tTAT\tWT\tRT\n" << endl;
    for (const Process &p : processes) {
        cout << p.pid << "\t" << p.arrival_time << "\t" << p.burst_time << "\t" << p.start_time << "\t" << p.completion_time << "\t" << p.turnaround_time << "\t" << p.waiting_time << "\t" << p.response_time << "\n" << endl;
    }

    cout << "Average Turnaround Time = " << avg_turnaround_time << endl;
    cout << "Average Waiting Time = " << avg_waiting_time << endl;
    cout << "Average Response Time = " << avg_response_time << endl;
    cout << "CPU Utilization = " << cpu_utilisation << "%" << endl;
    cout << "Throughput = " << throughput << " processes/unit time" << endl;

    return 0;
}
