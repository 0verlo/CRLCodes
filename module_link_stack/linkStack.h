#ifndef __LINKSTACK__
#define __LINKSTACK__

#ifdef __DEBUGMODE
#define DEBUG(format,...) printf(format,##__VA_ARGS__)
#else
#define DEBUG(format, ...)
#endif

#define PROCFAIL (-1)
#define PROCSUCCESS 0

typedef char ELEMTYPE;
typedef int PROCSTATS;

/*****Stack NODE for data saving*****/
typedef struct _LINKSTACK_NODE{
    ELEMTYPE data;
    struct _LINKSTACK_NODE *previous;
}LINKSTACK_NODE;

/************Stack info*************/
typedef struct _LINKSTACK{
    struct _LINKSTACK_NODE *end;
	struct _LINKSTACK_NODE *header;
	int elemNumb;
}LINKSTACK;

//static LINKSTACK *pstLinkStack = NULL;

#if 1
PROCSTATS MODULE_linkStack_Creat(LINKSTACK **pstLinkStack);
PROCSTATS MODULE_linkStack_Delete(LINKSTACK **pstLinkStack);
PROCSTATS MODULE_linkStack_Push(LINKSTACK **pstLinkStack,ELEMTYPE* dataIn);
PROCSTATS MODULE_linkStack_Pop(LINKSTACK **pstLinkStack,ELEMTYPE* dataOut);
#endif

#endif // __LINKSTACK__
