/*************************************************************************
	> File Name: stack_NF.c
	> Author: 
	> Mail: 
	> Created Time: Tue 14 Mar 2017 05:01:27 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

#include"stack_NF.h"

static void nfStackGrow(nfStack *pNfS)
{
	pNfS->allocLength *=2;
	pNfS->elems = realloc(pNfS->elems,pNfS->allocLength * pNfS->elemSize);
}

void nfStackNew(nfStack *pNfS,int elemSize,void(*freeNf)(void*))
{
	assert(0 < elemSize);
	pNfS->elemSize = elemSize;
	pNfS->logicalLen = 0;
	pNfS->allocLength = 4;
	pNfS->elems = malloc(4 * elemSize);
	assert(NULL != pNfS->elems);
}

void nfStackDispose(nfStack *pNfS)
{
	if(NULL != pNfS->freeNf){
		for(int i = 0;i < pNfS->logicalLen;i++){
			pNfS->freeNf((char*)pNfS->elems + (i * pNfS->elemSize));
		}
	}
	free(pNfS->elems);
}

void nfStackPush(nfStack *pNfS, void *elemAddr)
{
	if(pNfS->allocLength ==  pNfS->logicalLen){
		nfStackGrow(pNfS);
	}
	void *target = (char*)pNfS->elems + (pNfS->logicalLen * pNfS->elemSize);		
	memcpy(target,elemAddr,pNfS->elemSize);
	pNfS->logicalLen++;
}

void nfStackPop(nfStack *pNfS, void *elemAddr)
{
	pNfS->logicalLen--;
	void *source = (char*)pNfS->elems + (pNfS->logicalLen * pNfS->elemSize);
	memcpy(elemAddr,source,pNfS->elemSize);
}

