#include "bits/stdc++.h"
using namespace std;

// // Number of processes
// const int P = 5;

// // Number of resources
// const int R = 4;

// // Request resources array in case of Immediate Request Grant Enquiry
// int request_resources[R] = {0};

// Function to find the need of each process
void calculateNeed(vector<vector<int>> &need, vector<vector<int>> &maxm,
                   vector<vector<int>> &allot, vector<int> &request_resources, int process_number)
{

    int P = allot.size();
    int R = allot[0].size();
    // Calculating Need of each P
    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < R; j++)
        {
            // Need of instance = maxm instance -
            //				 allocated instance
            need[i][j] = maxm[i][j] - allot[i][j];
        }
    }

    // In case of Immediate request, we subtract request resources from it
    if (process_number != -1)
    {
        for (size_t i = 0; i < R; i++)
        {
            need[process_number][i] -= request_resources[i];
        }
    }
}
void printNeed(vector<vector<int>> &need)
{
    // Printing Need for Each Process
    // 0 0 1 2 1 0 0 0 1 3 5 4 0 6 3 2 0 0 1 4 0 0 1 2 1 7 5 0 2 3 5 6 0 6 5 2 0 6 5 6 1 5 2 0
    // 4req 0 2 1 0
    int P = need.size();
    int R = need[0].size();
    cout << "Need Output" << endl;
    cout << "    ";
    for (size_t i = 0; i < R; i++)
    {
        cout << "R" << i + 1 << " ";
    }
    cout << endl;

    for (int i = 0; i < P; i++)
    {
        cout << "P" << i << "  ";
        // cout << "(";
        for (int j = 0; j < R; j++)
        {
            cout << need[i][j];
            if (j != R - 1)
            {
                cout << "  ";
            }
        }
        cout << endl;
    }
}

void printSafeSequence(vector<int> &safeSeq, int req)
{
    // If system is in safe state then
    // safe sequence will be as below
    int P = safeSeq.size();
    cout << "Safe state <";
    for (int i = 0; i < P; i++)
    {
        if (safeSeq[i] == req)
        {
            cout << "P" << safeSeq[i] << "req";
        }
        else
        {
            cout << "P" << safeSeq[i];
        }
        if (i != P - 1)
        {
            cout << ",";
        }
    }
    cout << ">" << endl;
}

// Function to find the system is in safe state or not
bool isSafe(vector<int> &avail, vector<vector<int>> &need,
            vector<vector<int>> &allot, vector<int> &safeSeq)
{
    int P = allot.size();
    int R = allot[0].size();

    // Mark all processes as infinish
    vector<bool> finish(P, 0);
    // bool finish[P] = {0};

    // Make a copy of available resources
    // int work[R];
    vector<int> work(R);
    for (int i = 0; i < R; i++)
        work[i] = avail[i];

    // While all processes are not finished
    // or system is not in safe state.
    int count = 0;
    while (count < P)
    {
        // Find a process which is not finish and
        // whose needs can be satisfied with current
        // work[] resources.
        bool found = false;
        for (int p = 0; p < P; p++)
        {
            // First check if a process is finished,
            // if no, go for next condition
            if (finish[p] == 0)
            {
                // Check if for all resources of
                // current P need is less
                // than work
                int j;
                for (j = 0; j < R; j++)
                    if (need[p][j] > work[j])
                        break;

                // If all needs of p were satisfied.
                if (j == R)
                {
                    // Add the allocated resources of
                    // current P to the available/work
                    // resources i.e.free the resources
                    for (int k = 0; k < R; k++)
                        work[k] += allot[p][k];

                    // Add this process to safe sequence.
                    safeSeq[count++] = p;

                    // Mark this p as finished
                    finish[p] = 1;

                    found = true;
                }
            }
        }

        // If we could not find a next process in safe
        // sequence.
        if (found == false)
        {
            return false;
        }
    }

    return true;
}

void askAllocation(vector<vector<int>> &allot)
{
    // int allot[][R] = {{0, 0, 1, 2},
    //                   {1, 0, 0, 0},
    //                   {1, 3, 5, 4},
    //                   {0, 6, 3, 2},
    //                   {0, 0, 1, 4}};

    int P = allot.size();
    int R = allot[0].size();
    // Resources allocated to processes
    cout << "Enter Allocation Matrix: " << endl;
    for (size_t i = 0; i < P; i++)
    {
        cout << "For Process " << i << ": " << endl;
        cout << "Enter " << R << " resources separated by space: ";
        for (size_t j = 0; j < R; j++)
        {
            cin >> allot[i][j];
        }
    }
}

void askMax(vector<vector<int>> &maxm)
{
    // to processes
    // int maxm[][R] = {{0, 0, 1, 2},
    //                  {1, 7, 5, 0},
    //                  {2, 3, 5, 6},
    //                  {0, 6, 5, 2},
    //                  {0, 6, 5, 6}};

    int P = maxm.size();
    int R = maxm[0].size();
    // Maximum R that can be allocated
    cout << "Enter Maximum Resource Matrix: " << endl;
    for (size_t i = 0; i < P; i++)
    {
        cout << "For Process " << i << ": " << endl;
        cout << "Enter " << R << " resources separated by space: ";
        for (size_t j = 0; j < R; j++)
        {
            cin >> maxm[i][j];
        }
    }
}

void askAvail(vector<int> &avail)
{
    // int avail[] = {1, 5, 2, 0};

    // Available instances of resources
    int R = avail.size();
    cout << "Enter Available Resource Matrix: " << endl;
    cout << "Enter " << R << " resources separated by space: ";
    for (size_t i = 0; i < R; i++)
    {
        cin >> avail[i];
    }
}

// Driver code
int main()
{
    while (true)
    {

        int P, R;
        cout << "Enter Number of Processes: ";
        cin >> P;
        cout << "Enter Number of Resources: ";
        cin >> R;

        // int request_resources[R] = {0};
        vector<int> request_resources(R, 0);
        vector<vector<int>> need(P, vector<int>(R));
        // int need[P][R];

        vector<int> processes(P);
        for (size_t i = 0; i < P; i++)
        {
            processes[i] = i;
        }
        // int processes[] = {0, 1, 2, 3, 4};

        // Resources allocated to processes
        vector<vector<int>> allot(P, vector<int>(R));
        // int allot[P][R];
        askAllocation(allot);
        cout << "-------------------------------------------" << endl;

        // Maximum R that can be allocated
        vector<vector<int>> maxm(P, vector<int>(R));
        // int maxm[P][R];
        askMax(maxm);
        cout << "-------------------------------------------" << endl;

        // Available instances of resources
        vector<int> avail(R);
        // int avail[R];
        askAvail(avail);
        cout << "-------------------------------------------" << endl;

        // To store safe sequence
        vector<int> safeSeq(P);
        // int safeSeq[P];

        char answer;

        // Function to calculate need matrix
        calculateNeed(need, maxm, allot, request_resources, -1);

        // Printing Need
        printNeed(need);

        while (true)
        {

            cout << "Press: " << endl;
            cout << "S or s for Safe State Enquiry" << endl;
            cout << "R or r for Immediate Request Grant Enquiry" << endl;
            cout << "N or n to enter new matrices" << endl;
            cout << "Q or q to quit" << endl;
            cin >> answer;
            if (answer == 'S' || answer == 's')
            {

                // Check system is in safe state or not
                if (isSafe(avail, need, allot, safeSeq))
                {
                    // Printing Safe Sequence normally
                    cout << "Yes, ";
                    printSafeSequence(safeSeq, -1);
                }
                else
                {
                    cout << "No, System is not in Safe State" << endl;
                }
            }
            else if (answer == 'R' || answer == 'r')
            {

                // Immediate Request
                int process_number;
                bool success = true;

                // asking for the process number
                cout << "Enter Process Number: ";
                cin >> process_number;

                // Asking for request resources
                cout << "Enter Request Resources: ";
                for (size_t i = 0; i < R; i++)
                {
                    cin >> request_resources[i];
                }

                // we need to check that requests is <= avail and need
                for (size_t i = 0; i < R; i++)
                {
                    if (request_resources[i] > need[process_number][i])
                    {
                        success = false;
                        break;
                    }
                    if (request_resources[i] > avail[i])
                    {
                        success = false;
                        break;
                    }
                }
                if (!success)
                {
                    cout << "No, Immediate Request Rejected" << endl;
                    continue;
                }

                // add to alloc, subtract from available and need
                for (size_t i = 0; i < R; i++)
                {
                    allot[process_number][i] += request_resources[i];
                    avail[i] -= request_resources[i];
                }

                // Function to calculate need matrix
                calculateNeed(need, maxm, allot, request_resources, process_number);

                // // Printing Need
                // printNeed(need);

                // Check system is in safe state or not
                if (isSafe(avail, need, allot, safeSeq))
                {
                    // Printing Safe Sequence normally
                    cout << "Yes, request can be granted with safe state. ";
                    printSafeSequence(safeSeq, process_number);
                }
                else
                {
                    cout << "No, System is not in Safe State" << endl;
                }
            }
            else if (answer == 'N' || answer == 'n')
            {
                break;
            }
            else if (answer == 'Q' || answer == 'q')
            {
                return 0;
            }
        }
    }

    return 0;
}
