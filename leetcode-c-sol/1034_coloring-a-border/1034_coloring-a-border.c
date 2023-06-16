#define IS_VISITED  (1)
#define IS_BOARDER  (2)

typedef struct dataInfo
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

DATA delQueue(QUEUE *obj)
{
	DATA ret = obj->data[obj->front];
	obj->front = (obj->front+1) % obj->size;
	obj->cur--;
	return ret;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** colorBorder(int** grid, int gridSize, int* gridColSize, int r0, int c0, int color, int* returnSize, int** returnColumnSizes)
{
	int colSize = gridColSize[0];
	int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
	int **visited = malloc(sizeof(int *)*gridSize);
	for (int i = 0; i < gridSize; i++)
	{
		visited[i] = calloc(colSize, sizeof(int));
	}        

	QUEUE *q = createQueue(gridSize*colSize);
	addQueue(q, r0, c0);
	int connectedColor = grid[r0][c0];

	while (!isEmpty(q))
	{        
		DATA tmp = delQueue(q);
		if (visited[tmp.x][tmp.y])
		{
			continue;
		}
		int found = 0;
		for (int i = 0; i < 4; i++)
		{
			int curX = tmp.x + dir[i][0];
			int curY = tmp.y + dir[i][1];
			if (curX < 0 || curX >= gridSize || curY < 0 || curY >= colSize || visited[curX][curY])
			{
				continue;
			}

			if (connectedColor == grid[curX][curY])
			{
				addQueue(q, curX, curY);
			} else
			{
				found = 1;
			}
		}
		if (tmp.x == 0 || tmp.y == 0 || tmp.x == gridSize-1 || tmp.y == colSize-1 || found)
		{
			grid[tmp.x][tmp.y] = color;
			visited[tmp.x][tmp.y] = IS_BOARDER;
		} else
		{
			visited[tmp.x][tmp.y] = IS_VISITED;
		}
	}

	*returnSize = gridSize;
	(*returnColumnSizes) = malloc(sizeof(int)*gridSize);
	for (int i = 0; i < gridSize; i++)
	{        
		(*returnColumnSizes)[i] = colSize;
	}
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < colSize; j++)
		{
			if (IS_BOARDER == visited[i][j])
			{
				grid[i][j] = color;
			}
		}        
	}

	destroyQueue(q);
	for (int i = 0; i < gridSize; i++)
	{
		free(visited[i]);        
	}
	free(visited);

	return grid;
}


