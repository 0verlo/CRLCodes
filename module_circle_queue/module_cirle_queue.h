/*************************************************************************       
     > File Name: module_cirle_queue.h
     > Version: V1.0
     > Author: CRL
     > Created Time: Fri 25 Mar 2016 01:50:27 AM PDT
************************************************************************/
/*************************************************************************   
	A CIRLE QUEUE module 的实现
	
	缺少ELEMTYPE与传入指针type的确认模块
************************************************************************/

#ifndef __MODULE_CIRLE_QUEUE__
#define __MODULE_CIRLE_QUEUE__

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

//#include "hi_comm_ive.h"

#define PROCFAIL (-1)
#define PROCSUCCESS 0

#define ELEMNUMBMAX 30

typedef int ELEMTYPE;

typedef int PROCSTATS;

typedef struct _CIRLE_QUEUE_NODE{  
    ELEMTYPE data;
    struct _CIRLE_QUEUE_NODE *next;  
}CIRLE_QUEUE_NODE;
  
typedef struct _CIRLE_QUEUE{
    struct _CIRLE_QUEUE_NODE *front;
    struct _CIRLE_QUEUE_NODE *end;
	struct _CIRLE_QUEUE_NODE *header;
	int ELEMNUMB;
}CIRLE_QUEUE;  

static CIRLE_QUEUE *pstCirleQueue = NULL;
static volatile int VisiterorCheck = 0;

void MODULE_CIRLE_QUEUE_VisitorCheckIn(int iSleepTime);

PROCSTATS MODULE_CIRLE_QUEUE_Uninit(void);

PROCSTATS MODULE_CIRLE_QUEUE_Init(void);

PROCSTATS MODULE_CIRLE_QUEUE_Inqueue(ELEMTYPE * pElemType);

PROCSTATS MODULE_CIRLE_QUEUE_Dequeue(ELEMTYPE * pElemType);

#endif



