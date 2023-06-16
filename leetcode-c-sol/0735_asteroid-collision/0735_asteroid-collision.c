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

int stackCurSize(STACK *obj)
{
	return obj->cur + 1;
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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* asteroidCollision(int* asteroids, int asteroidsSize, int* returnSize)
{
	STACK *s = stackCreate(asteroidsSize);
	for (int i = 0; i < asteroidsSize; i++)
	{
		int cur = asteroids[i];
		while (1)
		{
			if (cur > 0 || stackIsEmpty(s) || stackTop(s) < 0)
			{
				stackPush(s, cur);
				break;
			} else
			{
				int tmp = stackPop(s);
				if (cur*(-1) > tmp)
				{
					continue;
				} else if (cur*(-1) < tmp)
				{
					stackPush(s, tmp);
					break;
				} else
				{
					break;
				}
			}
		}
	}

	*returnSize = stackCurSize(s);
	int *ret = malloc(sizeof(int)*(*returnSize));
	for (int i = *returnSize - 1; i >= 0; i--)
	{
		ret[i] = stackPop(s);
	}
	stackFree(s);
	return ret;
}

