/**
 * expressionEvaluation.c 
 * @Author   shenzhuo
 * @DateTime 2018-07-31T15:57:46+0800
 */

#include "expressionEvaluation.h"
#include <ctype.h>		//	isdigit() isspace()
#include <string.h>		//	strlen()

#define INIT 	 0
#define OPERATOR 1
#define OPERAND  2

/**
 * get a complete number from infixExpression and put into postfixExpression
 * @Author   shenzhuo
 * @DateTime 2018-07-31T15:57:46+0800
 * @param    s                        the stack of operators
 * @param    infixExpression          infixExpression
 * @param    postfixExpression        postfixExpression
 * @param    post_index               current index of postfixExpression
 * @return                            the point of infixExpression after getting a number
 */
char *getNumber(SqStack *s, char *infixExpression, char postfixExpression[], int *post_index);





/**
 * find the left brace which is matched with current right brace and pop the value
 * @Author   shenzhuo
 * @DateTime 2018-07-31T16:03:15+0800
 * @param    s                        the stack of operators	
 * @param    infixExpression          infixExpression
 * @param    postfixExpression        postfixExpression
 * @param    post_index               postfixExpression
 * @return                            the point of infixExpression after getting a number
 */
char *getLeftBrace(SqStack *s, char *infixExpression, char postfixExpression[], int *post_index);






/**
 * pop the prioritized operators	
 * @Author   shenzhuo
 * @DateTime 2018-07-31T16:08:28+0800
 * @param    postfixExpression        [description]
 * @param    post_index               [description]
 * @param    s                        [description]
 * @param    c                        current operator
 */
void PopPriority(char postfixExpression[], int *post_index, SqStack *s, char c);




/**
 * check if ch is an operator
 * @Author   shenzhuo
 * @DateTime 2018-07-31T16:10:21+0800
 * @param    ch                       [description]
 * @return                            [description]
 */
int isOperator(char ch);





/**
 * get the next char that is not a space character
 * @Author   shenzhuo
 * @DateTime 2018-07-31T16:11:16+0800
 * @param    infixExpression          [description]
 * @param    infixExpressionHead      [description]
 * @return                            [description]
 */
char getPrevChar(char *infixExpression, char *infixExpressionHead);





/**
 * infixExpression to PostfixExpression
 * @Author   shenzhuo
 * @DateTime 2018-07-31T16:12:57+0800
 * @param    infixExpression          [description]
 * @param    postfixExpression        [description]
 * @return                            [description]
 */
int infixToPostfix(char *infixExpression,char postfixExpression[]) {
	char *infixExpressionHead = infixExpression;	//save the point
	int status = INIT;
	int post_index = 0;
	SqStack *s = (SqStack *)malloc(sizeof(SqStack));
	if (s == NULL){
		printf("Memory allocation failed.\n");
		return -1;
	}
	InitStack(s);
	while (*infixExpression != '\0') {
		char ch = *infixExpression;
		if isdigit(ch) {
			if (status == OPERAND)	{
				printf("Two consecutive numbers.\n");
				return -1;
			}
			status = OPERAND;
			infixExpression = getNumber(s, infixExpression, postfixExpression, &post_index);
		} else {
			char c, n;
			switch (ch) {
				case ' ':	break;
				case '(' :	Push(s, ch);	break;
				case '+' :	
				case '-' :	if (status == OPERATOR && isOperator(*(infixExpression-1)) ){
								printf("Opreator '%c' immediately follows another operator in the expression.\n", ch);
								return -1;
							}
							c = getPrevChar(infixExpression, infixExpressionHead);
							// c == '(' means first char from left brace
							// c == '!' or '\0'	means the first char in the line
							n = *(infixExpression+1);
							if (c == '(' || c == '!'|| c == '\0'){
								if (isdigit( *(infixExpression+1)) || '(' == *(infixExpression+1) ) {
									if (ch == '-')	Push(s, '$');	//	'$' -> '-'
									else	Push(s, '@');			//	'@' -> '+'
									break;
								}else if(n == ' '){
									printf("A space follows a unary plus.\n");
									return -1;
								}else if(isOperator(n)){
									printf("Operator '%c' immediately follows another operator in the expression.\n", n);
									return -1;
								}else {
									printf("A space follows a unary plus????.\n");
									return -1;
								} 
							}else {
								PopPriority(postfixExpression, &post_index, s, ch);
								Push(s, ch);	
								status = OPERATOR;
								break;
							}
				case '*' :
				case '/' :	if (status == OPERATOR && *(infixExpression-1) != ' '){
								printf("Opreator '%c' immediately follows another operator in the expression.\n", ch);
								DestroyStack(s);
								return -1;
							}
							PopPriority(postfixExpression, &post_index, s, ch);
							Push(s, ch);	
							status = OPERATOR;
							break;
				case ')' :	infixExpression = getLeftBrace(s, infixExpression, postfixExpression, &post_index);
							if (infixExpression == NULL)	{
								printf("Wrong expression. No matched '(' before ')'\n");
								DestroyStack(s);
								return -1;	
							}
							break;
				default: printf("iliegal char :%c\n", ch); DestroyStack(s); return -1;
			}
			infixExpression++;
		}
		
	}
	if (status == OPERATOR) {
		printf("Some operator without operand in the expression.\n");
		DestroyStack(s);
		return -1;
	}
	while (StackEmpty(s)!=1) {
		char ch;
		Pop(s, &ch);
		if(ch == '('){
			printf("Wrong expression. No matched ')' after '('\n");
			DestroyStack(s);
			return 0;
		}
		postfixExpression[post_index++] = ch;
	}
	postfixExpression[post_index++] = '\0';
	DestroyStack(s);
	return 1;
}




/**
 * [computeValueFromPostfix description]
 * @Author   shenzhuo
 * @DateTime 2018-07-31T16:31:30+0800
 * @param    postfixExpression        [description]
 * @param    value                    [description]
 * @return                            [description]
 */
int computeValueFromPostfix(char *postfixExpression, double *value) {
	if(strlen(postfixExpression)<=0)	{
		printf("The input is EMPTY\n");
		return 0;
	}
	*value = -1;
	double t1, t2;
    SqStack1* stack = (SqStack1 *)malloc(sizeof(SqStack1));
    if (stack == NULL)	{
    	printf("Memory allocation failed.\n");
    	return -1;
    }
    InitStack1(stack);
    while(*postfixExpression != '\0') {
        char ch = *postfixExpression;
        if(isdigit(ch)) {
            double i = ch - '0';
            while(isdigit(*(postfixExpression+1))){
                postfixExpression++;
                i = i * 10 + (*postfixExpression) - '0';
            }
            Push1(stack, i);
        } else if(ch != '#' && ch != '@'){
        	if (ch == '$'){
        		Pop1(stack, &t1);
        		Push1(stack, -1*t1);
        	}else {
        		Pop1(stack, &t1);
	            Pop1(stack, &t2);
	            switch(ch) {
	            	case '+': *value = t1 + t2;	break;
	            	case '-': *value = t2 - t1; break;
	            	case '*': *value = t2 * t1; break;
	            	case '/': if(t1 == 0)	{printf("integer division or modulo by zero\n");	return -1;}
	            			 *value = t2 / t1;	break;
	            	default: printf("error! \n"); return -1;
	            }
	            Push1(stack,*value);
        	}
        }
        postfixExpression++;
    }
    if(stack->top == 0){
        Pop1(stack, value);
    }
    DestroyStack1(stack);
    return 1;
}


char *getNumber(SqStack *s, char *infixExpression, char postfixExpression[], int *post_index) {
	char ch;
	while(isdigit(ch = *infixExpression)) {
		postfixExpression[*post_index] = ch;
		++(*post_index);
		++infixExpression;
	}
	postfixExpression[*post_index] = '#';
	++(*post_index);
	return infixExpression;
}


char *getLeftBrace(SqStack *s, char *infixExpression, char postfixExpression[], int *post_index) {
	char ch;
	while (!StackEmpty(s) && Pop(s, &ch)){
		if (ch != '(') {
			postfixExpression[*post_index] = ch;
			(*post_index)++;
		} else {
			return infixExpression;; 
		}
	}
	return NULL;
}


void PopPriority(char postfixExpression[], int *post_index, SqStack *s, char c) {
	char ch;
	if (c == '+' || c == '-') {
		while(!StackEmpty(s)) {
			GetTop(s, &ch);
			if (ch == '*' || ch == '/' || ch == '+' || ch == '-' || ch == '@' || ch == '$') {
				postfixExpression[*post_index] = ch;
				Pop(s, &ch);
				(*post_index)++;
			} else {
				return;
			}
		}
	}else if (c == '*' || c == '/'){
		while(!StackEmpty(s)) {
			GetTop(s, &ch);
			if (ch == '*' || ch == '/' || ch == '@' || ch == '$') {
				postfixExpression[*post_index] = ch;
				Pop(s, &ch);
				(*post_index)++;
			}else {
				return;
			}
		}
	}
}


int isOperator(char ch) {
	return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}


char getPrevChar(char *infixExpression, char *infixExpressionHead) {
	infixExpression--;
	char ch;
	do {
		if (!isspace(ch = *infixExpression)){
			return ch;
		}
		infixExpression--;
	}while(infixExpression != infixExpressionHead);
	return '!';
}
