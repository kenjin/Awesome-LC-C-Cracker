typedef struct queueInfo
{
	int size;
	int cur;
	int front;
	int rear;
	int *arr;
} QUEUE;

QUEUE* createQueue(int size)
{
	QUEUE *obj = malloc(sizeof(QUEUE));
	obj->size = size;
	obj->cur = 0;
	obj->front = 0;
	obj->rear = -1;
	obj->arr = malloc(sizeof(int)*size);
	return obj;
}

void destroyQueue(QUEUE *obj)
{
	free(obj->arr);
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

void addQueue(QUEUE *obj, int key)
{
	if (isFull(obj))
	{
		return;
	}
	obj->rear = (obj->rear+1) % obj->size;
	obj->arr[obj->rear] = key;
	obj->cur++;
}

int delQueue(QUEUE *obj)
{
	if (isEmpty(obj))
	{
		return;
	}
	int ret = obj->arr[obj->front];
	obj->front = (obj->front+1) % obj->size;
	obj->cur--;
	return ret;
}

bool canVisitAllRooms(int** rooms, int roomsSize, int* roomsColSize)
{
	QUEUE *q = createQueue(roomsSize);
	// Checking record
	char *checkRoom = calloc(roomsSize, sizeof(char));
	// Record checking status
	int checkCtr = 1;
	checkRoom[0] = 1; 
	for (int i = 0; i < roomsColSize[0]; i++)
	{
		if (!checkRoom[rooms[0][i]])
		{
			addQueue(q, rooms[0][i]);
		}
	}

	while (!isEmpty(q))
	{
		int curKey = delQueue(q);
		// Room has been checked
		if (checkRoom[curKey])
		{
			continue;
		}
		// Update the record
		checkCtr++;
		checkRoom[curKey] = 1;
		for (int i = 0; i < roomsColSize[curKey]; i++)
		{
			if (!checkRoom[rooms[curKey][i]])
			{
				addQueue(q, rooms[curKey][i]);
			}
		}
		// All rooms have been checked
		if (checkCtr == roomsSize)
		{
			break;            
		}
	}

	free(checkRoom);
	destroyQueue(q);
	return (roomsSize == checkCtr) ? true : false;
}

