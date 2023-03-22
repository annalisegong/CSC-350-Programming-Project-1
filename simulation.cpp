#include <iostream>
using namespace std;

struct Process
{
    string processID; //p1, p2
    //bool active = false; 
    int a; //arrival time = random between 0 and 20
    int t; //total cpu time == burst time
    //int tt; //turn around time = burst time + wait time
};

//wt[] array of wait times for each process
//rt[] array of remaining times for each process
void findWaitTime(Process p[], int numOfPs, int wt[])
{
    int rt[numOfPs];
    //copies burst time into remaining time array
    for(int i = 0; i < numOfPs; i++)
    {
        rt[i] = p[i].t;
    }
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
            //arrival time of p < currTime & 0 < remainingTime < currT
            if( (p[j].a <= currT) && (rt[j] < min) && rt[j] > 0)
            {
                min = rt[j]; //update min SRT
                shortest = j; //update index for shortest p
                check = true;
            }
        }

        if (check == false)
        {
            currT++;
            continue;
        }
        //reduce remaining time by one
        rt[shortest]--;

        //update min
        min = rt[shortest];
        if(min == 0)
        {
            min = INT_MAX;
        }

        //if processes terminates
        if(rt[shortest] == 0)
        {
            complete++; //inc num of processes completed
            check = false;

            //find terminateTime of current process
            terminateTime = currT + 1;

            //calculate wt
            wt[shortest] = terminateTime - p[shortest].t - p[shortest].a;

            if(wt[shortest] < 0)
            {
                wt[shortest] = 0;
            }
        }
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
    int totalWT = 0;
    int totalTAT = 0;

    //find wt for all processes
    findWaitTime(p, numOfPs, wt);
    //find att for all processes
    findTAT(p, numOfPs, wt, tat);

    cout << " pID\t\t" 
        << "BT\t\t"
        << "WT\t\t"
        <<"TAT\t\t\n";

    //calculate total wt and total tat
    for(int i = 0; i < numOfPs; i++)
    {
        totalWT = totalWT + wt[i];
        totalTAT = totalTAT + tat[i];
        cout << " " << p[i].processID << "\t\t"
            << p[i].t << "\t\t " << wt[i] << "\t\t "
            << tat[i] << endl; 
    }

    cout << "\nAverage waiting time = " 
        << (float)totalWT / (float)numOfPs;
    cout << "\nAverage turn around time = " 
        << (float)totalTAT / (float)numOfPs << endl;
}

int main()
{
    Process p[] = { 
        {"p1", 0, 5},
        {"p2", 3, 1},
        {"p3", 2, 4},
        {"p4", 5, 10},
        {"p5", 9, 2}
    };

    int numOfPs = sizeof(p) / sizeof(p[0]);

    findAvgTime(p, numOfPs);
    return 0;
}