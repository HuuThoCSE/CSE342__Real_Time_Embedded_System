#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int numCPU = 2; // Default number of CPUs
int quantumTime = 2; // Default quantum time
int idleTime = 0; // Idle time of CPU

class Process {
private:
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int start_time = 0;
    int completion_time = 0;
    int turnaround_time = 0;
    int waiting_time = 0;
    int response_time = 0;
    bool isStarted = false;

public:
    Process(int id, int arrival, int burst) 
    : pid(id), arrival_time(arrival), burst_time(burst), remaining_time(burst) {}

    // Getters and setters
    int getPid() const { return pid; }
    int getArrivalTime() const { return arrival_time; }
    int getBurstTime() const { return burst_time; }
    int getRemainingTime() const { return remaining_time; }
    int getStartTime() const { return start_time; }
    int getCompletionTime() const { return completion_time; }
    int getTurnaroundTime() const { return turnaround_time; }

    void setRemainingTime(int time) { remaining_time = time; }
    void setStartTime(int time) { if (!isStarted) { start_time = time; isStarted = true; }}
    void setCompletionTime(int time) { completion_time = time; }
    void setTurnaroundTime(int time) { turnaround_time = time; }
    void setWaitingTime(int time) { waiting_time = time; }
    void setResponseTime(int time) { response_time = time; }

    bool isCompleted() const { return remaining_time == 0; }
    bool hasStarted() const { return isStarted; }
};

vector<Process> processes;

void testExample1(){
    numCPU = 2;
    quantumTime = 3;

    // add process
    processes.push_back(Process(1, 3, 1));
    processes.push_back(Process(2, 1, 4));
    processes.push_back(Process(3, 4, 2));
    processes.push_back(Process(4, 0, 6));
    processes.push_back(Process(5, 2, 3));
}

void printListProcess(){
    // Print infomation process
    cout << "Number of CPUs: " << numCPU << ", Quantum Time: " << quantumTime << endl;
    for (const auto& p : processes) {
        cout << "Process ID: " << p.getPid() << ", Arrival Time: " << p.getArrivalTime() << ", Burst Time: " << p.getBurstTime() << endl;
    }
}

void printResult(){
    float totalTurnaroundTime = 0, totalWaitingTime = 0, totalResponseTime = 0;

    // Print the header for the table
    cout << "#P\tAT\tBT\tST\tCT\tTAT\tWT\tRT\n" << endl;

    for (const auto &process : processes) {
        int turnaroundTime = process.getCompletionTime() - process.getArrivalTime();
        int waitingTime = turnaroundTime - process.getBurstTime();
        int responseTime = process.getStartTime() - process.getArrivalTime();

        cout << process.getPid() << "\t"
             << process.getArrivalTime() << "\t"
             << process.getBurstTime() << "\t"
             << process.getStartTime() << "\t"
             << process.getCompletionTime() << "\t"
             << turnaroundTime << "\t"
             << waitingTime << "\t"
             << responseTime << "\n" << endl;

        totalTurnaroundTime += turnaroundTime;
        totalWaitingTime += waitingTime;
        totalResponseTime += responseTime;
    }

    float avgTurnaroundTime = totalTurnaroundTime / processes.size();
    float avgWaitingTime = totalWaitingTime / processes.size();
    float avgResponseTime = totalResponseTime / processes.size();

    cout << "Average Turnaround Time = " << avgTurnaroundTime << endl;
    cout << "Average Waiting Time = " << avgWaitingTime << endl;
    cout << "Average Response Time = " << avgResponseTime << endl;

    // Calculate and print CPU Utilization and Throughput
    int totalTime = processes.back().getCompletionTime(); // Thời gian lập lịch tổng cộng
    float cpuUtilization = (float)(totalTime - idleTime) / totalTime * 100;
    float throughput = (float)processes.size() / totalTime;

    cout << "CPU Utilization = " << cpuUtilization << "%" << endl;
    cout << "Throughput = " << throughput << " processes/unit time" << endl;
}