#include "funt.h"

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

int main(){
    
}