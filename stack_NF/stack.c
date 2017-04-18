/*************************************************************************
	> File Name: stack.c
	> Author: 
	> Mail: 
	> Created Time: Thu 09 Mar 2017 12:06:15 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#include"stack.h"

void intStackNew(intStack *pIntS)
{
	pIntS->logicalLen = 0;
	pIntS->allocLength = 4;
	pIntS->elems = malloc(4 * sizeof(int));
	assert(NULL != pIntS->elems);
}

void intStackDispose(intStack *pIntS)
{
	free(pIntS->elems);
}

void intStackPush(intStack *pIntS, int iValue)
{
	if(pIntS->allocLength ==  pIntS->logicalLen){
		pIntS->allocLength *= 2;
		pIntS->elems = realloc(pIntS->elems,pIntS->allocLength*sizeof(int));
		assert(NULL != pIntS->elems);
	}
	pIntS->elems[pIntS->logicalLen] = iValue;
	pIntS->logicalLen++;
}

int  intStackPop(intStack *pIntS)
{
	assert(0 < pIntS->logicalLen);
	pIntS->logicalLen--;
	return pIntS->elems[pIntS->logicalLen];
}
