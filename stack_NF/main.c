/*************************************************************************
	> File Name: main.c
	> Author: 
	> Mail: 
	> Created Time: Tue 14 Mar 2017 04:31:36 PM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include"stack.h"
#include"stack_NF.h"

void main()
{
	int result;
	intStack iStack;
	intStackNew(&iStack);
	for(int i = 0;i < 7;i++){
		intStackPush(&iStack,i);
	}
	for(int i = 0;i < 7;i++){
		result = intStackPop(&iStack);
		printf("the %dth num is %d\n",i,result);
	}

	printf("------------------NF_result_below------------------\n");
	int nResult;
	nfStack nStack;
	nfStackNew(&nStack,sizeof(int),NULL);
	for(int i = 0;i < 7;i++){
		nfStackPush(&nStack,&i);
	}
	for(int i = 0;i < 7;i++){
		nfStackPop(&nStack,&nResult);
		printf("the %dth num is %d\n",i,nResult);
	}
	nfStackDispose(&nStack);

	printf("------------------str_srote_test------------------\n");
	const char *friends[] = {"Ami","Lily","Carly"};
	nfStack nameStack;

	void stringFree(void *elem){
		free(*(char**)elem);
	}

	nfStackNew(&nameStack,sizeof(char*),stringFree);
	
	for(int i = 0;i < 3;i++){
		char *copy = strdup(friends[i]);
		printf("%s\n",copy);
		nfStackPush(&nameStack,&copy);
	}

	char *nameGet;
	for(int i = 0;i < 3;i++){
		nfStackPop(&nameStack,&nameGet);
		printf("%dth friend:%s\n",i,nameGet);
	}
	nfStackDispose(&nameStack);
}
