#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstdint>

std::vector<int> resolveConflict(std::vector<int> at, std::vector<int> bt, int minAT) {
    std::vector<int> leastAT, indices;
    for(int i=0; i<at.size(); i++) {
        if(at[i]==minAT) {
            leastAT.push_back(i);
        }
    }

    if(leastAT.size()==1) {
        return leastAT;
    }
    else {
        std::vector<int>::iterator minBT;
        std::vector<int> leastBT, sortedAT;
        for(int i=0; i<leastAT.size(); i++) {
            leastBT.push_back(bt[leastAT[i]]);
        }
        while(!leastBT.empty()) {
            minBT=std::min_element(leastBT.begin(), leastBT.end());
            sortedAT.push_back(leastAT[std::distance(leastBT.begin(), minBT)]);
            leastBT.erase(minBT);
        }

        return sortedAT;
    }
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

void printVector(std::vector<int> v) {
    for(int i=0; i<v.size(); i++) {
        std::cout<<v[i]<<"\t";
    }
    std::cout<<std::endl;
}

void run(int n, int tq) {
    std::queue<int> readyq, runningq, ganttTimes;
    std::vector<int> at(n), bt(n), ct(n), tat(n), wt(n), rt(n), responset(n);
    int contextSwitches=0;

    for(int i=0; i<n; i++) {
        responset[i]=INT16_MAX;
    }

    std::cout<<"Enter arrival time and burst time for each process:"<<std::endl;
    for(int i=0; i<n; i++) {
        std::cin>>at[i]>>bt[i];
    }

    for(int i=0; i<n; i++) {
        if(at[i]<0 || bt[i]<=0) {
            std::cout<<"Invalid input!"<<std::endl;
            return;
        }
    }

    rt=bt;

    int prevTime=0, time=0, index=0, done=*std::min_element(at.begin(), at.end());
    std::vector<int> sortedAT=resolveConflict(at, rt, done);
    printVector(sortedAT);
    for(int i=0; i<sortedAT.size(); i++) {
        readyq.push(sortedAT[i]);
    }

    if(done!=0) {
        prevTime=time;
        time+=done;
        ganttTimes.push(time);
        runningq.push(-1);
    }

    while(!readyq.empty()) {
        index=readyq.front();
        readyq.pop();

        if(rt[index]<tq) {
            prevTime=time;
            time+=rt[index];
            rt[index]=0;
            runningq.push(index);
            ganttTimes.push(time);
        }
        else {
            prevTime=time;
            rt[index]-=tq;
            time+=tq;
            runningq.push(index);
            ganttTimes.push(time);
        }

        for(int i=prevTime+1; i<=time; i++) {
            for(int j=0; j<n; j++) {
                if(at[j]==i) {
                    sortedAT=resolveConflict(at, rt, i);
                    printVector(sortedAT);
                    done=i;
                    for(int k=0; k<sortedAT.size(); k++) {
                        readyq.push(sortedAT[k]);
                    }
                }
            }
        }

        if(rt[index]!=0) {
            readyq.push(index);
        }
    }

    printGantt(runningq, ganttTimes);
    std::queue<int> tempGanttTimes=ganttTimes, tempRunningq=runningq;

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

    std::cout<<std::endl<<"Process\tAT\tBT\tCT\tTAT\tWT\tRT"<<std::endl;
    for(int i=0; i<n; i++) {
        std::cout<<i<<"\t"<<at[i]<<"\t"<<bt[i]<<"\t"<<ct[i]<<"\t"<<tat[i]<<"\t"<<wt[i]<<"\t"<<responset[i]<<std::endl;
    }

    float avgTAT=0, avgWT=0, avgRT=0;
    for(int i=0; i<n; i++) {
        avgTAT+=tat[i];
        avgWT+=wt[i];
        avgRT+=responset[i];
    }
    
    std::cout<<std::endl<<"Average TAT: "<<avgTAT/n<<std::endl;
    std::cout<<"Average WT: "<<avgWT/n<<std::endl;
    std::cout<<"Average RT: "<<avgRT/n<<std::endl;
}

int main() {
    int n, tq;

    std::cout<<"Enter the number of processes: ";
    std::cin>>n;

    std::cout<<std::endl<<"Enter time quantum: ";
    std::cin>>tq;

    if(n<=0 || tq<=0) {
        std::cout<<"Invalid input!"<<std::endl;
        return 0;
    }

    run(n, tq);

    return 0;
}