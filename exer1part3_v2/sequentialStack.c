#include "sequentialStack.h"

/* Interfaces for the 1st stack for char elements*/

int getStackSize(SqStack *s) {
	return s->top + 1;
}

/*  Initialize the sequential stack
 */
void InitStack(SqStack *s){
	s->top = -1;
}

/*  Release the memory of the sequential stack
 */
void DestroyStack(SqStack *s){
	free(s);
	s = NULL;
}

/*  Check if the stack is empty.
    Return 1 to indicate the stack is empty.
    Return 0 to indicate the stack is NOT empty.
 */
int StackEmpty(SqStack *s){
	return getStackSize(s) <= 0;
}

/*  If the stack is NOT full, push e into it and return 1 to indicate a successful push.
    If the stack is full, merely return 0 to indicate an unsuccessful push.
 */
int Push(SqStack *s, ElemType e){
	if(getStackSize(s) == MaxSize) {
		printf("the stack is full!\n");
		return 0;
	}
	s->data[++s->top] = e;
	return 1;
}

/*  If the stack is NOT empty, pop the top of the stack into e and return 1 to indicate a successful pop.
    If the stack is empty, merely return 0 to indicate an unsuccessful pop.
 */
int Pop(SqStack *s, ElemType *e) {
	if (getStackSize(s) <= 0){
		printf("the stack is empty\n");
		return 0;
	}
	*e = s->data[s->top--];
	return 1;
}

/*  If the stack is NOT empty, assign the top of the stack to e and return 1 to indicate a successful gettop.
    If the stack is empty, merely return 0 to indicate an unsuccessful gettop.
 */
int GetTop(SqStack *s, ElemType *e) {
	if (getStackSize(s) <= 0){
		printf("the stack is empty\n");
		return 0;
	}
	*e = s->data[s->top];
	return 1;
}

void display(SqStack *s) {
	for (int i = 0; i < getStackSize(s); ++i) {
		printf("%c\t", s->data[i]);
	}
	printf("\n");
}


/* Interfaces for the 2nd stack for double elements*/

int getStackSize1(SqStack1 *s) {
	return s->top + 1;
}

/*  Initialize the sequential stack
 */
void InitStack1(SqStack1 *s) {
	s->top = -1;
}

/*  Release the memory of the sequential stack
 */
void DestroyStack1(SqStack1 *s) {
	free(s);
	s = NULL;
}

/*  Check if the stack is empty.
 Return 1 to indicate the stack is empty.
 Return 0 to indicate the stack is NOT empty.
 */
int StackEmpty1(SqStack1 *s) {
	return getStackSize1(s) <= 0;
}

/*  If the stack is NOT full, push e into it and return 1 to indicate a successful push.
    If the stack is full, merely return 0 to indicate an unsuccessful push.
 */
int Push1(SqStack1 *s, ElemType1 e) {
	if (getStackSize1(s) >= MaxSize) {
		printf("the stack is full\n");
		return 0;
	}
	s->data[++s->top] = e;
	return 1;
}

/*  If the stack is NOT empty, pop the top of the stack into e and return 1 to indicate a successful pop.
    If the stack is empty, merely return 0 to indicate an unsuccessful pop.
 */
int Pop1(SqStack1 *s,ElemType1 *e) {
	if (StackEmpty1(s)) {
		printf("the stack is empty\n");
		return 0;
	}
	*e = s->data[s->top--];
	return 1;
}

/*  If the stack is NOT empty, assign the top of the stack to e and return 1 to indicate a successful gettop.
    If the stack is empty, merely return 0 to indicate an unsuccessful gettop.
 */
int GetTop1(SqStack1 *s,ElemType1 *e) {
	if (StackEmpty1(s)) {
		printf("the stack is empty\n");
		return 0;
	}
	*e = s->data[s->top];
	return 1;
}


