/*

Kết quả Exit time, turn Around time, waiting time, average turn around time, average waiting time của thuật toán SRTF là bao nhiêu dựa trên các thông số sau:

Process ID  Arrival time    Burst time
P1  3   1
P2  1   4
P3  4   2
P4  0   6
P5  2   3

*/

#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
};

bool compareArrival(process p1, process p2) { 
    return p1.arrival_time < p2.arrival_time; 
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    process p[n];
    int remaining_time[n];

    int total_turnaround_time = 0, total_waiting_time = 0, total_response_time = 0;
    int total_idle_time = 0, max_completion_time = 0, min_arrival_time = INT_MAX;

    cout << "Enter arrival time and burst time for each process:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Process " << i + 1 << ":" << endl;
        cout << "Arrival Time: ";
        cin >> p[i].arrival_time;
        if(p[i].arrival_time < min_arrival_time) {
            min_arrival_time = p[i].arrival_time;
        }
        cout << "Burst Time: ";
        cin >> p[i].burst_time;
        p[i].pid = i + 1;
        remaining_time[i] = p[i].burst_time;
    }

    sort(p, p + n, compareArrival);

    int current_time = 0;
    int completed = 0;
    while (completed != n) {
        int idx = -1;
        int min = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && remaining_time[i] < min && remaining_time[i] > 0) {
                min = remaining_time[i];
                idx = i;
            }
        }

        if (idx != -1) {
            if (remaining_time[idx] == p[idx].burst_time) {
                p[idx].start_time = current_time;
            }
            remaining_time[idx]--;
            current_time++;
            if (remaining_time[idx] == 0) {
                completed++;
                p[idx].completion_time = current_time;
                p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
                p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
                p[idx].response_time = p[idx].start_time - p[idx].arrival_time;

                total_turnaround_time += p[idx].turnaround_time;
                total_waiting_time += p[idx].waiting_time;
                total_response_time += p[idx].response_time;

                if (max_completion_time < current_time) {
                    max_completion_time = current_time;
                }
            }
        } else {
            current_time++;
            total_idle_time++;
        }
    }

    float avg_turnaround_time = (float)total_turnaround_time / n;
    float avg_waiting_time = (float)total_waiting_time / n;
    float avg_response_time = (float)total_response_time / n;
    float cpu_utilisation = ((max_completion_time - total_idle_time) / (float)max_completion_time) * 100;
    float throughput = float(n) / (max_completion_time - min_arrival_time);

    // Printing the results
    cout << "#P\tAT\tBT\tST\tCT\tTAT\tWT\tRT\n" << endl;
    for (int i = 0; i < n; i++) {
        cout << p[i].pid << "\t" << p[i].arrival_time << "\t" << p[i].burst_time << "\t" << p[i].start_time << "\t" << p[i].completion_time << "\t" << p[i].turnaround_time << "\t" << p[i].waiting_time << "\t" << p[i].response_time << "\t\n" << endl;
    }
    cout << "Average Turnaround Time = " << avg_turnaround_time << endl;
    cout << "Average Waiting Time = " << avg_waiting_time << endl;
    cout << "Average Response Time = " << avg_response_time << endl;
    cout << "CPU Utilization = " << cpu_utilisation << "%" << endl;
    cout << "Throughput = " << throughput << " process/unit time" << endl;

    return 0;
}