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

int stackPop(STACK* obj)
{
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



bool find132pattern(int* nums, int numsSize)
{
	STACK *s = stackCreate(numsSize);
	int numJ = INT_MIN;

	for (int x = numsSize-1; x >= 0; x--)
	{
		if (nums[x] < numJ)
		{
			return true;
		}        
		while (!stackIsEmpty(s) && nums[x] > stackTop(s))
		{
			numJ = stackPop(s);
		}
		stackPush(s, nums[x]);
	}

	stackFree(s);
	return false;
}


