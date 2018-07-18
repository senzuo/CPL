#include <string.h>

typedef struct Stack{
	size_t data_size;
	void *data;
	int capacity;
	int top;
}Stack;

#define INIT_SIZE 8

Stack *resize(Stack* stack);
int isEmpty(Stack *stack);
int isFull(Stack *stack);
int getSize(Stack *stack);
void push(Stack *stack, void *e);
Stack* createStack(size_t data_size);
void *pop(Stack *stack);
void *peek(Stack *stack);
void destroy(Stack *stack);
