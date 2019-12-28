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
	obj->cur -= 1;
	return;
}

int stackTop(STACK* obj)
{
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
int* sortArrayByParityII(int* A, int ASize, int* returnSize)
{
	STACK *sOdd = stackCreate(ASize);
	STACK *sEven = stackCreate(ASize);

	for (int i = 0; i < ASize; i++)
	{
		if ((A[i] & 0x1) > 0)
		{
			stackPush(sOdd, A[i]);
		} else
		{
			stackPush(sEven, A[i]);
		}
	}

	for (int i = 0; i < ASize; i++)
	{
		if (i%2)
		{
			A[i] = stackTop(sOdd); stackPop(sOdd);
		} else
		{
			A[i] = stackTop(sEven); stackPop(sEven);
		}
	}

	stackFree(sOdd);
	stackFree(sEven);
	*returnSize = ASize;
	return A;
}


