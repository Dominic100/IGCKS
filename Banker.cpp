#include <iostream>
#include <string>
#include <vector>

void displayMatrix(const std::vector<std::vector<int>> matrix, const std::string name) {
    std::cout<<name<<" Matrix:"<<std::endl;
    for(int i=0; i<matrix.size(); i++) {
        for(int j=0; j<matrix[i].size(); j++) {
            std::cout<<matrix[i][j]<<"\t";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}

bool satisfyRequirements(const std::vector<int> processNeed, const std::vector<int> working) {
    for(int i=0; i<working.size(); i++) {
        if(processNeed[i]>working[i]) {
            return false;
        }
    }

    return true;
}

bool checkFinish(const std::vector<bool> finish) {
    for(int i=0; i<finish.size(); i++) {
        if(finish[i]==false) {
            return false;
        }
    }

    return true;
}

void isSafeState(const std::vector<int> available, const std::vector<std::vector<int>> max, const std::vector<std::vector<int>> allocated) {
    int numProcesses=max.size();
    int numResources=available.size();

    std::vector<std::vector<int>> need(numProcesses, std::vector<int>(numResources));
    for(int i=0; i<numProcesses; i++) {
        for(int j=0; j<numResources; j++) {
            need[i][j]=max[i][j]-allocated[i][j];
        }
    }

    displayMatrix(need, "Need");

    std::vector<int> safeSequence;
    std::vector<int> work=available;
    std::vector<bool> finish(numProcesses, false);

    int count=0, i=0;
    
    while(count<=numProcesses) {
        if(!finish[i] && satisfyRequirements(need[i], work)) {
            for(int j=0; j<numResources; j++) {
                work[j]+=allocated[i][j];
            }

            finish[i]=true;
            safeSequence.push_back(i);
            count=0;
            i=(i+1)%numProcesses;
            continue;
        }

        count++;
        i=(i+1)%numProcesses;  
    }

    if(checkFinish(finish)) {
        std::cout<<"Safe state!"<<std::endl;
        std::cout<<"Safe sequence: ";
        for(int i=0; i<safeSequence.size(); i++) {
            std::cout<<safeSequence[i]<<" ";
        }
    }
    else {
        std::cout<<"Unsafe state!"<<std::endl;
    }
}

int main() {
    int numProcesses, numResources;

    std::cout<<"Enter number of processes: ";
    std::cin>>numProcesses;
    std::cout<<"Enter number of resources: ";
    std::cin>>numResources;

    std::vector<int> available(numResources);
    std::vector<std::vector<int>> max(numProcesses, std::vector<int>(numResources)), allocated(numProcesses, std::vector<int>(numResources));

    std::cout<<"Enter available resources: ";
    for(int i=0; i<numResources; i++) {
        std::cin>>available[i];
    }

    for(int i=0; i<numProcesses; i++) {
        std::cout<<"Enter maximum resources for process "<<i+1<<": ";
        for(int j=0; j<numResources; j++) {
            std::cin>>max[i][j];
        }
    }

    for(int i=0; i<numProcesses; i++) {
        std::cout<<"Enter allocated resources for process "<<i+1<<": ";
        for(int j=0; j<numResources; j++) {
            std::cin>>allocated[i][j];
        }
    }

    displayMatrix(max, "Max");
    displayMatrix(allocated, "Allocated");

    isSafeState(available, max, allocated);

    return 0;
}