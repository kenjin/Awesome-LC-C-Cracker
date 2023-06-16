#define MIN(a, b) (a < b ? a : b)
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

void stackPush(STACK* obj, int dist)
{
	obj->cur += 1;
	obj->arr[obj->cur] = dist;
}

int stackGetSize(STACK* obj)
{
	return obj->cur + 1;
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

void stackFree(STACK* obj) 
{
	free(obj->arr);
	free(obj);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* shortestToChar(char * S, char C, int* returnSize)
{
	int len = strlen(S);
	*returnSize = len;
	int *ret = calloc(len, sizeof(int));

	STACK *s = stackCreate(len);
	int i = 0, tmpDist = 10001;
	for (i = 0; i < len; i++)
	{
		if (S[i] == C)
		{            
			ret[i] = 0;
			int offset = 1;
			while (!stackIsEmpty(s) && i-offset >= 0)
			{
				int update = stackPop(s);     
				ret[i-offset] = MIN(update, offset);
				offset++;
			}
			tmpDist = 1;
		} else
		{
			stackPush(s, tmpDist);
			tmpDist++;
		}
	}

	if (!stackIsEmpty(s))
	{
		int offset = 1;
		while (!stackIsEmpty(s))
		{
			ret[i-offset] = stackPop(s);
			offset++;
		}
	}

	stackFree(s);
	return ret;
}

