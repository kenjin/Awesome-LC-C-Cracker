typedef struct
{
	int x;
	int y;
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

void addQueue(QUEUE *obj, int row, int col)
{
	if (isFull(obj))
	{
		return;
	}
	obj->rear = (obj->rear+1) % obj->size;
	obj->data[obj->rear].x = row;
	obj->data[obj->rear].y = col;
	obj->cur++;
}

int getSizeQueue(QUEUE *obj)
{
	return obj->cur;
}

DATA delQueue(QUEUE *obj)
{
	DATA ret = obj->data[obj->front];
	obj->front = (obj->front+1) % obj->size;
	obj->cur--;
	return ret;
}

int orangesRotting(int** grid, int gridSize, int* gridColSize)
{

	QUEUE *q = createQueue(gridSize*gridColSize[0]);
	int freshCtr = 0;
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridColSize[0]; j++)
		{
			if (grid[i][j] == 2)
			{
				addQueue(q, i, j);
			} else if (grid[i][j] == 1)
			{
				freshCtr++;   
			}
		}
	}
	int min = 0;
	int dir[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
	while (!isEmpty(q) && freshCtr > 0)
	{
		min++;
		int qSize = getSizeQueue(q);
		for (int x = 0; x < qSize; x++)
		{
			DATA cur = delQueue(q);
			for (int i = 0; i < 4; i++)
			{
				int checkRow = cur.x + dir[i][0];
				int checkCol = cur.y + dir[i][1];
				if (checkRow >= 0 && checkCol >= 0 && 
						checkRow < gridSize && checkCol < gridColSize[0] &&
						grid[checkRow][checkCol] == 1)
				{
					addQueue(q, checkRow, checkCol);
					grid[checkRow][checkCol] = 2;
					freshCtr--;
				}
			}
		}
	}

	destroyQueue(q);
	return (freshCtr > 0 ? -1 : min);
}

