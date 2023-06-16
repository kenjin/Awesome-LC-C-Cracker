
typedef struct
{
	int size;
	int cur;
	char *arr;
} STACK;

STACK* stackCreate(int size) 
{
	STACK *obj = malloc(sizeof(STACK));
	obj->size = size;
	obj->cur = -1;
	obj->arr = malloc(sizeof(char)*size);
	return obj;
}

int stackGetSize(STACK* obj)
{
	return obj->cur + 1;
}

bool stackIsEmpty(STACK *obj)
{
	return (obj->cur == -1 ? true : false);
}

void stackPush(STACK* obj, char c)
{
	obj->cur += 1;
	obj->arr[obj->cur] = c;
}

char stackPop(STACK* obj)
{
	if (stackIsEmpty(obj))
	{
		printf("WARNING: empty stack!\n");
		return;
	}

	obj->cur -= 1;
	return obj->arr[obj->cur+1];
}

char stackTop(STACK* obj)
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

char * removeDuplicates(char * S)
{
	int len = strlen(S);
	STACK *st = stackCreate(len);
	for (int i = 0; i < len; i++)
	{
		if (!stackIsEmpty(st) && S[i] == stackTop(st))
		{
			stackPop(st);
			continue;
		} 
		stackPush(st, S[i]);
	}

	int size = stackGetSize(st);
	S[size] = 0;
	for (int i = size-1; i >= 0; i--)
	{
		S[i] = stackPop(st);
	}
	stackFree(st);
	return S;
}

