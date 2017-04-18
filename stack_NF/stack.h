/*************************************************************************
	> File Name: stack.h
	> Author: 
	> Mail: 
	> Created Time: Thu 09 Mar 2017 11:24:43 AM CST
 ************************************************************************/

#ifndef _STACK_H
#define _STACK_H

typedef struct _intStack{
	int *elems;
	int logicalLen;
	int allocLength;
}intStack;

void intStackNew(intStack *pIntS);
void intStackDispose(intStack *pIntS);
void intStackPush(intStack *pIntS, int iValue);
int  intStackPop(intStack *pIntS);
#endif

