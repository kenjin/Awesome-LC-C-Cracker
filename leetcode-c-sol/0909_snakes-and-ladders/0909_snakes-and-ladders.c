typedef struct
{
	int step;
	int val;
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

bool isEmpty(QUEUE *obj)
{
	return (obj->cur == 0 ? true : false) ;
}

bool isFull(QUEUE *obj)
{
	return (obj->cur == obj->size ? true : false) ;
}

void addQueue(QUEUE *obj, int step, int val)
{
	if (isFull(obj))
	{
		return;
	}
	obj->rear = (obj->rear+1) % obj->size;
	obj->data[obj->rear].step = step;
	obj->data[obj->rear].val = val;
	obj->cur++;
}

DATA delQueue(QUEUE *obj)
{
	if (isEmpty(obj))
	{
		return;
	}
	DATA ret = obj->data[obj->front];
	obj->front = (obj->front+1) % obj->size;
	obj->cur--;
	return ret;
}

void transferCoordinate(int boardSize, int val, int *x, int *y)
{
	*x = (boardSize-1) - (val / boardSize);
	*y = ((boardSize - 1 - *x) % 2 == 0 ? val % boardSize : (boardSize - 1 - (val % boardSize)));
}

int snakesAndLadders(int** board, int boardSize, int* boardColSize)
{
	int minStep, endX, endY, addVal;
	char **visited = malloc(sizeof(int *)*boardSize);
	for (int i = 0; i < boardSize; i++)
	{
		visited[i] = calloc(boardSize, sizeof(int));
	}

	QUEUE *q = createQueue(boardSize*boardSize);
	minStep = boardSize+1;

	// Calculate the end point
	endX = 0;
	endY = (boardSize % 2 == 0 ? 0 : boardSize-1);
	// Add the first square info
	addVal = (board[0][0] == -1 ? 0: board[0][0]-1);
	addQueue(q, 0, addVal);
	while (!isEmpty(q))
	{
		DATA cur = delQueue(q);
		int x, y;
		transferCoordinate(boardSize, cur.val, &x, &y);
		if (x == endX && y == endY)
		{
			minStep = (minStep < (cur.step) ? minStep : (cur.step));
		}
		// move at most 6 destinations
		int tmpVal = cur.val + 1;
		while (tmpVal <= cur.val + 6)
		{
			if (tmpVal == boardSize*boardSize)
			{
				break;
			}

			transferCoordinate(boardSize, tmpVal, &x, &y);
			if (visited[x][y])
			{
				tmpVal++;
				continue;
			}         

			if (x == endX && y == endY)
			{
				minStep = (minStep < (cur.step + 1) ? minStep : (cur.step + 1));
			}

			addVal = (board[x][y] != -1) ? (board[x][y]-1) : tmpVal;
			addQueue(q, cur.step + 1, addVal);
			// Ignore the duplicate point
			visited[x][y] = 1;

			tmpVal++;            
		}
	}

	destroyQueue(q);
	for (int i = 0; i < boardSize; i++)
	{
		free(visited[i]);
	}
	free(visited);

	return (minStep == boardSize+1) ? -1 : minStep;
}

