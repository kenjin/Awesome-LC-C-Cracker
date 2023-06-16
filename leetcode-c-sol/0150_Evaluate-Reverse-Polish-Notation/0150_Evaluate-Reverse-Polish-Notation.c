/**
150. Evaluate Reverse Polish Notation [M]
Ref: https://leetcode.com/problems/evaluate-reverse-polish-notation/

Evaluate the value of an arithmetic expression in Reverse Polish Notation.
Valid operators are +, -, *, /. Each operand may be an integer or another expression.

Note:
Division between two integers should truncate toward zero.
The given RPN expression is always valid. That means the expression would always evaluate to a result and there won't be any divide by zero operation.

Example 1:
Input: ["2", "1", "+", "3", "*"]
Output: 9
Explanation: ((2 + 1) * 3) = 9

Example 2:
Input: ["4", "13", "5", "/", "+"]
Output: 6
Explanation: (4 + (13 / 5)) = 6

Example 3:
Input: ["10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"]
Output: 22
Explanation:
  ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
= ((10 * (6 / (12 * -11))) + 17) + 5
= ((10 * (6 / -132)) + 17) + 5
= ((10 * 0) + 17) + 5
= (0 + 17) + 5
= 17 + 5
= 22

 */
typedef struct stackInfo
{
	int size;
	int top;
	int *s;  
} STACK;

STACK* createStack(int size)
{
	STACK *obj = malloc(sizeof(STACK));
	obj->size = size;
	obj->top = -1;
	obj->s = malloc(sizeof(int *)*size);
	return obj;
}

void destroyStack(STACK *obj)
{
	free(obj->s);
	free(obj);
}

void push(STACK *obj, int num)
{
	obj->top = (obj->top + 1) % obj->size;
	obj->s[obj->top] = num;
}

int pop(STACK *obj)
{
	int ret = obj->s[obj->top];
	obj->top = (obj->top - 1) % obj->size;
	return ret;
}

int str2int(char* s) 
{
	int n = strlen(s);
	int res = 0;
	int i = 0;
	int sign = s[0] == '-' ? -1 : 1;
	for (i = 0; i < n; i++) 
	{
		if (s[i] == '-')
		{
			continue;
		}
		res *= 10;
		res += s[i] - '0';
	}
	return res * sign;
}

int evalRPN(char ** tokens, int tokensSize)
{
	STACK *s = createStack(tokensSize);
	for (int i = 0; i < tokensSize; i++)
	{
		if ((strlen(tokens[i]) == 1) &&
				(tokens[i][0] == '+' || tokens[i][0] == '-' ||
				 tokens[i][0] == '*' || tokens[i][0] == '/'))
		{
			int num2 = pop(s);
			int num1 = pop(s);
			switch (tokens[i][0])
			{
				case '+':
					push(s, num1+num2);
					break;
				case '-':
					push(s, num1-num2);
					break;
				case '*':
					push(s, num1*num2);
					break;
				case '/':
					push(s, num1/num2);
					break;
			}
		} else
		{
			push(s, str2int(tokens[i]));
		}
	}
	int ret = pop(s);
	destroyStack(s);

	return ret;
}
