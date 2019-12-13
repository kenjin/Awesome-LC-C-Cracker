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

void stackPop(STACK* obj)
{
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


int sumSubarrayMins(int* A, int ASize)
{    
	int *sum = malloc(sizeof(int)*(ASize));    
	STACK *s = stackCreate(ASize);    
	stackPush(s, 0);
	sum[0] = A[0];

	int ret = A[0], modNum = 1e9+7;
	for (int i = 1; i < ASize; i++)
	{        
		while (!stackIsEmpty(s) && A[i] <= A[stackTop(s)]) 
		{
			stackPop(s);
		}

		if (stackIsEmpty(s))
		{
			sum[i] = ((i+1)*A[i]) % modNum;
		} else
		{
			sum[i] = (sum[stackTop(s)] + (i - stackTop(s)) * A[i]) % modNum;
		}
		stackPush(s, i);
		ret = (ret + sum[i]) % modNum;
	}

	free(sum);
	stackFree(s);    
	return ret;
}


