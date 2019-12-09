#define MAX_NUM 80001
typedef struct qData
{
	int num;
	int ctr;    
} DATA;

typedef struct queueInfo
{
	int size;
	int cur;
	int front;
	int rear;
	DATA *data;
} QUEUE;

QUEUE* createQueue(int size)
{
	QUEUE *obj = malloc(sizeof(QUEUE));
	obj->size = size;
	obj->cur = 0;
	obj->front = 0;
	obj->rear = -1;
	obj->data = malloc(sizeof(DATA)*size);
	return obj;
}

void destroyQueue(QUEUE *obj)
{
	free(obj->data);
	free(obj);
}

bool isFull(QUEUE *obj)
{
	return (obj->cur == obj->size ? true : false) ;
}

bool isEmpty(QUEUE *obj)
{
	return (obj->cur == 0 ? true : false) ;
}

void addQueue(QUEUE *obj, int num, int ctr)
{
	if (isFull(obj))
	{
		return;
	}
	obj->rear = (obj->rear+1) % obj->size;
	obj->data[obj->rear].num = num;
	obj->data[obj->rear].ctr = ctr;
	obj->cur++;
}

int delQueue(QUEUE *obj)
{
	int ret = obj->data[obj->front].num;
	if (obj->data[obj->front].ctr <= 1)
	{
		obj->front = (obj->front+1) % obj->size;
		obj->cur--;
	} else
	{
		obj->data[obj->front].ctr --;
	}
	return ret;
}
int minIncrementForUnique(int* A, int ASize)
{    
	int record[MAX_NUM] = {0};

	int min = INT_MAX;
	int max = INT_MIN;
	int dup = 0;
	for (int i = 0; i < ASize; i++)
	{
		if (record[A[i]] >= 1)
		{
			dup++;
		}
		record[A[i]]++;
		min = (min < A[i] ? min : A[i]);
		max = (max > A[i] ? max : A[i]);
	}

	int cur = min;    
	QUEUE *q = createQueue(ASize);
	int ret = 0;
	int chkCtr = 0;
	while (chkCtr < dup)
	{
		if (record[cur] > 1)
		{
			addQueue(q, cur, record[cur]-1);
		}

		if (record[cur] == 0 && !isEmpty(q))
		{
			int tmp = cur - delQueue(q);
			ret += tmp;
			record[cur] = 1;
			chkCtr++;
		}
		cur++;
	}
	destroyQueue(q);

	return ret;
}

