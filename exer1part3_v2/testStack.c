#include "sequentialStack.h"

void main() {
	SqStack1* s = (SqStack1 *)malloc(sizeof(SqStack1));
	InitStack1(s);
	// for (int i = 0; i < 10; ++i)
	{
		Push1(s, 1.23);
	}
	double c;
	if (Pop1(s, &c))
		printf("%lf\n", c);
	
	// display(s);
	DestroyStack1(s);


}