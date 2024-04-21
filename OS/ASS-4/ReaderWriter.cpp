#include <iostream> 
#include <thread>  //for declaring treads and creating them
#include <mutex>   // for mutex db_lock and reader_count_lock
#include <vector>  //vector to store the readers and writers
#include <chrono>  // for  this_thread::sleep_for(chrono::milliseconds(rand() % 10000 + 500));
#include <ctime>   
#include <random>  // for (rand()%10000 +500)

using namespace std;

mutex db_lock;
mutex readers_count_lock;

int readers_count = 0;
int shared_variable = 0;
 
bool writerinthhouse=false;
int wid; //current writer id who is in database

void lock(mutex & mtx) {
    mtx.lock();
}

void unlock(mutex& mtx) {
    mtx.unlock();
}

void reader(int id) {
    cout << "(Reader " << id << " is trying to enter)" << endl;
    
    if(writerinthhouse)
    cout << "(Reader " << id << " is waiting in queue as writer-"<<wid<<" is writing in database !)" << endl;
    


    lock(readers_count_lock);

    readers_count++;
    if (readers_count == 1) {
        lock(db_lock);
    }
    
    unlock(readers_count_lock);

    // Reading
    this_thread::sleep_for(chrono::milliseconds(rand() % 10000 + 500));
    cout << "(Reader " << id << " has entered reading the value of shared variable [" << shared_variable << "] )" << endl;


    // Leave
    lock(readers_count_lock);

    readers_count--;
    if (readers_count == 0) {
        unlock(db_lock);
    }

    unlock(readers_count_lock);



    cout << "(Reader " << id << " leaves)" << endl;
}

void writer(int id) {
    // Simulate random wait time
    cout << "(Writer " << id << " is trying to enter)" << endl;
    // Try to enter
    if(readers_count >0)
    cout << "(Writer " << id << " is waiting in queue as readers are reading database !)" << endl;
    if(writerinthhouse)
    cout << "(Writer " << id << " is waiting in queue as writer-"<<wid<<" is writing in database !)" << endl;
    
    lock(db_lock);
    
    cout << "(Writer " << id << " has entered)" << endl;
    wid=id;
    writerinthhouse=true;
    
    for (int i = 0; i < 10000; i++) {
        shared_variable++;
    }
    cout << "(Writer " << id << " increments shared variable to [" << shared_variable << "] )" << endl;

    // Simulate random wait time
    this_thread::sleep_for(chrono::milliseconds(rand() % 20000 + 500));

    // Leave
    unlock(db_lock);
    cout << "(Writer " << id << " leaves)" << endl;
     writerinthhouse=false;
}




void initialize() {
    srand(time(nullptr)); 
    cout << "shared_variable value is initialized to 0" << endl << endl;
}

void addReader(vector<thread>& threads, int id) {
    threads.push_back(thread(reader, id));
}

void deleteReader(vector<thread>& threads) {
    if (!threads.empty()) {
        threads.back().join();
        threads.pop_back();
    } else {
        cout << "No reader to delete." << endl;
    }
}

void addWriter(vector<thread>& threads, int id) {
    threads.push_back(thread(writer, id));
}

void deleteWriter(vector<thread>& threads) {
    if (!threads.empty()) {
        threads.back().join();
        threads.pop_back();
    } else {
        cout << "No writer to delete." << endl;
    }
}

int main() {
    vector<thread> threads; //vector<thread> threads;

    // srand(time(nullptr));
    //cout << "shared_variable value is initialized to 0" << endl << endl;

    /*
    void addreader(vector<thread> & threads,int id){
        threads.push_back(thread(reader,id));
    

    void addwriter(vector<thread & threads,int id)
    {
        threads.push_back(thread(writer,id));
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
            cout<<"no writer thread to delete"
        }

    }


        }
    */  

    
    initialize();
    int id = 1;



    while (true) {
        cout << "Choose an option:\n 1. Add reader\n 2. Delete reader\n 3. Add writer\n 4. Delete writer\n 5. Exit\n";
        int option;
        cin >> option;

        switch (option) {
            case 1:
                addReader(threads, id++);
                break;
            case 2:
                deleteReader(threads);
                break;
            case 3:
                addWriter(threads, id++);
                break;
            case 4:
                deleteWriter(threads);
                break;
            case 5:
                for (auto& t : threads) {
                    t.join();
                }
                cout << "The value of shared variable is " << shared_variable << endl;
                return 0;
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    }
}
