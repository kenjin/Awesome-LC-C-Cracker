/**
286. Walls and Gates [Medium]

You are given a m x n 2D grid initialized with these three possible values.

-1 - A wall or an obstacle.
0 - A gate.
INF - Infinity means an empty room. We use the value 231 - 1 = 2147483647 to represent INF as you may assume that the distance to a gate is less than 2147483647.
Fill each empty room with the distance to its nearest gate. If it is impossible to reach a gate, it should be filled with INF.

Example:

Given the 2D grid:

INF  -1  0  INF
INF INF INF  -1
INF  -1 INF  -1
  0  -1 INF INF

After running your function, the 2D grid should be:

  3  -1   0   1
  2   2   1  -1
  1  -1   2  -1
  0  -1   3   4

  */



typedef struct queue
{
    int size;
    int curSize;
    int rear;
    int front;
    int **arr;
} QUEUE;

QUEUE* createQueue(int qSize)
{
    QUEUE *q = malloc(sizeof(QUEUE));
    q->size = qSize;
    q->rear = -1;
    q->front = 0;
    q->curSize = 0;
    q->arr = (int**)malloc(sizeof(int *) * qSize);
    for (int x = 0; x < qSize; x++)
    {
        q->arr[x] = malloc(sizeof(int)*2);
    }

    return q;
}


#define EMPTY_QUEUE (-2)

bool isEmpty(QUEUE *q)
{
    return (q->curSize == 0 ? true : false);
}

bool isFull(QUEUE *q)
{
    return (q->curSize == q->size ? true : false);
}

void enQueue(QUEUE *q, int row, int col)
{
    if (isFull(q))
    {
        printf("WARNING FULL !!!\n");
        return;
    }
    //printf("    => enque [%d,%d]\n", row, col);
    q->rear = ((q->rear)+1) % q->size;
    q->arr[q->rear][0] = row;
    q->arr[q->rear][1] = col;
    q->curSize += 1;
}

int* deQueue(QUEUE *q)
{
    if (isEmpty(q))
    {
        return NULL;
    }

    int *ret = q->arr[q->front];
    q->front = ((q->front)+1) % q->size;
    q->curSize -= 1;

    //printf("    => deque [%d,%d]\n", ret[0], ret[1]);
    return ret;
}

void deleteQueue(QUEUE *q)
{
    for (int x = 0; x < q->size; x++)
    {
        free(q->arr[x]);
    }
    free(q->arr);
    free(q);
}

void printRooms(int** rooms, int row, int col)
{
    printf("\n[Rooms]\n");
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (rooms[i][j] == INT_MAX)
                printf("INF ");
            else
                printf("%3d ", rooms[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void wallsAndGates(int** rooms, int roomsSize, int* roomsColSize){
    if (!roomsSize)
    {
        return;
    }

    int colSize = roomsColSize[0];
    //printRooms(rooms, roomsSize, colSize);
    QUEUE *q = createQueue(roomsSize * colSize);

    // Push all the gate to the queue
    for (int i = 0; i < roomsSize; i++)
    {
        for (int j = 0; j < colSize; j++)
        {
            if (rooms[i][j] == 0)
            {
                enQueue(q, i, j);
            }
        }
    }

    int direction[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    while (!isEmpty(q))
    {
        int *curRoom = deQueue(q);
        int curRow = curRoom[0];
        int curCol = curRoom[1];
        printRooms(rooms, roomsSize, colSize);
        for (int i = 0; i < 4; i++)
        {
            int x = curRow + direction[i][0];
            int y = curCol + direction[i][1];

            if (x >= 0 && x < roomsSize && y >= 0 && y < colSize && rooms[x][y] > rooms[curRow][curCol])
            {
                rooms[x][y] = rooms[curRow][curCol] + 1;
                enQueue(q, x, y);
            }
        }
    }

    deleteQueue(q);
}

