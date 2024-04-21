#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to calculate remaining need for each process
vector<vector<int>> calculateRemainingNeed(const vector<vector<int>>& maxNeed, const vector<vector<int>>& allocated) {
    int processes = maxNeed.size();
    int resources = maxNeed[0].size();
    vector<vector<int>> remainingNeed(processes, vector<int>(resources)); //p*r
    for (int i = 0; i < processes; ++i) {
        transform(maxNeed[i].begin(), maxNeed[i].end(), allocated[i].begin(), remainingNeed[i].begin(), minus<int>());
    }
    return remainingNeed;
}

// Function to check if the current allocation is less than needed
bool isSafe(const vector<vector<int>>& remainingNeed, vector<int>& available, const vector<vector<int>>& allocated) {
    int processes = remainingNeed.size();
    int resources = remainingNeed[0].size();
    vector<int> work = available;
    vector<bool> finish(processes, false);
    vector<int> safeSequence;

    for (int count = 0; count < processes; count++) {
        bool found = false;
        for (int i = 0; i < processes; i++) {
            if (!finish[i]) {
                int j;
                found=true;
                
                for (j = 0; j < resources; j++) {
                     if (remainingNeed[i][j] > work[j])
                     {   found=false;
                         break;
                     }
                     
                     
                    
                }
                
                if(found)  {
                     for (int k = 0; k < resources; k++)
                        work[k] += allocated[i][k];
                        
                    safeSequence.push_back(i);
                    finish[i] = true;
                    break;
                    
                }
               
                
                   
                 
            
            }
        }
        if (!found) {
            cout << "Deadlock will occur!" << endl;
            return false;
        }
    }



    cout << "Safe Sequence: ";
    for (int i = 0; i < processes; ++i) {
        cout << "P" << safeSequence[i];
        if (i != processes - 1)
            cout << " -> ";
    }
    cout << endl;
    return true;
}

int main() {
    int processes, resources;
    cout << "Enter number of processes: ";
    cin >> processes;
    cout << "Enter number of resources: ";
    cin >> resources;

    vector<vector<int>> maxNeed(processes, vector<int>(resources));
    vector<vector<int>> allocated(processes, vector<int>(resources));
    vector<int> totalResources(resources);
    vector<int> available(resources);
    
    // Input maximum need and allocated resources for each process
    cout << "Enter maximum need for each process:" << endl;
    for (int i = 0; i < processes; ++i) {
        cout << "Process " << i << ": ";
        for (int j = 0; j < resources; ++j)
            cin >> maxNeed[i][j];
    }

    cout << "Enter allocated resources for each process:" << endl;
    for (int i = 0; i < processes; ++i) {
        cout << "Process " << i << ": ";
        for (int j = 0; j < resources; ++j)
            cin >> allocated[i][j];
    }

    // Input total resources
    cout << "Enter total number of resources: ";
    for (int i = 0; i < resources; ++i)
        cin >> totalResources[i];

    // Calculate available resources
    for (int i = 0; i < resources; ++i) {
        int sum=0;
        for(int j=0;j< processes ;j++)
        {
            sum=sum + allocated[j][i];
            
        }
        available[i]= totalResources[i]-sum;
    }

    // Calculate remaining need for each process
    vector<vector<int>> remainingNeed = calculateRemainingNeed(maxNeed, allocated);
    // Show remaining need and available resources
    cout << "Remaining Need for each process:" << endl;
    for (int i = 0; i < processes; ++i) {
        cout << "Process " << i << ": ";
        for (int j = 0; j < resources; ++j)
            cout << remainingNeed[i][j] << " ";
        cout << endl;
    }

    cout << "Available Resources: ";
    for (int i = 0; i < resources; ++i)
        cout << available[i] << " ";
    cout << endl;

    // Check if system is in a safe state
    isSafe(remainingNeed, available, allocated);

    return 0;
}
