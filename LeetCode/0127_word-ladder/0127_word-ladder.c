typedef struct queueInfo
{
	int size;
	int cur;
	int front;
	int rear;
	// q[idx][0]: idx of the wordList
	// q[idx][1]: current length of transformation
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
	for (int i = 0; i < size; i++)
	{
		obj->q[i] = malloc(sizeof(int)*2);
	}
	return obj;
}

void destroyQueue(QUEUE *obj)
{
	for (int i = 0; i < obj->size; i++)
	{
		free(obj->q[i]);
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

void addQueue(QUEUE *obj, int idx, int len)
{
	if (isFull(obj))
	{
		return;
	}
	obj->rear = (obj->rear+1) % obj->size;
	obj->q[obj->rear][0] = idx;
	obj->q[obj->rear][1] = len;
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

bool oneLetterDiff(char *s1, char *s2)
{
	int len = strlen(s1);
	int diffCtr = 0;
	for (int idx = 0; idx < len; idx++)
	{
		if (s1[idx] != s2[idx])
		{
			diffCtr++;
		}
		if (diffCtr > 1)
		{
			return false;
		}
	}
	return true;
}

int ladderLength(char * beginWord, char * endWord, char ** wordList, int wordListSize)
{
	// Check that the endWord is in the wordList or not
	int endWordExist = 0;
	for (int i = 0; i < wordListSize; i++)
	{
		if (!strcmp(endWord, wordList[i]))
		{
			endWordExist = 1;
			break;
		}
	}
	if (!endWordExist)
	{
		return 0;
	}

	// 1. Init the queue and put the beginWord to it
	// 2. Let the beginWord use the "wordListSize" index
	QUEUE *q = createQueue(wordListSize);
	char *record = calloc(wordListSize+1, sizeof(char));
	addQueue(q, wordListSize, 1);
	record[wordListSize] = 1;
	while (!isEmpty(q))
	{
		int *curElement = delQueue(q);
		char *curStr = (curElement[0] == wordListSize ? beginWord : wordList[curElement[0]]);
		for (int i = 0; i < wordListSize; i++)
		{
			if (!record[i] && oneLetterDiff(curStr, wordList[i]))
			{
				if (!strcmp(endWord, wordList[i]))
				{
					int ret = curElement[1]+1;
					free(record);
					destroyQueue(q);
					return ret;
				}
				addQueue(q, i, curElement[1]+1);
				record[i] = 1;
			}
		}
	}
	free(record);
	destroyQueue(q);
	return 0;
}

