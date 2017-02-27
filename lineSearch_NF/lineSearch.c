/*************************************************************************
	> File Name: lineSearch.c
	> Author: 
	> Mail: 
	> Created Time: Mon 27 Feb 2017 06:18:43 AM PST
 ************************************************************************/

#include<stdio.h>
#include<string.h>

int lineSearch_simple1(int key,int array[],int n)
{
	for(int i = 0;i < n;i++){
		if(key == array[i]){
			return i;
		}
	}
	return -1;
}

void *lineSearch_NF(void *key,void *base,int n,int elemSize)
{
	for(int i = 0;i < n;i++){
		void *elemAddr = (char*)base + i*elemSize;
		printf("--%d--\n",i);
		//A little trick makes the memory addr calculation turns to simple math.
		if(0 == memcmp(key,elemAddr,elemSize))
			return elemAddr;
	}
	printf("---\n");
	return NULL;
}

void main()
{
	int array[] = {1,95,23,3,5,78,2};
	int key = 78;
	int size = 7;
	int searchResult = -1;

	searchResult = lineSearch_simple1(key,array,size);

	printf("The key numb %d is at the %dth play of the line.\n",key,searchResult);

	printf("-----------------------\n");
	float arrayF[] = {1.22,3.221,5.23,34.9,3.14,9.22};
	float keyF = 3.14;
	int n = 6;
	float *fGet = NULL;
	printf("-----------------------\n");
	fGet = lineSearch_NF(&key,arrayF,n,sizeof(key));
	if(NULL != fGet)
		printf("Got key %f in arrayF. Memory addr is",*fGet);
}
