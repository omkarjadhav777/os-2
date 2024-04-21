#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
class Process
{
public:
    int pno;
    int arrivalTime;
    int burstTime;
    int priority;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int bursttimeremaining;

    Process(int p, int at, int bt, int pri)
        : pno(p), arrivalTime(at), burstTime(bt), priority(pri), completionTime(0), turnaroundTime(0), waitingTime(0) {}

    // Comparison function for sorting by priority
    static bool sortpri(const Process &a, const Process &b)
    {
        if (a.priority != b.priority)
            return a.priority > b.priority;
        if (a.arrivalTime != b.arrivalTime)
            return a.arrivalTime < b.arrivalTime;
        return a.pno < b.pno;
    }

    // Comparison function for sorting by arrival time
    static bool sortarr(const Process &a, const Process &b)
    {
        if (a.arrivalTime != b.arrivalTime)
            return a.arrivalTime < b.arrivalTime;
        if (a.priority != b.priority)
            return a.priority > b.priority;
        return a.pno < b.pno;
    }
};

struct ComparePriority {
    bool operator()(const Process &a, const Process &b) {
        return a.priority < b.priority;
    }
};

std::queue<Process> calculateTimesPriorityPreemptive(std::vector<Process> &processes, int n)
{
    priority_queue<Process, std::vector<Process>, ComparePriority> pq;
    std::queue<Process>bq;
    int currentTime = 0;
    int completedProcesses = 0;
    

    while (completedProcesses < n) {
        for (int i = 0; i < processes.size(); ++i) {
            if (processes[i].arrivalTime <= currentTime ) {
                pq.push(processes[i]);
             processes.erase(processes.begin() + i);
            }
        }

        if (!pq.empty()) {
            Process currentProcess = pq.top();
            pq.pop();

            int execTime = std::min(currentProcess.burstTime, 1); // Execute for 1 unit of time
            currentTime += execTime;
            currentProcess.bursttimeremaining -= execTime;

            if (currentProcess.bursttimeremaining == 0) {
                currentProcess.completionTime = currentTime;
                currentProcess.turnaroundTime = currentProcess.completionTime - currentProcess.arrivalTime;
                currentProcess.waitingTime = currentProcess.turnaroundTime - currentProcess.burstTime;
                completedProcesses++;
                bq.push(currentProcess);
            } else {
                pq.push(currentProcess);
            }
        } else {
            currentTime++;
        }
    }
    return bq;
}

int main()
{
    int numProcesses;
    std::cout << "Enter the number of processes: ";
    std::cin >> numProcesses;

    std::vector<Process> processes;
    for (int i = 0; i < numProcesses; ++i)
    {
        int p, at, bt, pri;
        std::cout << "Enter process " << i + 1 << " details (pno arrivalTime burstTime priority): ";
        std::cin >> p >> at >> bt >> pri;
        processes.emplace_back(p, at, bt, pri);
        processes[i].bursttimeremaining=bt;
    }
    std::sort(processes.begin(), processes.end(), Process::sortarr);
    std::queue<Process> bq = calculateTimesPriorityPreemptive(processes, numProcesses);

    std::cout << "Process\tArrivalTime\tBurstTime\tPriority\tCompletionTime\tTurnaroundTime\tWaitingTime\n";
    // Traverse the queue by dequeuing elements until it becomes empty

    float avgwaitingTime=0;
    float avgturnaroundtime=0;
    while (!bq.empty()) {
        Process process = bq.front(); // Get the front element
        bq.pop(); // Remove the front element
        std::cout << process.pno << "\t" << process.arrivalTime << "\t\t" << process.burstTime << "\t\t"
                  << process.priority << "\t\t" << process.completionTime << "\t\t"
                  << process.turnaroundTime << "\t\t" << process.waitingTime << "\n";
                  avgturnaroundtime=avgturnaroundtime + process.turnaroundTime;
                  avgwaitingTime=avgwaitingTime + process.waitingTime;
    }
     cout << "avgturnaround time: " << avgturnaroundtime / numProcesses << endl;
    cout << "avgwaiting time " << avgwaitingTime / numProcesses;


    return 0;
}
