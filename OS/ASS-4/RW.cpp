#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <mutex>
#include <thread>
#include <ctime>
// #include <>

using namespace std;

mutex db;
mutex readers_lock;

int shared_variable=0;
int readers_count=0;

int wid;
bool writerinhouse=false;

void down(mutex & mtx)
{
    mtx.lock();
}


void up(mutex & mtx)
{
    mtx.unlock();
}

void reader(int id)
{
    cout<<"reader "<<id<<"is trying to enter"<<endl;
    if(writerinhouse)
    cout<<" writer "<<wid<<"is in the database reader "<<id <<"is waititng in queue"<<endl;
    

    down(readers_lock);
    readers_count++;
    if(readers_count==1)
    down(db);
    up(readers_lock);

    // this_thread::sleep_for(chrono::milliseconds(rand() % 10000 +500));
    cout<<"reader"<<id<<" has entered and readin the value of shared varibale as"<<shared_variable;


    down(readers_lock);
    readers_count--;
    if(readers_count==0)
    down(db);
    up(readers_lock);

    cout<<"\nreader"<<id<<"leaves";
    

}

void writer(int id)
{  
    cout<<"writer "<<id<<"is trying to enter"<<endl;
    if(writerinhouse)
    cout<<"\n writer "<<wid<<"is in the database writer "<<id <<"is waititng in queue"<<endl;
    if(readers_count>0)
    cout<<readers_count<<" readers are in database" <<"so writer "<<id <<"is waititng in queue"<<endl;


    
    down(db);
    wid=id;
    writerinhouse=true;
    
    this_thread::sleep_for(chrono::milliseconds(rand() %20000 +500));
    for(int i=0;i<10000;i++)
    shared_variable++;
    cout<<"\nreader"<<id<<" has entered and incremented the value of shared varibale as"<<shared_variable;
    up(db);
    cout<<"\nwriter"<<id<<"leaves";
}

void initialize(){
    srand(time(nullptr));
    cout<<"shared variable is initialized to 0"<<endl;
}

void addreader(vector<thread> & threads,int id)
{
    threads.push_back(thread(reader,id));
}

void addwriter(vector<thread> & threads,int id)
{
    threads.push_back(thread(writer,id));
}

void deletereader(vector<thread> & threads)
{
    if(!threads.empty())
    {
        threads.back().join();
        threads.pop_back();
    }
    else
    {
        cout<<"NO  writer thread to delete";
    }

}

void deletewriter(vector<thread> & threads)
{
    if(!threads.empty())
    {
        threads.back().join();
        threads.pop_back();
    }
    else
    {
        cout<<"NO  writer thread to delete";
    }

}

int main()
{
    vector<thread> threads;
   initialize();
    int id=1;
    while(true)
    {  cout << "Choose an option:\n 1. Add reader\n 2. Delete reader\n 3. Add writer\n 4. Delete writer\n 5. Exit\n";
        int option;
        cout<<"Choose an option :"; cin>>option;
        switch(option)
        {
            case 1:
            addreader(threads,id++);
            break;
            case 2:
            deletereader(threads);
            break;
            case 3:
            addwriter(threads,id++);
            break;
            case 4:
            deletewriter(threads);
            break;
            case 5:
            for(auto & thread: threads)
            {
                thread.join();
            }
            cout<<"\nThe vlaue of shared varible is :"<<shared_variable;
            return 0;
            break;
            default:
            cout<<"\ninvalid Option";
        }
       

    }
    return 0;
}