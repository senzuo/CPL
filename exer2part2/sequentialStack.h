#include <string.h>

#define INIT_SIZE 8

typedef struct Stack{
	int data_size;
	void *data;
	int capacity;
	int top;
}Stack;


Stack *resize(Stack* stack);
int isEmpty(Stack *stack);
int isFull(Stack *stack);
int getSize(Stack *stack);
void push(Stack *stack, void *e);
Stack* createStack(int data_size);
void *pop(Stack *stack);
void *peek(Stack *stack);
void destroy(Stack *stack);
