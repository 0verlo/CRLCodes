#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkStack.h"
//printf("[ERROR in FILE:%s, LINE:%d]:\n	LINKSTACK struck init fail\n\n",__FILE__,__LINE__);
PROCSTATS MODULE_linkStack_Creat(LINKSTACK **ppstLinkStack)
{
	(*ppstLinkStack) = NULL;

	/****stLinkStack creat****/
    if(NULL ==((*ppstLinkStack) = (LINKSTACK*)malloc(sizeof(LINKSTACK))))
	{
		printf("[ERROR in FILE:%s, LINE:%d]:\n	LINKSTACK struck init fail\n\n",__FILE__,__LINE__);
		return PROCFAIL;
	}
    memset((*ppstLinkStack), 0, sizeof(LINKSTACK));

	
	/****stLinkStackNode header creat****/
    if(NULL == ((*ppstLinkStack)->header = (LINKSTACK_NODE*)malloc(sizeof(LINKSTACK_NODE))))
	{
		printf("[ERROR in FILE:%s, LINE:%d]:\n	LINKSTACK header init fail\n\n",__FILE__,__LINE__);
		return PROCFAIL;
	}
	(*ppstLinkStack)->header->previous = NULL;
    (*ppstLinkStack)->header->data = 0;
	
	/****stLinkStackNode end (first data block) creat****/
    #if 1
    if(NULL == ((*ppstLinkStack)->end= (LINKSTACK_NODE*)malloc(sizeof(LINKSTACK_NODE))))
	{
		printf("[ERROR in FILE:%s, LINE:%d]:\n	LINKSTACK front init fail\n\n",__FILE__,__LINE__);
		return PROCFAIL;
	}
	(*ppstLinkStack)->end->previous = (*ppstLinkStack)->header;
	(*ppstLinkStack)->end->data = 0;
	#endif
	
	return PROCSUCCESS;
}

PROCSTATS MODULE_linkStack_Delete(LINKSTACK **ppstLinkStack)
{
	/****Clear out all data stacks****/
	while(((*ppstLinkStack)->end) != ((*ppstLinkStack)->header))
	{
		LINKSTACK_NODE* nodeKiller;
		nodeKiller = (*ppstLinkStack)->end;
		(*ppstLinkStack)->end = (*ppstLinkStack)->end->previous;
		(*ppstLinkStack)->elemNumb--;
		free(nodeKiller);
	}
	
	/****Clear out header stack****/
	free(((*ppstLinkStack)->header));
	
	/****Clear out stLinkStack stack****/
	free((*ppstLinkStack));
	//printf("ppst after free ?? = %d\n",(*ppstLinkStack));
	(*ppstLinkStack) = NULL;

	return PROCSUCCESS;
}
PROCSTATS MODULE_linkStack_Push(LINKSTACK **ppstLinkStack,ELEMTYPE* dataIn)
{

	#if 1
	LINKSTACK_NODE* tmpPrevious;

	tmpPrevious = (*ppstLinkStack)->end;

	if(NULL == ((*ppstLinkStack)->end = (LINKSTACK_NODE*)malloc(sizeof(LINKSTACK_NODE))))
	{
		printf("[ERROR in FILE:%s, LINE:%d]:\n	LINKSTACK NODE generate fail\n\n",__FILE__,__LINE__);
		return PROCFAIL;
	}

	(*ppstLinkStack)->end->previous = tmpPrevious;
	(*ppstLinkStack)->end->data = *dataIn;
	#endif

	#if 0
    LINKSTACK_NODE* nodeGenerater;

	if(NULL == (nodeGenerater = (LINKSTACK_NODE*)malloc(sizeof(LINKSTACK_NODE))))
	{
		printf("[ERROR in FILE:%s, LINE:%d]:\n	LINKSTACK header init fail\n",__FILE__,__LINE__);
		return PROCFAIL;
	}

	nodeGenerater->data = *dataIn;
	nodeGenerater->previous = (*ppstLinkStack)->end;
	(*ppstLinkStack)->end = nodeGenerater;
	nodeGenerater = NULL;
	#endif

	(*ppstLinkStack)->elemNumb++;

	return PROCSUCCESS;

}

PROCSTATS MODULE_linkStack_Pop(LINKSTACK **ppstLinkStack,ELEMTYPE* dataOut)
{
	LINKSTACK_NODE* nodeKiller;

	if((*ppstLinkStack)->header!= (*ppstLinkStack)->end && (*ppstLinkStack)->elemNumb > 0)
	{
		*dataOut = (*ppstLinkStack)->end->data;

		nodeKiller = (*ppstLinkStack)->end;
		(*ppstLinkStack)->end = (*ppstLinkStack)->end->previous;
		free(nodeKiller);
		nodeKiller = NULL;

		(*ppstLinkStack)->elemNumb--;
		return PROCSUCCESS;
	}
	else
	{
		printf("ERROR:linkStack was Empty.Unable to pop.");
	}

	return PROCFAIL;
}
