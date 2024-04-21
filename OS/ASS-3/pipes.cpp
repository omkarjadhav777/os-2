#include <iostream>
#include <unistd.h>

#include <cstring>
using namespace std;
int main()
{
    int parentToChildPipe[2], childToParentPipe[2];
    int returnstatus1, returnstatus2;
    char parentMessage[100];
    char childMessage[100];
    char receivedMessage[100];
    returnstatus1 = pipe(parentToChildPipe);
    if (returnstatus1 == -1)
    {
        cerr << "Error: Unable to create parent-to-child pipe" << endl;
        return 1;
    }
    returnstatus2 = pipe(childToParentPipe);
    if (returnstatus2 == -1)
    {
        cerr << "Error: Unable to create child-to-parent pipe" << endl;
        return 1;
    }
    int pid = fork();
    if (pid < 0)
    {
        cerr << "Error: Fork failed" << endl;
        return 1;
    }
    else if (pid == 0)
    {
        while (true)
        {
            close(parentToChildPipe[1]);
            close(childToParentPipe[0]);
            read(parentToChildPipe[0], receivedMessage, sizeof(receivedMessage));
            cout << "Child (PID " << getpid() << "): Received from parent: " << receivedMessage
                 << endl;
            if (strcmp(receivedMessage, "stop") == 0)
            {
                cout << "Child (PID " << getpid() << "): Chat stopped" << endl;
                break;
            }
            cout << "Child (PID " << getpid() << "): Enter message for parent: ";
            cin.getline(childMessage, sizeof(childMessage));
            write(childToParentPipe[1], childMessage, strlen(childMessage) + 1);
        }
    }
    else
    {
        while (true)
        {
            close(parentToChildPipe[0]);
            close(childToParentPipe[1]);
            cout << "Parent (PID " << getpid() << "): Enter message for child: ";
            cin.getline(parentMessage, sizeof(parentMessage));
            write(parentToChildPipe[1], parentMessage, strlen(parentMessage) + 1);
            if (strcmp(parentMessage, "stop") == 0)
            {
                cout << "Parent (PID " << getpid() << "): Chat stopped" << endl;
                break;
            }
            read(childToParentPipe[0], receivedMessage, sizeof(receivedMessage));
            cout << "Parent (PID " << getpid() << "): Received from child: " << receivedMessage << endl;
        }
    }
    return 0;
}
