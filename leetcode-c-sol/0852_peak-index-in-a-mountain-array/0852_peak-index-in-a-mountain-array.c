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

void stackPush(STACK* obj, int idx)
{
	obj->cur += 1;
	obj->arr[obj->cur] = idx;
}

int stackTop(STACK* obj)
{
	if (stackIsEmpty(obj))
	{
		return -1;
	}
	return obj->arr[obj->cur];
}

void stackClean(STACK* obj) 
{
	obj->cur = -1;
}

bool isUpfill(STACK* obj) 
{
	return (obj->cur >= 1);
}

void stackFree(STACK* obj) 
{
	free(obj->arr);
	free(obj);
}

int peakIndexInMountainArray(int* A, int ASize)
{
	int ret = -1;
	STACK *s = stackCreate(ASize);
	for (int i = 0; i < ASize; i++)
	{        
		if (!stackIsEmpty(s) && A[i] < A[stackTop(s)])
		{
			int cur = stackTop(s);
			if (isUpfill(s))
			{
				ret = (ret != -1 && A[ret] > A[cur]) ? ret : cur;        
			}            
			stackClean(s);            
		}
		stackPush(s, i);
	}

	stackFree(s);
	return ret;
}


