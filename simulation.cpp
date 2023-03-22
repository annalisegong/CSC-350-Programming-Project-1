#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

struct Process
{
    string processID; //p0 - p4
    int a; //arrival time = random between 0 and 20
    int t; //total cpu time == burst time random between 5 and 25
};

//wt[] array of wait times for each process
//rt[] array of remaining times for each process
void findWaitTime(Process p[], int numOfPs, int wt[])
{
    //create rt array to be size = number of processes
    int rt[numOfPs];
    //copies total cpu time into rt[] array
    for(int i = 0; i < numOfPs; i++)
    {
        rt[i] = p[i].t;
    }
    //
    int complete = 0;
    int currT = 0;
    int min = INT_MAX;
    int shortest = 0;
    int terminateTime;
    bool check = false;

    //run until all processes are completed
    while(complete != numOfPs)
    {
        //find process with SRT among proccesses
        for(int j = 0; j < numOfPs; j++)
        {
            //arrival time of p < currTime & 0 < remainingTime < min
            if( (p[j].a <= currT) && (rt[j] < min) && rt[j] > 0)
            {
                min = rt[j]; //update min SRT to be the total CPU time of process at index j
                shortest = j; //update index for shortest process
                check = true;
            }
        }
        //if no new process meets conditional above aka no updates to process w SRT
        if(check == false)
        {
            currT++; //increase current time
            continue;
        }
        //reduce remaining time of process with SRT by one
        rt[shortest]--; 

        //update min to be the current process with SRT
        min = rt[shortest];
        //if process with SRT is complete/terminates, reset min value
        if(min == 0)
        {
            min = INT_MAX;
        }

        //if processes terminates
        if(rt[shortest] == 0)
        {
            complete++; //inc num of processes completed
            check = false;//reset check

            //find terminateTime of current process
            terminateTime = currT + 1;

            //calculate wt of process that just terminated
            wt[shortest] = terminateTime - p[shortest].t - p[shortest].a;

            if(wt[shortest] < 0)
            {
                wt[shortest] = 0;
            }
        }
        //inc current time
        currT++;
    }
}

//calculate turn around time for each process and copy into tat array
void findTAT(Process p[], int numOfPs, int wt[], int tat[])
{
    for(int i = 0; i < numOfPs; i++)
    {
        tat[i] = p[i].t + wt[i];
    }
}

//function to calculate average times (wt and tat)
void findAvgTime(Process p[], int numOfPs)
{
    int wt[numOfPs];
    int tat[numOfPs];
    int totalCPU = 0;
    int totalTAT = 0;

    //find wt for all processes
    findWaitTime(p, numOfPs, wt);
    //find tat for all processes
    findTAT(p, numOfPs, wt, tat);

    //prints column titles
    cout << " pID\t\t" 
        << "Ai\t\t"
        << "Ti\t\t\n";

    //calculate total wt and total tat
    for(int i = 0; i < numOfPs; i++)
    {
        //sums up total CPU and TAT to find average later
        totalCPU = totalCPU + p[i].t;
        totalTAT = totalTAT + tat[i];
        //prints process id, arrival time, and total cpu time in correct columns
        cout << " " << p[i].processID << "\t\t"
            << p[i].a << "\t\t" << p[i].t << "\t\t " << endl; 
    }
    //calculates and prints average total CPU time and TAT
    cout << "\nAverage total CPU time = " 
        << (float)totalCPU / (float)numOfPs;
    cout << "\nAverage turn around time (ATT) = " 
        << (float)totalTAT / (float)numOfPs << endl;
}

int main()
{
    srand(time(0));
    //creates processes
    Process p[] = { 
        {"p0", (rand() % 21 ), 5 + (rand() % 25)},
        {"p1", (rand() % 21 ), 5 + (rand() % 25)},
        {"p2", (rand() % 21 ), 5 + (rand() % 25)},
        {"p3", (rand() % 21 ), 5 + (rand() % 25)},
        {"p4", (rand() % 21 ), 5 + (rand() % 25)}
    };
    
    int numOfPs = sizeof(p) / sizeof(p[0]);

    findAvgTime(p, numOfPs);
    return 0;
}