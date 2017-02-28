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
/*************************************************************************/
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
/*************************************************************************/
int lineSearch_NF_Hook(void *key,void *base,int n,int elemSize,int (*cmpFN)(void *,void *))
{
	for(int i = 0;i < n;i++){
		void *elemAddr = (char*)base + i*elemSize;
		//A little trick makes the memory addr calculation turns to simple math.
		if(0 == cmpFN(key,elemAddr))
			return i;
	}
	return -1;
}
int intCmp(void *elem1,void *elem2)
{
	int *ip1 = elem1;
	int *ip2 = elem2;

	return (*ip1 - *ip2);
}
int stringCmp(void *elem1,void *elem2)
{
	char *sp1 = *(char**)elem1;
	char *sp2 = *(char**)elem2;

	return(strcmp(sp1,sp2));
}

/*************************************************************************
 *test_zoon                                                              *
 *************************************************************************/
void test_Float()
{
	float arrayF[] = {1.22,3.221,5.23,34.9,3.14,9.22};
	float keyF = 3.14;
	int nF = 6;
	int searchResult = -1;

	printf("lineSearch_NF in %s:\n",__func__);
	searchResult = lineSearch_NF(&keyF,arrayF,nF,sizeof(keyF));
	printf("The float keyF %f is at the %dth place of the line.\n",keyF,searchResult);
}

void test_Int()
{
	int array[] = {1,95,23,3,5,78,2};
	int key = 78;
	int n = 7;
	int searchResult = -1;

	printf("lineSearch_simple1 in %s:\n",__func__);
	searchResult = lineSearch_simple1(key,array,n);
	printf("The key numb %d is at the %dth place of the line.\n",key,searchResult);

	printf("llineSearch_NF_Hook in %s:\n",__func__);
	searchResult = lineSearch_NF_Hook(&key,array,n,sizeof(key),intCmp);
	printf("The key numb %d is at the %dth place of the line.\n",key,searchResult);
}

void test_String()
{
	char *array[] = {"EE","AB","D","Eb"."C","Q"};
	char *key = "EE"
	int n = 6;
	int searchResult = -1;

	printf("lineSearch_NF_Hook in %s:\n",__func__);
	searchResult = lineSearch_NF_Hook(&key,array,n,sizeof(key),intCmp);
	printf("The key numb %d is at the %dth place of the line.\n",key,searchResult);
}
/*************************************************************************/
void main()
{
	test_Int();

	test_Float();
}
