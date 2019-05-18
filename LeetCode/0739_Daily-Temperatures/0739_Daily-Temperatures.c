/**

739. Daily Temperatures [Medium]

Given a list of daily temperatures T, return a list such that, for each day 
in the input, tells you how many days you would have to wait until a warmer 
temperature. If there is no future day for which this is possible, put 0 instead.

For example, given the list of temperatures T = [73, 74, 75, 71, 69, 72, 76, 73], 
your output should be [1, 1, 4, 2, 1, 1, 0, 0].

Note: The length of temperatures will be in the range [1, 30000]. 
      Each temperature will be an integer in the range [30, 100].

*/

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

void stackPop(STACK* obj)
{
	if (stackIsEmpty(obj))
	{
		printf("WARNING: empty stack!\n");
		return;
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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* dailyTemperatures(int* T, int TSize, int* returnSize)
{
	if (TSize == 0)
	{
		*returnSize = 0;
		return NULL;
	}

	/* Init all to zero */
	int *ret = calloc(TSize, sizeof(int));
	*returnSize = TSize;
	STACK *obj = stackCreate(TSize);

	for (int i = 0; i < TSize; i++)
	{
		if (stackIsEmpty(obj) || T[i] <= T[stackTop(obj)])
		{
			stackPush(obj, i);
		} else  /* Find the higher temperature */
		{
			int targetIdx = stackTop(obj);
			stackPop(obj);
			int target = T[targetIdx];
			ret[targetIdx] = i - targetIdx;
			i--;
		}
	}

	stackFree(obj);
	return ret;
}

