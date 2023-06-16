/**

84. Largest Rectangle in Histogram [Hard]
Ref: https://leetcode.com/problems/largest-rectangle-in-histogram/

 */

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

int largestRectangleArea(int* heights, int heightsSize)
{
	if (heightsSize == 0 || heights == NULL)
	{
		return 0;
	}

	STACK* stack = stackCreate(heightsSize);
	int *h = calloc(heightsSize+1, sizeof(int));
	memcpy(h, heights, sizeof(int)*heightsSize);
	int max = 0;
	for (int i = 0; i <= heightsSize; i++)
	{
		if (stackIsEmpty(stack) || (h[i] > h[stackTop(stack)]))
		{
			stackPush(stack, i);
		} else
		{
			int curIdx = stackTop(stack); stackPop(stack);
			int leftLimitIdx = stackTop(stack);
			max = (max > (i-leftLimitIdx-1)*h[curIdx] ? max : (i-leftLimitIdx-1)*h[curIdx]);
			i--;
		}
	}

	free(h);
	stackFree(stack);
	return max;
}


