/**
542. 01 Matrix [M]
Ref: https://leetcode.com/problems/01-matrix/

Given a matrix consists of 0 and 1, find the distance of the nearest 0 for each cell.
The distance between two adjacent cells is 1.


Example 1:
Input:
[[0,0,0],
 [0,1,0],
 [0,0,0]]

Output:
[[0,0,0],
 [0,1,0],
 [0,0,0]]

 Example 2:
Input:
[[0,0,0],
 [0,1,0],
 [1,1,1]]

Output:
[[0,0,0],
 [0,1,0],
 [1,2,1]]


Note:
The number of elements of the given matrix will not exceed 10,000.
There are at least one 0 in the given matrix.
The cells are adjacent in only four directions: up, down, left and right.

 */

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
        obj->q[x] = malloc(sizeof(int)*3);
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

void addQueue(QUEUE *obj, int x, int y)
{
    if (isFull(obj))
    {
        return;
    }
    obj->rear = (obj->rear+1) % obj->size;
    obj->q[obj->rear][0] = x;
    obj->q[obj->rear][1] = y;
    obj->cur++;
}

int* delQueue(QUEUE *obj)
{
    if (isEmpty(obj))
    {
        return;
    }
    int *ret = obj->q[obj->front];
    obj->front = (obj->front+1) % obj->size;
    obj->cur--;

    return ret;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** updateMatrix(int** matrix, int matrixSize, int* matrixColSize, int* returnSize, int** returnColumnSizes)
{
    if (matrixSize == 0)
    {
        *returnSize = 0;
        return NULL;
    }
    /* Init return object */
    int **ret = malloc(sizeof(int*)*matrixSize);
    *returnSize = matrixSize;
    *returnColumnSizes = calloc(matrixSize, sizeof(int));

    /* Init queue and add "0" element to the queue */
    /* Use "mark" table to avoid the duplicate access */
    QUEUE *queue = createQueue(matrixSize*matrixColSize[0]);
    char **mark = malloc(sizeof(char*)*matrixSize);
    for (int i = 0; i < matrixSize; i++)
    {
        ret[i] = calloc(matrixColSize[i], sizeof(int));
        (*returnColumnSizes)[i] = matrixColSize[i];
        mark[i] = calloc(matrixColSize[i], sizeof(char));

        for (int j = 0; j < matrixColSize[i]; j++)
        {
            if (matrix[i][j] == 0)
            {
                addQueue(queue, i, j);
                mark[i][j] = 1;
            }
        }
    }

    int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int len = 0;
    while (!isEmpty(queue))
    {
        int curQueueSize = queue->cur; /* current queue size */
        len++;
        while (curQueueSize > 0)
        {
            int *cur = delQueue(queue);
            curQueueSize--;
            for (int x = 0; x < 4; x++)
            {
                int n1 = cur[0]+dir[x][0];
                int n2 = cur[1]+dir[x][1];
                if (n1 < 0 || n1 >= matrixSize ||
                    n2 < 0 || n2 >= matrixColSize[0] ||
                    mark[n1][n2] == 1)
                {
                    continue;
                }
                /* Update */
                ret[n1][n2] = len;
                mark[n1][n2] = 1;
                addQueue(queue, n1, n2);
            }
        }
    }
    free(mark);
    destroyQueue(queue);
    return ret;
}

