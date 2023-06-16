typedef struct queueInfo
{
	int size;
	int cur;
	int front;
	int rear;
	int **q;
} QUEUE;

QUEUE* createQueue(int size)
{
	QUEUE *obj = malloc(sizeof(QUEUE));
	obj->size = size;
	obj->cur = 0;
	obj->front = 0;
	obj->rear = -1;
	obj->q = malloc(sizeof(int*)*size);
	for (int x = 0; x < size; x++)
	{
		obj->q[x] = malloc(sizeof(int)*2);
	}
	return obj;
}

void destroyQueue(QUEUE *obj)
{
	for (int x = 0; x < obj->size; x++)
	{
		free(obj->q[x]);
	}
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

void enqueue(QUEUE *obj, int row, int col)
{
	if (isFull(obj))
	{
		return;
	}
	obj->rear = (obj->rear+1) % obj->size;
	obj->q[obj->rear][0] = row;
	obj->q[obj->rear][1] = col;
	obj->cur++;
}

int* dequeue(QUEUE *obj)
{
	if (isEmpty(obj))
	{
		return NULL;
	}
	int *ret = obj->q[obj->front];
	obj->front = (obj->front+1) % obj->size;
	obj->cur--;

	return ret;
}

void BFS(char** board, int bRowSize, int bColSize, int row, int col, QUEUE *q, char **visit)
{
	char dir[8][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, 
		{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

	// 'M' case
	if (board[row][col] == 'M')
	{
		board[row][col] = 'X';
		return;
	}
	// 'E' case
	// check the mine around the click
	int ctr = 0;
	for (int i = 0; i < 8; i++)
	{
		int x = dir[i][0] + row;
		int y = dir[i][1] + col;
		if (x < 0 || x >= bRowSize || y < 0 || y >= bColSize)
		{
			continue;
		}
		if (board[x][y] == 'M')
		{
			ctr++;
		}        
	}

	if (ctr == 0)
	{
		board[row][col] = 'B';            
		for (int i = 0; i < 8; i++)
		{            
			int x = dir[i][0] + row;
			int y = dir[i][1] + col;
			if (x < 0 || x >= bRowSize || y < 0 || y >= bColSize || visit[x][y])
			{
				continue;
			}
			enqueue(q, x, y);
			visit[x][y] = 1;
		}
	} else
	{
		board[row][col] = (ctr - 0) + '0';
	}    
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char** updateBoard(char** board, int boardSize, int* boardColSize, int* click, int clickSize, int* returnSize, int** returnColumnSizes)
{
	int bColSize = boardColSize[0];

	// Use queue to run BFS
	QUEUE *q = createQueue(boardSize*bColSize);
	// Use visit to avoid the duplicate BFS node
	char **visit = malloc(sizeof(char *)*boardSize);
	for (int x = 0; x < boardSize; x++)
	{
		visit[x] = calloc(bColSize, sizeof(char));
	}

	enqueue(q, click[0], click[1]);
	visit[click[0]][click[1]] = 1;
	while (!isEmpty(q))
	{
		int *cur = dequeue(q);
		BFS(board, boardSize, bColSize, cur[0], cur[1], q, visit);
	}

	// Update the result and release memory
	char **ret = malloc(sizeof(char *)*boardSize);
	*returnColumnSizes = malloc(sizeof(int)*boardSize);
	*returnSize = boardSize;
	for (int x = 0; x < boardSize; x++)
	{
		ret[x] = malloc(sizeof(char)*bColSize);
		(*returnColumnSizes)[x] = bColSize;
		memcpy(ret[x], board[x], sizeof(char)*bColSize);

		free(visit[x]);
	}
	free(visit);
	destroyQueue(q);

	return ret;
}

