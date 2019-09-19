#define MAX_TEST_CASE 10000

typedef struct 
{
	int size;
	int cur;
	int front;
	int rear;
	int *q;
} RecentCounter;

RecentCounter* createQueue(int size)
{
	RecentCounter *obj = malloc(sizeof(RecentCounter));
	obj->size = size;
	obj->cur = 0;
	obj->front = 0;
	obj->rear = -1;
	obj->q = malloc(sizeof(int)*size);
	return obj;
}

void destroyQueue(RecentCounter *obj)
{
	free(obj->q);
	free(obj);
}

bool isEmpty(RecentCounter *obj)
{
	return (obj->cur == 0 ? true : false) ;
}

bool isFull(RecentCounter *obj)
{
	return (obj->cur == obj->size ? true : false) ;
}

int getSizeQueue(RecentCounter *obj)
{
	return obj->cur;
}

void addQueue(RecentCounter *obj, int val)
{
	if (isFull(obj))
	{
		return;
	}
	obj->rear = (obj->rear+1) % obj->size;
	obj->q[obj->rear] = val;
	obj->cur++;
}

int peakQueue(RecentCounter *obj)
{
	return (isEmpty(obj) ? -1 : obj->q[obj->front]);
}

void delQueue(RecentCounter *obj)
{
	if (isEmpty(obj))
	{
		return;
	}
	obj->front = (obj->front+1) % obj->size;
	obj->cur--;
}

RecentCounter* recentCounterCreate() 
{
	RecentCounter *obj = createQueue(MAX_TEST_CASE);
	return obj;
}

int recentCounterPing(RecentCounter* obj, int t) 
{
	int minTime = t - 3000;
	while (!isEmpty(obj))
	{
		int peak = peakQueue(obj);
		if (peak >= minTime)
		{
			break;
		}
		delQueue(obj);            
	}    
	addQueue(obj, t);
	return getSizeQueue(obj);
}

void recentCounterFree(RecentCounter* obj) 
{
	destroyQueue(obj);
}

/**
 * Your RecentCounter struct will be instantiated and called as such:
 * RecentCounter* obj = recentCounterCreate();
 * int param_1 = recentCounterPing(obj, t);

 * recentCounterFree(obj);
 */
