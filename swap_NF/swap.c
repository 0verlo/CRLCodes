/*************************************************************************
	> File Name: swap.c
	> Author: 
	> Mail: 
	> Created Time: Fri 24 Feb 2017 11:49:48 AM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>

void swap_simple_f1(int *x,int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

void swap_NF(void *vpx,void *vpy,int size)
{
	//XXX:need an input check to make sure vpx and vpy are same type.
	char buffer[size];
	//A standard C programme should use malloc() here.
	//but neet 2 be free(),so an array will be a more simple way.
	memcpy(buffer,vpx,size);
	memcpy(vpx,vpy,size);
	memcpy(vpy,buffer,size);
}

void main()
{
	int x = 123;
	int y = 79;
	printf("befor swap_simple_f1 x = %d,y = %d\n",x,y);
	swap_simple_f1(&x,&y);
	printf("after swap_simple_f1 x = %d,y = %d\n",x,y);

	printf("----------------swap in a Normal form way----------------");

	float fX = 11.2;
	float fY = 3.1415;
	printf("befor swap_nf fX = %f,fY = %f\n",fX,fY);
	swap_NF(&fX,&fY,sizeof(fX));
	printf("after swap_nf fX = %f,fY = %f\n",fX,fY);

	char *husband = strdup("William");
	char *wife = strdup("Lisa");
	printf("befor swap_nf husband %s,and wife %s\n",husband,wife);
	swap_NF(&husband,&wife,sizeof(husband));
	printf("after swap_nf husband %s,and wife %s\n",husband,wife);
}
