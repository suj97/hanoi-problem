#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<limits.h>

struct Stack
{
   unsigned size;
   int top;
   int *array;
};
 
// function to create a stack of given size.
struct Stack* create_stack(int size)
{
	struct Stack* stack =
		(struct Stack*) malloc(sizeof(struct Stack));
	stack -> size = size;
	stack -> top = -1;
	stack -> array =
		(int*) malloc(stack -> size * sizeof(int));
	return stack;
}

// Stack is full when top is equal to the last index
int is_full(struct Stack* stack)
{
	return (stack->top == stack->size - 1);
}

// Stack is empty when top is equal to -1
int is_empty(struct Stack* stack)
{
	return (stack->top == -1);
}

// Function to add an item to stack increasing top by 1
void push(struct Stack *stack, int item)
{
	if (is_full(stack))
		return;
	stack -> array[++stack -> top] = item;
}

// Function to remove an item from stack.  It decreases top by 1
int pop(struct Stack* stack)
{
	if (is_empty(stack))
		return -100;
	return stack -> array[stack -> top--];
}

//Function to print the movement of disks
void move_print(char from, char to, int d)
{
	printf("Move the disk %d from %c to %c\n",d, from, to);
}

// Function to implement the movement between two poles
void move_between_poles(struct Stack *src,struct Stack *dest, char s, char d)
{
	int pole1_top = pop(src);
	int pole2_top = pop(dest);

// When pole 1 is empty
	if (pole1_top == -100)
	{
		push(src, pole2_top);
		move_print(d, s, pole2_top);
	}

// When pole2 pole is empty
	else if (pole2_top == -100)
	{
		push(dest, pole1_top);
		move_print(s, d, pole1_top);
	}

// When top disk of pole1 > top disk of pole2
	else if (pole1_top > pole2_top)
	{
		push(src, pole1_top);
		push(src, pole2_top);
		move_print(d, s, pole2_top);
	}

// When top disk of pole1 < top disk of pole2
	else
	{
		push(dest, pole2_top);
		push(dest, pole1_top);
		move_print(s, d, pole1_top);
	}
}

void hanoi_iterative(int n,struct Stack *src,struct Stack *aux,struct Stack *dest)
{
	char s='A',a='B',d='C';
	long i;
	//If no of disks is even interchange destination
	//and auxiliary
	if(n%2==0)
	{
		char temp=d;
		d=a;
		a=temp;
	}

	long long moves=pow(2,n)-1;
//bigger disks are pushed first
	for (i = n; i >= 1; i--)
		push(src, i);

	for (i = 1; i <= moves; i++)
	{
		if (i % 3 == 1)
			move_between_poles(src, dest, s, d);
 
		else if (i % 3 == 2)
			move_between_poles(src, aux, s, a);

		else if (i % 3 == 0)
			move_between_poles(aux, dest, a, d);
    }
}

int main(int argc, char const *argv[])
{
	int num;
	printf("Enter number of disks: ");
	scanf("%d",&num);

	struct Stack *src_st, *dest_st, *aux_st;
	src_st = create_stack(num);
	aux_st = create_stack(num);
	dest_st = create_stack(num);

	hanoi_iterative(num,src_st,aux_st,dest_st);

	return 0;
}