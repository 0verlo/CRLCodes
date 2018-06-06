/*************************************************************************
	> File Name: cones.h
	> Author: 
	> Mail: 
	> Created Time: Fri 27 Apr 2018 03:20:06 PM CST
 ************************************************************************/

#ifndef _CONES_H
#define _CONES_H
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <unistd.h>

#define CUSTOM_NUMB (10)

bool conePassed = false;
int debugCounter = 0;
pid_t gettid(void){return syscall(224);}

struct _threadInCones{
    pthread_t custom;
    pthread_t cashier;
    pthread_t manager;
    pthread_t clerk;
}threadInCones;

struct _semLocks{
    sem_t coneCheckRequest;
    sem_t coneCheckDone;
    sem_t coneOnSell;
    sem_t payRequest;
    sem_t payDoneCount;
}semLocks;

struct _mutexLocks{
    pthread_mutex_t managerRoomLock;
}mutexLocks;
#endif
