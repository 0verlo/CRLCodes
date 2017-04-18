/*************************************************************************
	> File Name: stack.h
	> Author: 
	> Mail: 
	> Created Time: Thu 09 Mar 2017 11:24:43 AM CST
 ************************************************************************/

#ifndef _STACK_NF_H
#define _STACK_NF_H

typedef struct _nfStack{
	void *elems;
	int elemSize;
	int logicalLen;
	int allocLength;
	void(*freeNf)(void*);
}nfStack;

//if elem have no need 2 be free().Give a NULL.
void nfStackNew(nfStack *pNfS,int elemSize,void(*freeNf)(void*));
void nfStackDispose(nfStack *pNfS);
void nfStackPush(nfStack *pNfS, void *elemAddr);
void nfStackPop(nfStack *pNfS, void *elemAddr);
#endif

