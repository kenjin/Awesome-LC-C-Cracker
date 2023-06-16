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

void stackPush(STACK* obj, char *ptr)
{
	obj->cur += 1;
	obj->arr[obj->cur] = ptr;
}

int stackPop(STACK* obj)
{
	if (stackIsEmpty(obj))
	{
		printf("WARNING: empty stack!\n");
		return NULL;
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


bool checkPossibility(int* nums, int numsSize)
{
	STACK *s = stackCreate(numsSize);
	bool ret = true;
	char tolerance = 0;

	stackPush(s, nums[0]);
	for (int i = 1; i < numsSize; i++)
	{
		if (nums[i] < stackTop(s))
		{
			if (tolerance)
			{
				ret = false;
				break;
			}
			tolerance = 1;
			// Check the modifed num
			int tmp = stackPop(s);
			if (stackIsEmpty(s) || stackTop(s) <= nums[i])
			{
				stackPush(s, nums[i]);
			} else
			{
				stackPush(s, tmp);
			}            
		} else
		{
			stackPush(s, nums[i]);
		}
	}

	stackFree(s);
	return ret;
}


