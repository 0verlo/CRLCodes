/*************************************************************************
	> File Name: main.c
	> Author: 
	> Mail: 
	> Created Time: Fri 27 Apr 2018 02:48:56 PM CST
 ************************************************************************/
#include "cones.h"

void locksInite()
{
    int ret[4] = {0};
    ret[0] = sem_init(&semLocks.coneCheckRequest,0,0);
    ret[1] = sem_init(&semLocks.coneCheckDone,0,0);
    ret[2] = sem_init(&semLocks.managerRoomLock,0,1);
    ret[3] = sem_init(&semLocks.payRequest,0,0);
    printf("Printf %d,%d,%d,%d\n",ret[0],ret[1],ret[2],ret[3]);
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
    do
    {
        sem_wait(&(semLocks.managerRoomLock));
        conePassed = false;
        sem_post(&semLocks.coneCheckRequest);
        printf("A cone have been made.\n");
    }while(!conePassed);
}

void *custom(void *numbCones)
{
    int i;
    for(i = 0;i < *(int*)numbCones;i++)
    {
        pthread_create(&(threadInCones.clerk),NULL,clerk,NULL);
    }
    for(i = 0;i < *(int*)numbCones;i++)
    {
        sem_wait(&semLocks.payRequest);
    }
    printf("A custom have buy %d cones.\n",*(int*)numbCones);
}

void *cashier(void *totalCones)
{
    int conesLeft = *(int*)totalCones;
    int money = 0;
    while(0 < conesLeft)
    {
        sem_wait(&semLocks.coneCheckDone);
        sem_post(&semLocks.payRequest);
        printf("Cashier got %d dollar.\n",++money);
        conesLeft--;
    }
}

void * manager(void *totalCones)
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
            printf("A cone is ready 2 go.\n");
        }
        sem_post(&(semLocks.managerRoomLock));
    }
}

int main()
{
    int totalCones = 0;

    locksInite();

    int i;
    for(i = 0;3 > i;i++){
        int numbCones = randomGet(1,2);
        pthread_create(&(threadInCones.custom),NULL,custom,&numbCones);
        totalCones += numbCones;
    }
    printf("Customers have order %d cones\n",totalCones);
    pthread_create(&(threadInCones.cashier),NULL,cashier,&totalCones);
    pthread_create(&(threadInCones.manager),NULL,manager,&totalCones);

    pthread_join(threadInCones.custom,NULL);
    printf("hello!\n");
    return 0;
}

