typedef struct
{
	int size;
	int cur;
	int *arr;
} STACK;

/** initialize your data structure here. */
STACK* stackCreate(int size) 
{
	STACK *obj = malloc(sizeof(STACK));
	obj->size = size;
	obj->cur = -1;
	obj->arr = malloc(sizeof(int)*size);
	return obj;
}

bool stackIsEmpty(STACK *obj)
{
	return (obj->cur == -1 ? true : false);
}

void stackPush(STACK* obj, int idx)
{
	obj->cur += 1;
	obj->arr[obj->cur] = idx;
}

int stackPop(STACK* obj)
{
	if (stackIsEmpty(obj))
	{
		printf("WARNING: empty stack!\n");
		return -1;
	}

	obj->cur -= 1;
	return obj->arr[obj->cur+1];
}

int stackTop(STACK* obj)
{
	if (stackIsEmpty(obj))
	{
		return -1;
	}
	return obj->arr[obj->cur];
}

void stackFree(STACK* obj) 
{
	free(obj->arr);
	free(obj);
}

int calculate(char * s)
{
	STACK *obj = stackCreate(100000);

	int idx = 0;
	long sum = 0;
	char op = '+'; //default
	while (1)
	{
		if (s[idx] >= '0' && s[idx] <= '9')
		{
			sum = sum*10 + (s[idx]-'0');
		}
		if (s[idx] == '*' || s[idx] == '/' || s[idx] == '+' || s[idx] == '-' || s[idx] == '\0')
		{
			int popNum;
			switch (op)
			{
				case '-':
					sum *= -1;
				case '+':
					stackPush(obj, sum);
					break;
				case '*':
					popNum = stackPop(obj);
					stackPush(obj, popNum*sum);
					break;
				case '/':
					popNum = stackPop(obj);
					stackPush(obj, popNum/sum);
					break;
				default:
					break;

			}
			if (s[idx] == '\0')
			{
				break;
			}
			sum = 0;
			op = s[idx];
		}
		idx++;
	}

	long ret = 0;
	while (!stackIsEmpty(obj))
	{
		ret += stackPop(obj);
	}
	stackFree(obj);
	return ret;
}

