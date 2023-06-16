typedef struct
{
	int size;
	int cur;
	int *arr;
} STACK;

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

void stackPush(STACK* obj, int val)
{
	obj->cur += 1;
	obj->arr[obj->cur] = val;
}

void stackPop(STACK* obj)
{
	if (!stackIsEmpty(obj))
	{
		obj->cur -= 1;
	}
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

int calPoints(char ** ops, int opsSize)
{
	STACK *s = stackCreate(opsSize);

	for (int i = 0; i < opsSize; i++)
	{
		char *cur = ops[i];
		if (*cur == 'C')
		{
			stackPop(s);
		} else if (*cur == 'D')
		{
			int dNum = stackTop(s);
			stackPush(s, dNum*2);
		} else if (*cur == '+')
		{
			int p1 = stackTop(s); stackPop(s);
			int p2 = stackTop(s);
			stackPush(s, p1);
			stackPush(s, p1+p2);
		} else
		{
			int neg = 1, num = 0;
			if (*cur == '-')
			{
				neg = -1;
				cur++;
			}
			while (*cur)
			{
				num *= 10;
				num += *cur - '0';                
				cur++;
			}
			num *= neg;
			stackPush(s, num);
		}
	}

	int ret = 0;
	while (!stackIsEmpty(s))
	{
		ret += stackTop(s);
		stackPop(s);
	}
	stackFree(s);
	return ret;
}

