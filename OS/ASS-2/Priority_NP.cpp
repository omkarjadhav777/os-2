#include <iostream>
#include <vector>
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

    Process(int p, int at, int bt, int pri)
        : pno(p), arrivalTime(at), burstTime(bt), priority(pri), completionTime(0), turnaroundTime(0), waitingTime(0) {}

   

    static bool sortpri(const Process &a, const Process &b) //take const and with reference
    {
        if (a.priority != b.priority)
            return a.priority > b.priority;//we ahve sor in decreasing priority order
        if (a.arrivalTime != b.arrivalTime)
            return a.arrivalTime < b.arrivalTime;
        return a.pno < b.pno;
    }

    static bool sortarr(const Process &a, const Process &b)
    {
        if (a.arrivalTime != b.arrivalTime)
            return a.arrivalTime < b.arrivalTime;
        if (a.priority != b.priority)
            return a.priority > b.priority;
        return a.pno < b.pno;
    }
};

void calculateTimesPriorityNonPreemptive(std::vector<Process> &processes, int n)
{
    int currentTime = 0;
    int i = 0;
    for (auto & process : processes)
    {

        if (currentTime < process.arrivalTime)
            currentTime = process.arrivalTime;

        process.completionTime = currentTime + process.burstTime;
        process.turnaroundTime = process.completionTime - process.arrivalTime;
        process.waitingTime = process.turnaroundTime - process.burstTime;

        currentTime = process.completionTime;

        i++;
        if (i + 1 < n)

        {
            int j = i ;
            for (j = i; j < n; j++)
            {
                if (processes[j].arrivalTime > currentTime)
                    break;
            }

            std::sort(processes.begin() + i, processes.begin() + j, Process::sortpri);
        }
        
    }
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
    }
    std::sort(processes.begin(), processes.end(), Process::sortarr);
    calculateTimesPriorityNonPreemptive(processes, numProcesses);
    float avgwaitingTime=0;
    float avgturnaroundtime=0;
    std::cout << "Process\tArrivalTime\tBurstTime\tPriority\tCompletionTime\tTurnaroundTime\tWaitingTime\n";
    for (const auto &process : processes)
    {
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
