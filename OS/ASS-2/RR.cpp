#include <iostream>
#include <algorithm>
#include <queue>
#include <iomanip>
#include <climits>
using namespace std;

struct process_struct {
    int pid;
    int at;
    int bt;
    int ct, wt, tat, rt, start_time;
    int bt_remaining;
} ps[100];

bool comparatorAT(struct process_struct a, struct process_struct b) {
    int x = a.at;
    int y = b.at;
    return x < y;
}

bool comparatorPID(struct process_struct a, struct process_struct b) {
    int x = a.pid;
    int y = b.pid;
    return x < y;
}

int main() {
    //input taking
    int n, tq, total_idle_time = 0, length_cycle;
    float sum_tat = 0, sum_wt = 0, sum_rt = 0;

    cout << "Enter total number of processes: ";
    cin >> n;

    cout << "Enter arrival time and burst time for each process (separated by space):" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Process " << i << ": ";
        cin >> ps[i].at >> ps[i].bt;
        ps[i].bt_remaining = ps[i].bt;
        ps[i].pid = i;   //add bt renainig and pid as i

    }

    cout << "Enter time quantum: ";
    cin >> tq;  // ask for time quata

    // Sort structure based on arrival time in increasing order
    sort(ps, ps + n, comparatorAT);



//step 1: intialize required variables  currrent time,complted,queeue of processes or ready queueand  bool array of visted;

    int current_time = 0, completed = 0; 
    queue<int>q;    // 
    bool visited[100] = {false};

    
//step 2:    //push 0 in queue and set visted[0]=true;
    q.push(0);
    visited[0] = true;


//step 3: now start the while lool until all the proceses are complted!
    while (completed != n) {
        //step 4: set the next process index and pop the ques 
        int index = q.front();
        q.pop();

//step 5: three conditions for tracking the process
 
//condition:1  first time process is exeuting we have to set the start time then total idle time,current time
        if (ps[index].bt_remaining == ps[index].bt) {
            ps[index].start_time = max(current_time, ps[index].at);  // maxof current time and the arrival time
            total_idle_time += (current_time == 0) ? 0 : ps[index].start_time - current_time;   //if current time is 0 then 0 and else  start time - current time
            current_time = ps[index].start_time; //   current time will be start time
        }


//condition :2  either the process will have btremaing is not equal to 0 after subtrating the 
        if (ps[index].bt_remaining - tq > 0) {
            ps[index].bt_remaining -= tq;
            current_time += tq;
        } 
//condition 3: after the compltetion  
        else {
            current_time += ps[index].bt_remaining;
            ps[index].bt_remaining = 0;
            completed++;

            ps[index].ct = current_time;
            ps[index].tat = ps[index].ct - ps[index].at;
            ps[index].wt = ps[index].tat - ps[index].bt;
            ps[index].rt = ps[index].start_time - ps[index].at;

            sum_tat += ps[index].tat;
            sum_wt += ps[index].wt;
            sum_rt += ps[index].rt;
        }


//step 6: now  inert the processes which came in this peroid in system
        for (int i = 1; i < n; i++) {
            if (ps[i].bt_remaining > 0 && ps[i].at <= current_time && !visited[i]) {
                q.push(i);
                visited[i] = true; ///important
            }
        }
//step 7 : insert the cuurent proesess if it is not complted
        if (ps[index].bt_remaining > 0)
        {
            q.push(index);

        }
            
//if still the queue is empty but complted != n  then we need to push atlest one process 
//inside the queue so will travese the procees array and select the first proces we got whose bt remaing is greater than 0
//and make it visited  and break the loop
        if (q.empty()) {
            for (int i = 1; i < n; i++) {
                if (ps[i].bt_remaining > 0) {
                    q.push(i);
                    visited[i] = true; //important
                    break;
                }
            }
        }
    }

    int max_completion_time = INT_MIN;

    for (int i = 0; i < n; i++)
        max_completion_time = max(max_completion_time, ps[i].ct);
    length_cycle = max_completion_time - ps[0].at;

    

    float cpu_utilization = (float)(length_cycle - total_idle_time) / length_cycle;

    sort(ps, ps + n, comparatorPID);

    cout << "\nProcess No.\tAT\tCPU Burst Time\tStart Time\tCT\tTAT\tWT\tRT\n";
    for (int i = 0; i < n; i++)
        cout << i << "\t\t" << ps[i].at << "\t" << ps[i].bt << "\t\t" << ps[i].start_time << "\t\t" << ps[i].ct << "\t" << ps[i].tat << "\t" << ps[i].wt << "\t" << ps[i].rt << endl;
    cout << endl;

    cout << "\nAverage Turn Around time= " << (float)sum_tat / n;
    cout << "\nAverage Waiting Time= " << (float)sum_wt / n;
    cout << "\nAverage Response Time= " << (float)sum_rt / n;
    cout << "\nThroughput= " << n / (float)length_cycle;
    cout << "\nCPU Utilization(Percentage)= " << cpu_utilization * 100 << endl;

    return 0;
}