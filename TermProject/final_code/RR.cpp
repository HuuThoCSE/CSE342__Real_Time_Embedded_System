#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
    bool isStarted = false;
};

bool compareArrival(Process p1, Process p2) { 
    return p1.arrival_time < p2.arrival_time;
}

int main() {
    int n; // Number of processes
    cout << "Enter the number of processes: ";
    cin >> n;

    int num_cpu; // Number of CPUs
    cout << "Enter the number of CPUs: ";
    cin >> num_cpu;

    int tq; // Time Quantum
    cout << "Enter time quantum: ";
    cin >> tq;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter arrival time of process " << i + 1 << ": ";
        cin >> processes[i].arrival_time;
        cout << "Enter burst time of process " << i + 1 << ": ";
        cin >> processes[i].burst_time;
        processes[i].pid = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
    }

    // Sort processes based on arrival time
    sort(processes.begin(), processes.end(), compareArrival);

    int current_time = 0;
    int completed_processes = 0;
    int total_turnaround_time = 0, total_waiting_time = 0, total_response_time = 0;
    int max_completion_time = 0, total_idle_time = 0;
    queue<int> process_queue;

    while (completed_processes < n) {
        for (int i = 0; i < n; i++) {
            if (!processes[i].isStarted && processes[i].arrival_time <= current_time) {
                process_queue.push(i);
                processes[i].isStarted = true;
            }
        }

        for (int cpu = 0; cpu < num_cpu && !process_queue.empty(); cpu++) {
            int idx = process_queue.front();
            process_queue.pop();
            
            if (processes[idx].start_time == 0)
                processes[idx].start_time = current_time;

            int exec_time = min(tq, processes[idx].remaining_time);
            processes[idx].remaining_time -= exec_time;
            current_time += exec_time;

            if (processes[idx].remaining_time > 0)
                process_queue.push(idx);
            else {
                processes[idx].completion_time = current_time;
                processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
                processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
                processes[idx].response_time = processes[idx].start_time - processes[idx].arrival_time;
                completed_processes++;

                total_turnaround_time += processes[idx].turnaround_time;
                total_waiting_time += processes[idx].waiting_time;
                total_response_time += processes[idx].response_time;
                max_completion_time = max(max_completion_time, processes[idx].completion_time);
            }
        }

        if (process_queue.empty() && completed_processes < n) {
            current_time++;
            total_idle_time++;
        }
    }

    int n; // Number of processes
    cout << "Enter the number of processes: ";
    cin >> n;

    int num_cpu; // Number of CPUs
    cout << "Enter the number of CPUs: ";
    cin >> num_cpu;

    float avg_turnaround_time = (float)total_turnaround_time / n;
    float avg_waiting_time = (float)total_waiting_time / n;
    float avg_response_time = (float)total_response_time / n;
    float cpu_utilisation = ((max_completion_time - total_idle_time) / (float)max_completion_time) * 100;
    int min_arrival_time = processes[0].arrival_time;
    float throughput = float(n) / (max_completion_time - min_arrival_time);

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
