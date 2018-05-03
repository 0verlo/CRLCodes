/*************************************************************************
	> File Name: main.c
	> Author: 
	> Mail: 
	> Created Time: Fri 27 Apr 2018 02:48:56 PM CST
 ************************************************************************/
#include "cones.h"

void locksInite()
{
    sem_init(&semLocks.coneCheckRequest,0,0);
    sem_init(&semLocks.coneCheckDone,0,0);
    sem_init(&semLocks.managerCheckDone,0,0);
    sem_init(&semLocks.payRequest,0,0);
    sem_init(&semLocks.paidCount,0,0);

    pthread_mutex_init(&mutexLocks.managerRoomLock,NULL);
}

int randomGet(int min,int max)
{
    static bool initMark = 1;
    if(initMark){
        srand(time(NULL));
        initMark = 0;
    }
    return(rand() % (max - min + 1) + min); 
}

void *clerk()
{
    printf("[clerk %d]%d\n",gettid(),++debugCounter);
    bool coneStatus = false; 
    do
    {
        pthread_mutex_lock(&mutexLocks.managerRoomLock);
        printf("[clerk %d]cone have been made.\n",gettid());
        sem_post(&semLocks.coneCheckRequest);
        sem_wait(&(semLocks.managerCheckDone));
        coneStatus = conePassed;
        pthread_mutex_unlock(&mutexLocks.managerRoomLock);
    }while(!coneStatus);
    printf("[clerk %d]cone passed.\n",gettid());
}

void *custom(void *numbCones)
{
    int i;
    printf("[custom %d] wants %d\n",gettid(),*(int*)numbCones);
    for(i = 0;i < *(int*)numbCones;i++)
    {
        pthread_create(&(threadInCones.clerk),NULL,clerk,NULL);
    }
    for(i = 0;i < *(int*)numbCones;i++)
    {
        sem_wait(&semLocks.payRequest);
    }
    printf("A custom have buy %d cones.\n",*(int*)numbCones);
    sem_post(&semLocks.paidCount);
}

void *cashier(void *totalCones)
{
    int conesLeft = *(int*)totalCones;
    int money = 0;
    int i;
    while(0 < conesLeft)
    {
        sem_wait(&semLocks.coneCheckDone);
        sem_post(&semLocks.payRequest);
        printf("Cashier got %d dollar.\n",++money);
        conesLeft--;
    }
    for(i = 0;i < CUSTOM_NUMB;i++)
        sem_wait(&semLocks.paidCount);
}

void *manager(void *totalCones)
{
    int conesLeft = *(int*)totalCones;
    while(0 < conesLeft)
    {
        sem_wait(&semLocks.coneCheckRequest);
        if(randomGet(0,1))
        {
            conePassed = true;
            sem_post(&semLocks.coneCheckDone);
            conesLeft--;
            printf("[manager]cone is ready to go.\n");
        }
        else
        {
            conePassed = false;
            printf("[manager]bad cone....\n");
        }
        sem_post(&(semLocks.managerCheckDone));
    }
}

int main()
{
    int totalCones = 0;

    locksInite();

    int i;
    int numbCones[CUSTOM_NUMB] = {0};
    for(i = 0;CUSTOM_NUMB > i;i++){
        numbCones[i] = randomGet(1,4);
        pthread_create(&(threadInCones.custom),NULL,custom,&numbCones[i]);
        totalCones += numbCones[i];
        printf("numbCones is %d totalCones is %d\n",numbCones[i],totalCones);
    }
    printf("Customers have order %d cones\n",totalCones);
    pthread_create(&(threadInCones.cashier),NULL,cashier,&totalCones);
    pthread_create(&(threadInCones.manager),NULL,manager,&totalCones);

    pthread_join(threadInCones.cashier,NULL);
    printf("hello!\n");
    return 0;
}

