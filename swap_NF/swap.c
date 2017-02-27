#include <stdio.h>

void swap_int_simple(int *ap,int *bp)
{
	int temp = *ap;
	*ap = *bp;
	*bp = temp;
}

void main()
{
	int x =7;
	int y = 117;
	printf("befor func swap_int_simple x = %d,y = %d",x,y);
	swap_int_simple(&x,&y);
	printf("after func swap_int_simple x = %d,y = %d",x,y);
}
