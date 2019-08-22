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

void stackPush(STACK* obj, int id)
{
	obj->cur += 1;
	obj->arr[obj->cur] = id;
}

void stackPop(STACK* obj)
{
	if (stackIsEmpty(obj))
	{
		printf("WARNING: empty stack!\n");
		return;
	}

	obj->cur -= 1;
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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* exclusiveTime(int n, char ** logs, int logsSize, int* returnSize)
{
	STACK *s = stackCreate(logsSize);
	int *ret = calloc(n, sizeof(int));
	*returnSize = n;

	int id = 0, time = 0;
	char op[16];
	int last = 0;
	for (int i = 0; i < logsSize; i++)
	{
		if (op[0] == 's') // "start"
		{            
			if (!stackIsEmpty(s))
			{
				ret[stackTop(s)] += (time - last);
			}
			stackPush(s, id);
			last = time;
		} else
		{
			ret[stackTop(s)] += (time - last + 1);
			stackPop(s);
			last = time + 1;
		}        
	}
	stackFree(s);
	return ret;
}
