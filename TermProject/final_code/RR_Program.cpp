#include "funt.h"

void roundRobinScheduling() {
    int currentTime = 0;
    idleTime = 0; // Reset idle time
    queue<int> processQueue;

    while (true) {
        bool allDone = true;
        for (Process& process : processes) {
            if (!process.isCompleted()) {
                allDone = false;
                if (process.getArrivalTime() <= currentTime && !process.hasStarted()) {
                    processQueue.push(process.getPid());
                    process.setStartTime(currentTime);
                }
            }
        }

        if (allDone) break;

        if (!processQueue.empty()) {
            int processIndex = processQueue.front() - 1;
            processQueue.pop();

            Process& currentProcess = processes[processIndex];
            int timeSlice = min(quantumTime, currentProcess.getRemainingTime());
            currentProcess.setRemainingTime(currentProcess.getRemainingTime() - timeSlice);
            currentTime += timeSlice;

            if (currentProcess.getRemainingTime() > 0) {
                processQueue.push(currentProcess.getPid());
            } else {
                currentProcess.setCompletionTime(currentTime);
                currentProcess.setTurnaroundTime(currentTime - currentProcess.getArrivalTime());
                currentProcess.setWaitingTime(currentProcess.getTurnaroundTime() - currentProcess.getBurstTime());
                currentProcess.setResponseTime(currentProcess.getStartTime() - currentProcess.getArrivalTime());
            }
        } else {
            currentTime++;
            idleTime++;
        }
    }
}

int main() {
    testExample1(); // Add test processes
    printListProcess(); // Print Process
    roundRobinScheduling(); // Perform scheduling
    printResult(); // Print results
    return 0;
}
