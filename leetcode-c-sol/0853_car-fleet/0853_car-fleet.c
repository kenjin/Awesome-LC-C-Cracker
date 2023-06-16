typedef struct
{
	int pos;
	int speed;
	double time;
} DATA;

typedef struct
{
	int size;
	int cur;
	double *arr;
} STACK;

STACK* stackCreate(int size) 
{
	STACK *obj = malloc(sizeof(STACK));
	obj->size = size;
	obj->cur = -1;
	obj->arr = malloc(sizeof(double)*size);
	return obj;
}

bool stackIsEmpty(STACK *obj)
{
	return (obj->cur == -1 ? true : false);
}

void stackPush(STACK* obj, double time)
{
	obj->cur += 1;
	obj->arr[obj->cur] = time;
}

int stackGetSize(STACK* obj)
{
	return obj->cur + 1;
}

double stackPop(STACK* obj)
{
	if (stackIsEmpty(obj))
	{
		printf("WARNING: empty stack!\n");
		return;
	}

	obj->cur -= 1;
	return obj->arr[obj->cur+1];
}

double stackTop(STACK* obj)
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

int compare(const void *a, const void *b)
{
	DATA d1 = *(DATA *)a;
	DATA d2 = *(DATA *)b;

	return d1.pos - d2.pos;
}

int carFleet(int target, int* position, int positionSize, int* speed, int speedSize)
{
	if (speedSize == 0)
	{
		return 0;
	}

	// Calculate the time needed to the target
	DATA *d = malloc(sizeof(DATA)*speedSize);    
	for (int i = 0; i < speedSize; i++)
	{
		d[i].pos = position[i];
		d[i].speed = speed[i];
		d[i].time =  (double)(target - position[i])/speed[i];
	}    
	// Sort via position
	qsort(d, speedSize, sizeof(DATA), compare);

	STACK *s = stackCreate(speedSize);
	for (int i = 0; i < speedSize; i++)
	{        
		if (stackIsEmpty(s))
		{
			stackPush(s, d[i].time);
			continue;
		}        
		// All initial positions are different, no need to consider equal case
		if (d[i].time < stackTop(s))
		{
			stackPush(s, d[i].time);
		} else
		{
			stackPop(s);
			i--;
		}
	}

	int ret = stackGetSize(s);
	stackFree(s);
	free(d);    
	return ret;
}

