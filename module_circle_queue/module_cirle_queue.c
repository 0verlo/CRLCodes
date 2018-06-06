#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


//#include "hi_comm_ive.h"

#include "module_cirle_queue.h"

PROCSTATS MODULE_CIRLE_QUEUE_Uninit(void)
{
	if((NULL != pstCirleQueue->header) &&
		(NULL != pstCirleQueue->header->next) &&
		(NULL != pstCirleQueue))
	{
		CIRLE_QUEUE_NODE* Cleaner;
		CIRLE_QUEUE_NODE* CleanTmp;
		Cleaner = pstCirleQueue->header->next->next;
		

		while((NULL != Cleaner->next) && (pstCirleQueue->header->next != Cleaner->next))
		{
			CleanTmp = Cleaner->next;
			free(Cleaner);
			Cleaner = CleanTmp;
		}
		free(Cleaner);
		Cleaner = CleanTmp = NULL;
		free(pstCirleQueue->header->next);
		free(pstCirleQueue->header);
		free(pstCirleQueue);
		pstCirleQueue = NULL;
		return PROCSUCCESS;
	}
	return PROCFAIL;	
}

PROCSTATS MODULE_CIRLE_QUEUE_Init(void)
{
	CIRLE_QUEUE_NODE* Generater;
	
	if(NULL ==(pstCirleQueue = (CIRLE_QUEUE *)malloc(sizeof(CIRLE_QUEUE))))
	{
		printf("CIRLE_QUEUE init fail\n");
		return PROCFAIL;
	}
	memset(pstCirleQueue, 0, sizeof(CIRLE_QUEUE));
	if(NULL == (pstCirleQueue->header = (CIRLE_QUEUE_NODE *)malloc(sizeof(CIRLE_QUEUE_NODE))))
	{
		printf("CIRLE_QUEUE init fail\n");
		return PROCFAIL;
	}
	if(NULL == (pstCirleQueue->header->next = (CIRLE_QUEUE_NODE *)malloc(sizeof(CIRLE_QUEUE_NODE))))
	{
		printf("CIRLE_QUEUE init fail\n");
		return PROCFAIL;
	}
	pstCirleQueue->front = pstCirleQueue->header->next;
	
	for(pstCirleQueue->ELEMNUMB = 1; pstCirleQueue->ELEMNUMB <= ELEMNUMBMAX; pstCirleQueue->ELEMNUMB++)
	{
		if(NULL == (Generater = (CIRLE_QUEUE_NODE *)malloc(sizeof(CIRLE_QUEUE_NODE))))
		{
			printf("CIRLE_QUEUE init fail\n");
			return PROCFAIL;
		}
		pstCirleQueue->front->next = Generater;
		pstCirleQueue->front = pstCirleQueue->front->next;
	}
	pstCirleQueue->front->next = pstCirleQueue->header->next;

	pstCirleQueue->front = pstCirleQueue->header->next;
	pstCirleQueue->end = pstCirleQueue->header->next;
	pstCirleQueue->ELEMNUMB = 0;
	return PROCSUCCESS;
}

PROCSTATS MODULE_CIRLE_QUEUE_Inqueue(ELEMTYPE * pElemType)
{
	MODULE_CIRLE_QUEUE_VisitorCheckIn(9);	
	if (NULL == pstCirleQueue->end)
	{
		printf("CIRLE_QUEUE havent init\n");
		goto CIRLE_QUEUE_INQUEUE_FAIL;
	}
	if(ELEMNUMBMAX <= pstCirleQueue->ELEMNUMB)
	{
		printf("CIRLE_QUEUE havent init or Queue full, Inqueue fail\n");
		goto CIRLE_QUEUE_INQUEUE_FAIL;
	}
	
	pstCirleQueue->end = pstCirleQueue->end->next;
	/**********data copy**********/
	memcpy(&(pstCirleQueue->end->data), pElemType, sizeof(ELEMTYPE));
	pstCirleQueue->ELEMNUMB++;
	printf("inqueue success \n");
	
	VisiterorCheck = VisiterorCheck - 1;

	return PROCSUCCESS;
	
CIRLE_QUEUE_INQUEUE_FAIL:
	
	VisiterorCheck = VisiterorCheck - 1;
	
	return PROCFAIL;
}


PROCSTATS MODULE_CIRLE_QUEUE_Dequeue(ELEMTYPE * pElemType)
{
    bool DataGetMark;
	DataGetMark = false;
	while(false == DataGetMark)
	{
		MODULE_CIRLE_QUEUE_VisitorCheckIn(7);
		if (NULL == pstCirleQueue->front)
		{
			printf("CIRLE_QUEUE havent init, Dequeue fail\n");
			break;
		}
		if(0 < pstCirleQueue->ELEMNUMB)
		{
			/**********data copy**********/
			memcpy(pElemType, &(pstCirleQueue->front->data), sizeof(ELEMTYPE));
			pstCirleQueue->front = pstCirleQueue->front->next;
			pstCirleQueue->ELEMNUMB--;
			printf("%d data in queue\n",pstCirleQueue->ELEMNUMB);
			DataGetMark = true;
		}	
		VisiterorCheck = VisiterorCheck - 1;
	}
	return PROCFAIL;
}

void MODULE_CIRLE_QUEUE_VisitorCheckIn(int iSleepTime)
{
	VisiterorCheck = VisiterorCheck + 1;
	if(VisiterorCheck > 1)
	{
		printf("BOOOOOM!");
		VisiterorCheck = VisiterorCheck - 1;
		usleep(iSleepTime);
		MODULE_CIRLE_QUEUE_VisitorCheckIn(iSleepTime);
	}
}

#if 0
HI_VOID MODULE_CIRLE_QUEUE(HI_VOID)
{
	ELEMTYPE TESTSUB;	
	MODULE_CIRLE_QUEUE_Init();
	MODULE_CIRLE_QUEUE_Inqueue(&TESTSUB);
	MODULE_CIRLE_QUEUE_Dequeue(&TESTSUB);
	MODULE_CIRLE_QUEUE_Uninit();	
}
#endif
