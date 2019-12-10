#define DEF_USERS         1001
#define MAX_POST           10

typedef struct
{
	int pId;
	int pTime;    
} POST_DATA;

typedef struct list_node
{
	int uId;
	struct list_node    *next; 
} LIST_NODE;

typedef struct queueInfo
{
	int size;
	int cur;
	int front;
	int rear;
	POST_DATA *data;
} QUEUE;

typedef struct
{
	QUEUE       *postQ;
	LIST_NODE   *headF;
} USER_INFO;

typedef struct
{
	int             time;
	USER_INFO       u[DEF_USERS];
} Twitter;


bool checkNodeExist(LIST_NODE *head, int id)
{
	LIST_NODE *tmp = head->next;
	while (tmp)
	{
		if (tmp->uId == id)
		{
			return true;            
		}
		tmp = tmp->next;
	}

	return false;
}

void addNode(LIST_NODE *head, int id)
{    
	LIST_NODE *obj = calloc(1, sizeof(LIST_NODE));
	obj->uId = id;        
	obj->next = head->next;
	head->next = obj;    
}

void delNode(LIST_NODE *head, int id)
{
	LIST_NODE *tmp = head->next;
	LIST_NODE *pre = head;
	while (tmp)
	{
		if (tmp->uId == id)
		{
			pre->next = tmp->next;
			free(tmp);
			break;
		}
		pre = tmp;
		tmp = tmp->next;
	}
}

void freeNode(LIST_NODE *head)
{
	LIST_NODE *tmp = head->next;
	LIST_NODE *del = NULL;
	while (tmp)
	{
		del = tmp->next;
		free(tmp);
		tmp = del;        
	}

	free(head);
}

QUEUE* createQueue(int size)
{
	QUEUE *obj = malloc(sizeof(QUEUE));
	obj->size = size;
	obj->cur = 0;
	obj->front = 0;
	obj->rear = -1;
	obj->data = malloc(sizeof(POST_DATA)*size);
	return obj;
}

void destroyQueue(QUEUE *obj)
{
	free(obj->data);
	free(obj);
}

bool isEmpty(QUEUE *obj)
{
	return (obj->cur == 0 ? true : false);
}

bool isFull(QUEUE *obj)
{
	return (obj->cur == obj->size ? true : false);
}

void fillQueueData(QUEUE *obj, POST_DATA *ret, int *retCtr)
{
	int ctr = 0;
	while (ctr < obj->cur)
	{
		ret[*retCtr+ctr].pId = obj->data[(obj->front + ctr) % obj->size].pId;
		ret[*retCtr+ctr].pTime = obj->data[(obj->front + ctr) % obj->size].pTime;        
		ctr++;
	}
	*retCtr += obj->cur;
}

void addQueue(QUEUE *obj, int id, int time)
{
	obj->rear = (obj->rear+1) % obj->size;
	obj->data[obj->rear].pId = id;
	obj->data[obj->rear].pTime = time;
	obj->cur++;
}

int getSizeQueue(QUEUE *obj)
{
	return obj->cur;
}

void delQueue(QUEUE *obj)
{    
	obj->front = (obj->front+1) % obj->size;
	obj->cur--;    
}

Twitter* twitterCreate() 
{
	Twitter *obj = calloc(1, sizeof(Twitter));
	for (int i = 0; i < DEF_USERS; i++)
	{
		obj->u[i].postQ = createQueue(MAX_POST);
		obj->u[i].headF = calloc(1, sizeof(LIST_NODE));
	}
	return obj;
}

/** Compose a new tweet. */
void twitterPostTweet(Twitter* obj, int userId, int tweetId) 
{
	if (isFull(obj->u[userId].postQ))
	{
		delQueue(obj->u[userId].postQ);
	}
	obj->time += 1;    
	addQueue(obj->u[userId].postQ, tweetId, obj->time);        
}

int compare(const void *a, const void *b)
{
	POST_DATA n1 = *(POST_DATA *)a;
	POST_DATA n2 = *(POST_DATA *)b;
	return n2.pTime - n1.pTime;
}

/** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
int* twitterGetNewsFeed(Twitter* obj, int userId, int* retSize) 
{
	int *res = malloc(sizeof(int)*10);
	POST_DATA *ret = malloc(sizeof(POST_DATA)*1000);
	int retCtr = 0;

	fillQueueData(obj->u[userId].postQ, ret, &retCtr);    
	LIST_NODE *cur = obj->u[userId].headF->next;
	while (cur)
	{
		int curId = cur->uId;
		fillQueueData(obj->u[curId].postQ, ret, &retCtr);
		cur = cur->next;
	}

	int update = 0;
	while (update < retCtr && update < 10)
	{
		int resIdx = 0;
		for (int x = 1; x < retCtr; x++)
		{            
			resIdx = (ret[x].pTime > ret[resIdx].pTime ? x : resIdx);            
		}        
		res[update] = ret[resIdx].pId;
		ret[resIdx].pTime = 0;
		update++;
	}
	*retSize = update;    
	return res;
}

/** Follower follows a followee. If the operation is invalid, it should be a no-op. */
void twitterFollow(Twitter* obj, int followerId, int followeeId) 
{
	if (followerId == followeeId || checkNodeExist(obj->u[followerId].headF, followeeId))
	{
		return;
	}

	addNode(obj->u[followerId].headF, followeeId);
}

/** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
void twitterUnfollow(Twitter* obj, int followerId, int followeeId) 
{
	delNode(obj->u[followerId].headF, followeeId);
}

void twitterFree(Twitter* obj) 
{
	for (int i = 0; i < DEF_USERS; i++)
	{
		destroyQueue(obj->u[i].postQ);
		freeNode(obj->u[i].headF);
	}    
	free(obj);
}

/**
 * Your Twitter struct will be instantiated and called as such:
 * Twitter* obj = twitterCreate();
 * twitterPostTweet(obj, userId, tweetId);

 * int* param_2 = twitterGetNewsFeed(obj, userId, retSize);

 * twitterFollow(obj, followerId, followeeId);

 * twitterUnfollow(obj, followerId, followeeId);

 * twitterFree(obj);
 */
