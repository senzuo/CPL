#include "expressionEvaluation.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *trim(char *properInfixExpressions) {
    while (*properInfixExpressions != '\0' && isspace(*properInfixExpressions)) {
        properInfixExpressions++;
    }
    return properInfixExpressions;
}

int report(char *s, Stack* stack) {
    if(stack!='\0') free(stack);
    printf("%s\n", s);
    return -1;
}

int infixToPostfix(char *properInfixExpressions, char postfixExpression[]) {
    Stack *stack = createStack(sizeof(char));
    int countOpertor = 0;
    int countNumber = 0;
    int count = 0;
    int index = 0;
    properInfixExpressions = trim(properInfixExpressions);
    if (*properInfixExpressions == '\0') {
        return report("Empty String !\n", stack);
    }
    
    int count_flag = 0; /* 0-> out of a number */
    while(*properInfixExpressions != '\0' ){
        char c = *properInfixExpressions;
        if (isdigit(c)){
            if (count % 2 != 0){
                if (isdigit(*(properInfixExpressions-2)))  return report("space", stack);
                return report("insufficient operands!\n", stack);
            }
            if (count_flag==0){
                countNumber++;
                count_flag = 1;
            }
            postfixExpression[index++] = c;
            if (*(properInfixExpressions+1) != '\0' && !isdigit(*(properInfixExpressions + 1)))  {
                postfixExpression[index++] = ' ';
                count_flag = 0;
                count++;
            }
        }else if(c =='('){
            push(stack, &c);
        }else if(c == '/' || c == '*'){
            count++;
            countOpertor++;
            if(!isEmpty(stack)){
                char tmp = *(char *)peek(stack);
                while(tmp=='/'||tmp=='*') {
                    tmp = *(char *)pop(stack);
                    postfixExpression[index++] = tmp;
                    if (isEmpty(stack))    break;
                    tmp = *(char *)peek(stack);
                }
            }
            push(stack, &c);
        }else if(c == '+' || c == '-'){
            count++;
            countOpertor++;
            if(isEmpty(stack)) {
                push(stack, &c);
                properInfixExpressions++;
                continue;
            }
            char tmp = *(char *)peek(stack);
            while(tmp=='*' || tmp=='/') {
                tmp = *(char *)pop(stack);
                postfixExpression[index++] = tmp;
                if (isEmpty(stack))    break;
                tmp = *(char *)peek(stack);
            }
            while(tmp=='+' || tmp=='-') {
                tmp = *(char *)pop(stack);
                postfixExpression[index++] = tmp;
                if (isEmpty(stack))    break;
                tmp = *(char *)peek(stack);
            }
            push(stack, &c);
        }else if(c == ')') {
            if(isEmpty(stack)) {
                return report("improper braces !\n", stack);
            }
            char tmp = *(char *)pop(stack);
            while (tmp != '(') {
                postfixExpression[index++] = tmp;
                if(isEmpty(stack)){
                    return report("improper braces !\n", stack);
                }
                tmp = *(char *)pop(stack);
            }
        }else if(c != ' '){
            return report("illegal character!\n", stack);
        }
        properInfixExpressions++;
    }
    if(isEmpty(stack) && countOpertor+1!=countNumber){
        return report("space!\n", stack);
    }
    while(!isEmpty(stack)){
        char ch = *(char *)peek(stack);
        if (ch == '(')  return report("improper braces !\n", stack);
        postfixExpression[index++] = *(char *)pop(stack);
    }
    if(countOpertor+1!=countNumber){
        return report("insufficient operands!\n", stack);
    }
    destroy(stack);
    postfixExpression[index] = '\0';
    return 1;
}

int computeValueFromPostfix(char *postfixExpression, double *value) {
    *value = -1;
    Stack* stack = createStack(sizeof(double));
    while(*postfixExpression != '\0') {
        char ch = *postfixExpression;
        if(isdigit(ch)) {
            double i = ch - '0';
            while(isdigit(*(postfixExpression+1))){
                postfixExpression++;
                i = i * 10 + (*postfixExpression) - '0';
            }
            push(stack, &i);
        } else {
            if (ch == '+'){
                *value = *(double *)pop(stack) + *(double *)pop(stack);
                push(stack,value);
            } else if (ch == '-') {
                double t = *(double *)pop(stack);
                *value = *(double *)pop(stack) - t;
                push(stack,value);
            } else if (ch == '/') {
                double t = *(double *)pop(stack);
                *value = 1.0 * *(double *)pop(stack) / t;
                push(stack,value);
            } else if (ch == '*') {
                *value = 1.0 * *(double *)pop(stack) * *(double *)pop(stack);
                push(stack,value);
            }
        }
        postfixExpression++;
    }
    if(!isEmpty(stack)){
        *value = *(double *)pop(stack);
        if (!isEmpty(stack)) {
            printf("insufficient operands!\n");
            return -1;
        }
    }
    destroy(stack);
    return 1;
}


