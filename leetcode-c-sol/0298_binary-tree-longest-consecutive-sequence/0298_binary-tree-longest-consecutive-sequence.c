typedef struct
{
	struct TreeNode *node;
	int ctr;
} DATA;

typedef struct queueInfo
{
	int size;
	int cur;
	int front;
	int rear;
	DATA *d;
} QUEUE;

QUEUE* createQueue(int size)
{
	QUEUE *obj = malloc(sizeof(QUEUE));
	obj->size = size;
	obj->cur = 0;
	obj->front = 0;
	obj->rear = -1;
	obj->d = malloc(sizeof(DATA)*size);    
	return obj;
}

void destroyQueue(QUEUE *obj)
{
	free(obj->d);
	free(obj);
}

bool isEmpty(QUEUE *obj)
{
	return (obj->cur == 0);
}

void addQueue(QUEUE *obj, struct TreeNode *n, int consecutiveCtr)
{
	obj->rear = (obj->rear+1) % obj->size;
	obj->d[obj->rear].node = n;
	obj->d[obj->rear].ctr = consecutiveCtr;
	obj->cur++;
}

DATA delQueue(QUEUE *obj)
{
	DATA ret = obj->d[obj->front];
	obj->front = (obj->front+1) % obj->size;
	obj->cur--;    
	return ret;
}

int countTree(struct TreeNode* root)
{
	if (NULL == root)
	{
		return 0;
	}
	return (1 + countTree(root->left) + countTree(root->right));
}

int checkConsecutive(struct TreeNode *child, int curVal, int consecutive)
{
	if (NULL == child)
	{
		return 0;
	}

	return (child->val - 1 == curVal) ? consecutive+1 : 1;
}

int longestConsecutive(struct TreeNode* root)
{
	if (NULL == root)
	{
		return 0;
	}

	QUEUE *q = createQueue(countTree(root));
	int max = 0;    
	addQueue(q, root, 1);
	while (!isEmpty(q))
	{
		DATA d = delQueue(q);                
		int addCtr;
		if (0 != (addCtr = checkConsecutive(d.node->left, d.node->val, d.ctr)))
		{
			addQueue(q, d.node->left, addCtr);
		}
		if (0 != (addCtr = checkConsecutive(d.node->right, d.node->val, d.ctr)))
		{
			addQueue(q, d.node->right, addCtr);
		}

		max = (max > d.ctr ? max : d.ctr);
	}

	destroyQueue(q);    
	return max;
}


