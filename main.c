#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

int numQuant, maxNum, minNum;
float averageNum;

void *max(int numList[]){
    int i, currentMaxNum = 0;

    for (i=0; i<numQuant; i++){
        if (numList[i] > currentMaxNum){
            currentMaxNum = numList[i];
        }
    }
    maxNum = currentMaxNum;
}

void *min(int numList[]){
    int i, currentMinNum = numList[0];

    for (i=0; i<numQuant; i++){
        if (numList[i] < currentMinNum){
            currentMinNum = numList[i];
        }
    }
    minNum = currentMinNum;
}

void *average(int numList[]){
    int i, somation = 0;
    float currentAverageNum = 0;

    for (i=0; i<numQuant; i++){
        somation += numList[i];
    }

    currentAverageNum = somation/numQuant;
    averageNum = currentAverageNum;
}

int main(void){
    int numList[numQuant], i = 0;
    pthread_t threadMax, threadMin, threadAverage;

    scanf("%d", &numQuant);
    
    while(i < numQuant){
        scanf("%d", &numList[i]);
        i++;
    }

    pthread_create(&threadMax, NULL, max, &numList);
    pthread_create(&threadMin, NULL, min, &numList);
    pthread_create(&threadAverage, NULL, average, &numList);

    pthread_join(threadMax, NULL);
    pthread_join(threadMin, NULL);
    pthread_join(threadAverage, NULL);

    printf("The average value is %f\nThe minimum value is %d\nThe maximum value is %d\n", averageNum, minNum, maxNum);

    return 0;
}