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
    int completionTime;
    int turnaroundTime;
    int waitingTime;

    // Constructor
    Process(int p, int at, int bt)
        : pno(p), arrivalTime(at), burstTime(bt) {}

    static bool sortburt(const Process &a, const Process &b)
    {
        if (a.burstTime != b.burstTime)
            return a.burstTime < b.burstTime;
        if (a.arrivalTime != b.arrivalTime)
            return a.arrivalTime < b.arrivalTime;
        return a.pno < b.pno;
    }

    static bool sortarr(const Process &a, const Process &b)
    {
        if (a.arrivalTime != b.arrivalTime)
            return a.arrivalTime < b.arrivalTime;
        if (a.burstTime != b.burstTime)
            return a.burstTime < b.burstTime;
        return a.pno < b.pno;
    }
};

void calculateTimes(std::vector<Process> &processes, int n)
{
    int currentTime = 0;
    int i = 0;
    for (auto &process : processes)
    {

        if (currentTime < process.arrivalTime)
            currentTime = process.arrivalTime;

        process.completionTime = currentTime + process.burstTime;
        process.turnaroundTime = process.completionTime - process.arrivalTime;
        process.waitingTime = process.turnaroundTime - process.burstTime;
        currentTime = process.completionTime;


     //imp portion
        i++; // i increment by 1
        if (i + 1 < n) 
        {
            int j = i; // j=i;
            for (j = i; j < n; j++)
            {
                if (processes[j].arrivalTime > currentTime)// arrival time should be less or equal to the current time
                    break;
            }
            sort(processes.begin() + i, processes.begin() + j, Process::sortburt); // sending the sortburt function declartion not excutatinon
        }



       
    }
}

int main()
{
    int numProcesses;
    std::cout << "Enter the number of processes: ";
    std::cin >> numProcesses;


    vector<Process> processes;
    
    for (int i = 0; i < numProcesses; ++i)
    {
        int p, at, bt;
        std::cout << "Enter process " << i + 1 << " details (pno arrivalTime burstTime): ";
        std::cin >> p >> at >> bt;
        processes.emplace_back(p, at, bt);
    }



    sort(processes.begin(), processes.end(), Process::sortarr);
    calculateTimes(processes, numProcesses);


    float avgwaitingTime = 0;
    float avgturnaroundtime = 0;



    cout << "\nProcess\tCT\tTAT\tWT\n";
    for (const auto &process : processes)
    {
        std::cout << process.pno << "\t" << process.completionTime
                  << "\t" << process.turnaroundTime << "\t" << process.waitingTime << "\n";
        avgturnaroundtime = avgturnaroundtime + process.turnaroundTime;
        avgwaitingTime = avgwaitingTime + process.waitingTime;
    
    }

    cout << "avgturnaround time: " << avgturnaroundtime / numProcesses << endl;
    cout << "avgwaiting time : " << avgwaitingTime / numProcesses;

    return 0;
}