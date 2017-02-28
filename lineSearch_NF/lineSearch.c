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

//void *lineSearch_NF(void *key,void *base,int n,int elemSize)
int lineSearch_NF(void *key,void *base,int n,int elemSize)
{
	for(int i = 0;i < n;i++){
		void *elemAddr = (char*)base + i*elemSize;
		//A little trick makes the memory addr calculation turns to simple math.
		if(0 == memcmp(key,elemAddr,elemSize))
			return i;
	}
	return -1;
}

void main()
{
	int array[] = {1,95,23,3,5,78,2};
	int key = 78;
	int n = 7;
	int searchResult = -1;

	searchResult = lineSearch_simple1(key,array,n);

	printf("The key numb %d is at the %dth place of the line.\n",key,searchResult);

	float arrayF[] = {1.22,3.221,5.23,34.9,3.14,9.22};
	float keyF = 3.14;
	int nF = 6;
	searchResult = lineSearch_NF(&keyF,arrayF,nF,sizeof(keyF));
	printf("The float keyF %f is at the %dth place of the line.\n",keyF,searchResult);

	double arrayLF[] = {1.22,3.221,5.23,34.9,3.14,9.22};
	double keyLF = 3.14;
	int nLF = 6;
	searchResult = lineSearch_NF(&keyLF,arrayLF,nLF,sizeof(keyLF));
	printf("The double keyLF %lf is at the %dth place of the line.\n",keyLF,searchResult);
}
