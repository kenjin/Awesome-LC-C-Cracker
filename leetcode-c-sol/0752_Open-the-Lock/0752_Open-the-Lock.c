/**
752. Open the Lock [M]
Ref: https://leetcode.com/problems/open-the-lock/

You have a lock in front of you with 4 circular wheels. Each wheel has 10 slots: '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'. The wheels can rotate freely and wrap around: for example we can turn '9' to be '0', or '0' to be '9'. Each move consists of turning one wheel one slot.

The lock initially starts at '0000', a string representing the state of the 4 wheels.

You are given a list of deadends dead ends, meaning if the lock displays any of these codes, the wheels of the lock will stop turning and you will be unable to open it.

Given a target representing the value of the wheels that will unlock the lock, return the minimum total number of turns required to open the lock, or -1 if it is impossible.

Example 1:
Input: deadends = ["0201","0101","0102","1212","2002"], target = "0202"
Output: 6
Explanation:
A sequence of valid moves would be "0000" -> "1000" -> "1100" -> "1200" -> "1201" -> "1202" -> "0202".
Note that a sequence like "0000" -> "0001" -> "0002" -> "0102" -> "0202" would be invalid,
because the wheels of the lock become stuck after the display becomes the dead end "0102".

 */

typedef struct queueInfo
{
	int size;
	int cur;
	int front;
	int rear;
	/* q[X][0]-q[X][3] save the index, 
	   q[X][4] save the wheels turns 
	 */
	int q[10000][5];
} QUEUE;

QUEUE* createQueue()
{
	QUEUE *obj = malloc(sizeof(QUEUE));
	obj->size = 10000;
	obj->cur = 0;
	obj->front = 0;
	obj->rear = -1;

	return obj;
}

void destroyQueue(QUEUE *obj)
{
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

void addQueue(QUEUE *obj, int x, int y, int z, int w, int turns)
{
	if (isFull(obj))
	{
		return;
	}
	obj->rear = (obj->rear+1) % obj->size;
	obj->q[obj->rear][0] = x;
	obj->q[obj->rear][1] = y;
	obj->q[obj->rear][2] = z;
	obj->q[obj->rear][3] = w;
	obj->q[obj->rear][4] = turns;
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

int openLock(char ** deadends, int deadendsSize, char * target)
{
	if (!strcmp(target,"0000"))
	{
		return -1;
	}

	char map[10][10][10][10];
	memset(map, 0, sizeof(char)*10000);
	QUEUE *queue = createQueue();
	for (int i = 0; i < deadendsSize; i++)
	{
		if (!strcmp(deadends[i],"0000"))
		{
			return -1;
		}
		/* set 1 to indicate the deadends */
		map[deadends[i][0]-'0'][deadends[i][1]-'0'][deadends[i][2]-'0'][deadends[i][3]-'0'] = 1;
	}
	/* set 2 to indicate the end */
	map[target[0]-'0'][target[1]-'0'][target[2]-'0'][target[3]-'0'] = 2;

	addQueue(queue, 0, 0, 0, 0, 0);
	int dir[8][4] = {{1,0,0,0}, {9,0,0,0}, {0,1,0,0}, {0,9,0,0}, 
		{0,0,1,0}, {0,0,9,0}, {0,0,0,1}, {0,0,0,9}};
	/* BFS */
	while (!isEmpty(queue))
	{
		int *cur= delQueue(queue);
		map[cur[0]][cur[1]][cur[2]][cur[3]] = -1;

		int curTurns = cur[4]+1;
		for (int i = 0; i < 8; i++)
		{
			int n1 = (cur[0] + dir[i][0]) % 10;
			int n2 = (cur[1] + dir[i][1]) % 10;
			int n3 = (cur[2] + dir[i][2]) % 10;
			int n4 = (cur[3] + dir[i][3]) % 10;
			if (2 == map[n1][n2][n3][n4])
			{
				return curTurns;
			}
			if (0 == map[n1][n2][n3][n4])
			{
				map[n1][n2][n3][n4] = 1;
				addQueue(queue, n1, n2, n3, n4, curTurns);
			}
		}       
	}

	destroyQueue(queue);
	return -1;
}

