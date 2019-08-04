typedef struct queueInfo
{
	int size;
	int cur;
	int front;
	int rear;
	int *q;
} QUEUE;

QUEUE* createQueue(int size)
{
	QUEUE *obj = malloc(sizeof(QUEUE));
	obj->size = size;
	obj->cur = 0;
	obj->front = 0;
	obj->rear = -1;
	obj->q = malloc(sizeof(int*)*size);
	return obj;
}

void destroyQueue(QUEUE *obj)
{
	free(obj->q);
	free(obj);
}

bool isEmpty(QUEUE *obj)
{
	return (obj->cur == 0 ? true : false) ;
}

bool isFull(QUEUE *obj)
{
	return (obj->cur == obj->size ? true : false) ;
}

void enqueue(QUEUE *obj, int idx)
{
	if (isFull(obj))
	{
		return;
	}
	obj->rear = (obj->rear+1) % obj->size;
	obj->q[obj->rear] = idx;
	obj->cur++;
}

int dequeue(QUEUE *obj)
{
	if (isEmpty(obj))
	{
		return -1;
	}
	int ret = obj->q[obj->front];
	obj->front = (obj->front+1) % obj->size;
	obj->cur--;

	return ret;
}

int findCircleNum(int** M, int MSize, int* MColSize)
{
	char *visit = calloc(MSize, sizeof(char));
	QUEUE *q = createQueue(MSize);

	int ret = 0;
	for (int x = 0; x < MSize; x++)
	{
		if (visit[x])
		{
			continue;
		} else
		{
			ret++;
			enqueue(q, x);
			visit[x] = 1;
		}

		while (!isEmpty(q))
		{
			int idx = dequeue(q);

			for (int i = 0; i < MSize; i++)
			{
				if (i == idx || visit[i])
				{
					continue;
				}
				if (M[idx][i])
				{
					enqueue(q, i);
					visit[i] = 1;
				}
			}
		}
	}
	destroyQueue(q);
	return ret;
}

