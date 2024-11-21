#include <bits/stdc++.h>
#include <iostream>
#include <cstring>
#include <pthread.h>

#define MAX 4
#define MAX_THREAD 4

int matA[MAX][MAX], matB[MAX][MAX], matC[MAX][MAX];
int step_i=0;
pthread_mutex_t mutex;

void* multi(void* arg) {
    while(true) {
        int i;
        pthread_mutex_lock(&mutex);
        i=step_i++;
        pthread_mutex_unlock(&mutex);

        if(i>=MAX) break;

        for(int j=0; j<MAX; j++) {
            matC[i][j]=0;
            for(int k=0; k<MAX; k++) {
                matC[i][j]+=matA[i][k]*matB[k][j];
            }
        }
    }

    return nullptr;
}

int main() {
    std::cout<<"Enter elements of first matrix: "<<std::endl;
    for(int i=0; i<MAX; i++) {
        for(int j=0; j<MAX; j++) {
            std::cin>>matA[i][j];
        }
    }

    std::cout<<"Enter elements of second matrix: "<<std::endl;
    for(int i=0; i<MAX; i++) {
        for(int j=0; j<MAX; j++) {
            std::cin>>matB[i][j];
        }
    }

    memset(matC, 0, sizeof(matC));

    pthread_mutex_init(&mutex, nullptr);

    pthread_t threads[MAX_THREAD];

    for(int i=0; i<MAX_THREAD; i++) {
        int* p;
        pthread_create(&threads[i], nullptr, multi, nullptr);
    }

    for(int i=0; i<MAX_THREAD; i++) {
        pthread_join(threads[i], nullptr);
    }

    pthread_mutex_destroy(&mutex);

    std::cout<<"Product of the matrices: "<<std::endl;
    for(int i=0; i<MAX; i++) {
        for(int j=0; j<MAX; j++) {
            std::cout<<matC[i][j]<<" ";
        }
        std::cout<<std::endl;
    }

    return 0;
}