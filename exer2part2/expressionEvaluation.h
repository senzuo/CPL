#include "sequentialStack.h"
#include <stdio.h>
#include <stdlib.h>


char *trim(char *properInfixExpressions);
int report(char *s, Stack* stack);
int infixToPostfix(char *properInfixExpressions, char postfixExpression[]);
int computeValueFromPostfix(char *postfixExpression, double *value);
