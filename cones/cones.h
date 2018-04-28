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

bool conePassed = false;

struct _threadInCones{
    pthread_t custom;
    pthread_t cashier;
    pthread_t manager;
    pthread_t clerk;
}threadInCones;

struct _semLocks{
    sem_t coneCheckRequest;
    sem_t coneCheckDone;
    sem_t managerRoomLock;
    sem_t payRequest;
}semLocks;
#endif
