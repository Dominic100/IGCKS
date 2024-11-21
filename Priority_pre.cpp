#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstdint>

std::vector<int> returnATList(std::vector<int> at, int time) {
    std::vector<int> listAT;
    for(int i=0; i<at.size(); i++) {
        if(at[i]==time) {
            listAT.push_back(i);
        }
    }

    return listAT;
}

bool areProcessesDone(std::vector<int> rt) {
    for(int i=0; i<rt.size(); i++) {
        if(rt[i]!=0) {
            return false;
        }
    }

    return true;
}

void printGantt(std::queue<int> runningq, std::queue<int> ganttTimes) {
    std::cout<<"Gantt Chart:"<<std::endl;
    while(!runningq.empty()) {
        std::cout<<runningq.front()<<"\t";
        runningq.pop();
    }
    std::cout<<std::endl;
    while(!ganttTimes.empty()) {
        std::cout<<ganttTimes.front()<<"\t";
        ganttTimes.pop();
    }
}

void run(int n) {
    std::vector<int> at(n), bt(n), priority(n), ct(n), tat(n), wt(n), rt(n), responset(n);
    std::priority_queue<std::pair<int, int>> pq;
    std::queue<int> ganttTimes, runningq;

    for(int i=0; i<n; i++) {
        responset[i]=INT16_MAX;
        std::cout<<"Enter arrival time, burst time and priority for process "<<i+1<<": "<<std::endl;
        std::cin>>at[i]>>bt[i]>>priority[i];
    }

    for(int i=0; i<n; i++) {
        if(at[i]<0 || bt[i]<=0) {
            std::cout<<"Invalid input!"<<std::endl;
            return;
        }
    }

    rt=bt;

    int prevTime=0, time=0, index=0, done=*std::min_element(at.begin(), at.end());
    std::pair<int, int> indexPair;
    if(done!=0) {
        prevTime=time;
        time+=done;
        std::cout<<time<<std::endl;
        ganttTimes.push(time);
        runningq.push(-1);
    }
    std::vector<int> listAT=returnATList(at, done);
    for(int i=0; i<listAT.size(); i++) {
        pq.push(std::pair<int, int>(priority[listAT[i]], listAT[i]));
    }

    while(!areProcessesDone(rt)) {
        if(!pq.empty()) {
            indexPair=pq.top();
            index=indexPair.second;
            pq.pop();

            prevTime=time;
            time++;
            rt[index]--;

            ganttTimes.push(time);
            runningq.push(index);

            if(rt[index]!=0) {
                pq.push(indexPair);
            }

            for(int i=0; i<n; i++) {
                if(at[i]==time) {
                    pq.push(std::pair<int, int>(priority[i], i));
                }
            }
        }
        else {
            prevTime=time;
            time++;

            for(int i=0; i<n; i++) {
                if(at[i]==time) {
                    pq.push(std::pair<int, int>(priority[i], i));
                    continue;
                }
            }

            ganttTimes.push(time);
            runningq.push(-1);
        }
    }

    printGantt(runningq, ganttTimes);

    std::queue<int> tempGanttTimes, tempRunningq;

    tempGanttTimes=ganttTimes;
    tempRunningq=runningq;
    prevTime=0;

    while(!tempGanttTimes.empty()) {
        if(tempRunningq.front()!=-1) {
            int i=tempRunningq.front();
            ct[i]=tempGanttTimes.front();

            if(responset[i]>(prevTime - at[i])) {
                responset[i]=prevTime-at[i];
            }
        }

        prevTime=tempGanttTimes.front();
        tempGanttTimes.pop();
        tempRunningq.pop();
    }

    for(int i=0; i<n; i++) {
        tat[i]=ct[i]-at[i];
        wt[i]=tat[i]-bt[i];
    }

    float avgTAT=0, avgWT=0, avgRT=0;
    for(int i=0; i<n; i++) {
        avgTAT+=tat[i];
        avgWT+=wt[i];
        avgRT+=responset[i];
    }

    std::cout<<std::endl<<"Process\tAT\tBT\tCT\tTAT\tWT\tRT"<<std::endl;
    for(int i=0; i<n; i++) {
        std::cout<<i<<"\t"<<at[i]<<"\t"<<bt[i]<<"\t"<<ct[i]<<"\t"<<tat[i]<<"\t"<<wt[i]<<"\t"<<responset[i]<<std::endl;
    }

    std::cout<<std::endl<<"Average TAT: "<<avgTAT/n<<std::endl;
    std::cout<<"Average WT: "<<avgWT/n<<std::endl;
    std::cout<<"Average RT: "<<avgRT/n<<std::endl;
}

int main() {
    int n;

    std::cout<<"Enter number of processes: ";
    std::cin>>n;

    run(n);

    return 0;
}