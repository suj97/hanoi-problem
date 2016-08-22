/* C program for Tower of Hanoi using Recursion */
#include<stdio.h>

void move(int n,int x,char beg,char aux,char end)
{
	if(n==1)
		printf("Move disk %d from %c to %c\n",x,beg,end);
	else
	{
		move(n-1,x-1,beg,end,aux);
		move(1,x,beg,aux,end);
		move(n-1,x-1,aux,beg,end);
	}
}

int main(int argc, char const *argv[])
{
	int num;
	printf("Enter no. of disks\n");
	scanf("%d",&num);
	move(num,num,'A','B','C');
	return 0;
}