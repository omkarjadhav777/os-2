#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct process{
    int pid,at,bt,ct,tat,wt,st,rt,pri,bt_remaining;
};

bool Atcomp(const process a,const process b){
    if(a.at!=b.at)
        return a.at< b.at;
    if(a.bt!=b.bt)
        return a.bt<b.bt;
        return a.pid<b.pid;
}

bool Btcomp(const process a,const process b){
    if(a.bt!=b.bt)
        return a.bt<b.bt;
    if(a.at!=b.at)
        return a.at< b.at;
        return a.pid<b.pid;
}

bool Pricomp(const process a,const process b){
    if(a.pri!=b.pri)
        return a.pri>b.pri;
    if(a.at!=b.at)
        return a.at< b.at;
    if(a.bt!=b.bt)
        return a.bt<b.bt;
        return a.pid<b.pid;
}

void FCFS(vector<process> ps, int p){ 
    cout<<"\nFCFS"<<endl;
    int currenttime=0;
    cout<<"\npid\tat \tbt \tst \tct \ttat\twt \trt ";
    for(int i=0;i<p;i++)
    {   ps[i].st=max(ps[i].at,currenttime);
        if(currenttime<ps[i].at)
            currenttime=ps[i].at;
        ps[i].ct=currenttime + ps[i].bt;
        ps[i].tat=ps[i].ct-ps[i].at;
        ps[i].wt=ps[i].tat- ps[i].bt;
        ps[i].rt=ps[i].st-ps[i].at;
        currenttime=ps[i].ct;
        cout<<"\n"<<ps[i].pid<<"\t"<<ps[i].at<<"\t"<<ps[i].bt<<"\t"<<ps[i].st<<"\t"<<ps[i].ct<<"\t"<<ps[i].tat<<"\t"<<ps[i].wt<<"\t"<<ps[i].rt<<"\t";
    }
}

void SJF(vector<process> ps, int p){
    cout<<"\nSJF"<<endl;
    int currenttime=0;
    cout<<"\npid\tat \tbt \tst \tct \ttat\twt \trt ";
    for(int i=0;i<p;)
    {
        ps[i].st=max(ps[i].at,currenttime);
        if(currenttime<ps[i].at)
            currenttime=ps[i].at;
        ps[i].ct=currenttime + ps[i].bt;
        ps[i].tat=ps[i].ct-ps[i].at;
        ps[i].wt=ps[i].tat- ps[i].bt;
        ps[i].rt=ps[i].st-ps[i].at;
        currenttime=ps[i].ct;
        cout<<"\n"<<ps[i].pid<<"\t"<<ps[i].at<<"\t"<<ps[i].bt<<"\t"<<ps[i].st<<"\t"<<ps[i].ct<<"\t"<<ps[i].tat<<"\t"<<ps[i].wt<<"\t"<<ps[i].rt<<"\t";
        i++;
        int j=i;
        if(j+1!=p){
             for (j;j<p;j++)
                {
                    if(ps[j].at>currenttime)
                    break;
                }
                sort(ps.begin()+i,ps.begin()+j,Btcomp);
        }
    }
}


void PRINP(vector<process> ps, int p){
    cout<<"\nPRINP"<<endl;
    int currenttime=0;
    cout<<"\npid\tat \tbt \tst \tct \ttat\twt \trt ";
    for(int i=0;i<p;)
    {
        ps[i].st=max(ps[i].at,currenttime);
        if(currenttime<ps[i].at)
            currenttime=ps[i].at;
        ps[i].ct=currenttime + ps[i].bt;
        ps[i].tat=ps[i].ct-ps[i].at;
        ps[i].wt=ps[i].tat- ps[i].bt;
        ps[i].rt=ps[i].st-ps[i].at;
        currenttime=ps[i].ct;
        cout<<"\n"<<ps[i].pid<<"\t"<<ps[i].at<<"\t"<<ps[i].bt<<"\t"<<ps[i].st<<"\t"<<ps[i].ct<<"\t"<<ps[i].tat<<"\t"<<ps[i].wt<<"\t"<<ps[i].rt<<"\t";
        i++;
        int j=i;
        if(j+1!=p){
             for (j;j<p;j++)
                {
                    if(ps[j].at>currenttime)
                    break;
                }
                sort(ps.begin()+i,ps.begin()+j,Pricomp);
        }
    }
}

void RR(vector<process>ps,int p)
{
    cout<<"\nRR"<<endl;
    int tq;
    cout<<"\nEnter the Time Quantum :";  cin>>tq;
    int currenttime=0;
    int completed=0;
    vector <bool> visited(p,false);
    queue <int> q;
    visited[0]=true;
    q.push(0);
    while(completed!=p){
       int idx= q.front();
       q.pop();

       if(ps[idx].bt_remaining==ps[idx].bt)
       {
         ps[idx].st=max(currenttime,ps[idx].at);
         currenttime=ps[idx].st;
       }
       if(ps[idx].bt_remaining-tq>0)
       {
         currenttime += tq;
         ps[idx].bt_remaining-= tq;
       }
       else
       { 
        currenttime+=ps[idx].bt_remaining;
        completed++;
        ps[idx].bt_remaining=0;

        ps[idx].ct=currenttime;
        ps[idx].tat=ps[idx].ct-ps[idx].at;
        ps[idx].wt=ps[idx].tat- ps[idx].bt;
        ps[idx].rt=ps[idx].st-ps[idx].at;

       }

       for(int i=0;i<p;i++)
       {
         if(ps[i].bt_remaining>0 && !visited[i] && ps[i].at<=currenttime)
         {
            q.push(i);
            visited[i]=true;
         }
       }

       if(ps[idx].bt_remaining>0)
       q.push(idx);

       if(q.empty()==true)
       {
         for(int i=1;i<p;i++)
         {
            if(ps[i].bt_remaining>0)
            {
                q.push(i);
                visited[i]=true;
            }
         }
       }
    }  
    cout<<"\npid\tat \tbt \tst \tct \ttat\twt \trt ";
    for(int i=0;i<p;i++)
    cout<<"\n"<<ps[i].pid<<"\t"<<ps[i].at<<"\t"<<ps[i].bt<<"\t"<<ps[i].st<<"\t"<<ps[i].ct<<"\t"<<ps[i].tat<<"\t"<<ps[i].wt<<"\t"<<ps[i].rt<<"\t";  

}






int main()
{
    int p;
    cout<<"\nEnter the no of processes:"; cin>>p;

    vector <process> ps(p);
    for(int i=0;i<p;i++)
    {   
        ps[i].pid=i;
        cout<<"\nEnter details of process  "<<i<<" (at,bt,pri):"; cin>>ps[i].at>>ps[i].bt>>ps[i].pri;
        ps[i].bt_remaining=ps[i].bt;

    }
    sort(ps.begin(),ps.end(),Atcomp);
    FCFS(ps,p);
    SJF(ps,p);
    PRINP(ps,p);
    RR(ps,p);
    return 0;
}