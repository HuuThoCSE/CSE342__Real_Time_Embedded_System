#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string.h>
using namespace std;

struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
};

int main() {
    int n;
    struct process p[100];
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int total_response_time = 0;
    int is_completed[100];
    float avg_turnaround_time;
    float avg_waiting_time;
    float avg_response_time;

    memset(is_completed, 0, sizeof(is_completed));
    cout << setprecision(2) << fixed;
    cout << "Enter the number of processes: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "Enter arrival time of process " << i + 1 << ": ";
        cin >> p[i].arrival_time;
        cout << "Enter burst time of process " << i + 1 << ": ";
        cin >> p[i].burst_time;
        p[i].pid = i + 1;
        p[i].remaining_time = p[i].burst_time;
        p[i].start_time = -1; // initializing start time to -1
        cout << endl;
    }

    int current_time = 0;
    int completed = 0;
    while (completed != n) {
        int idx = -1;
        int mn = 10000000;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && is_completed[i] == 0) {
                if (p[i].remaining_time < mn) {
                    mn = p[i].remaining_time;
                    idx = i;
                }
                if (p[i].remaining_time == mn) {
                    if (p[i].arrival_time < p[idx].arrival_time) {
                        mn = p[i].remaining_time;
                        idx = i;
                    }
                }
            }
        }
        if (idx != -1) {
            if (p[idx].start_time == -1) {
                p[idx].start_time = current_time;
            }
            p[idx].remaining_time -= 1;
            current_time++;
            if (p[idx].remaining_time == 0) {
                p[idx].completion_time = current_time;
                p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
                p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
                p[idx].response_time = p[idx].start_time - p[idx].arrival_time;
                total_turnaround_time += p[idx].turnaround_time;
                total_waiting_time += p[idx].waiting_time;
                total_response_time += p[idx].response_time;
                completed++;
                is_completed[idx] = 1;
            }
        } else {
            current_time++;
        }
    }

    avg_turnaround_time = (float)total_turnaround_time / n;
    avg_waiting_time = (float)total_waiting_time / n;
    avg_response_time = (float)total_response_time / n;

    cout << endl << "Process\tAT\tBT\tST\tCT\tTAT\tWT\tRT\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].pid << "\t" << p[i].arrival_time << "\t" << p[i].burst_time << "\t" 
             << p[i].start_time << "\t" << p[i].completion_time << "\t" 
             << p[i].turnaround_time << "\t" << p[i].waiting_time << "\t" 
             << p[i].response_time << "\n";
    }

    cout << "Average Turnaround Time = " << avg_turnaround_time << endl;
    cout << "Average Waiting Time = " << avg_waiting_time << endl;
    cout << "Average Response Time = " << avg_response_time << endl;
}

/* 
AT - Arrival Time
BT - Burst Time
ST - Start Time
CT - Completion Time
TAT - Turnaround Time
WT - Waiting Time
RT - Response Time
*/
