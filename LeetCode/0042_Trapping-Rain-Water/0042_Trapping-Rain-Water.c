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

int stackPop(STACK* obj)
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

int trap(int* height, int heightSize)
{
	STACK *s = stackCreate(heightSize+1);

	int ret = 0;
	for (int i = 0; i < heightSize; i++)
	{
		if (stackIsEmpty(s) && height[i] == 0)
		{
			continue;
		}
		if (!stackIsEmpty(s))
		{
			int top = height[stackTop(s)];            
			if (height[i] > top) 
			{
				int maxHeight = height[i]; 
				int lowValleyIdx = stackPop(s);
				while (!stackIsEmpty(s))
				{
					int chkIdx = stackPop(s);
					int diff = (maxHeight > height[chkIdx]) ? height[chkIdx] - height[lowValleyIdx]
						: maxHeight - height[lowValleyIdx];

					if (diff != 0)
					{
						ret += diff*(i-chkIdx-1);
					}
					if (maxHeight < height[chkIdx])
					{
						stackPush(s, chkIdx);
						break;
					}
					lowValleyIdx = chkIdx;
				}
			}
		}
		stackPush(s, i);
	}

	stackFree(s);
	return ret;
}

