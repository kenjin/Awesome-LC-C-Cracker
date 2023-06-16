typedef struct
{
	struct TreeNode *n;
	int lv;
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

void addQueue(QUEUE *obj, struct TreeNode *node, int lv)
{
	obj->rear = (obj->rear+1) % obj->size;
	obj->data[obj->rear].n = node;
	obj->data[obj->rear].lv = lv;
	obj->cur++;
}

DATA delQueue(QUEUE *obj)
{
	DATA ret = obj->data[obj->front];
	obj->front = (obj->front+1) % obj->size;
	obj->cur--;
	return ret;
}

int getTreeInfo(struct TreeNode* root, int lv, int *nodeCtr)
{
	if (NULL == root)
	{
		return 0;
	}
	*nodeCtr += 1;
	int l = getTreeInfo(root->left, lv+1, nodeCtr);
	int r = getTreeInfo(root->right, lv+1, nodeCtr);
	return (l > r ? l : r) + 1;
}


double* averageOfLevels(struct TreeNode* root, int* returnSize)
{
	int nodeCtr = 0;
	int h = getTreeInfo(root, 0, &nodeCtr);
	double *ret = malloc(sizeof(double)*h);
	*returnSize = h;

	QUEUE *q = createQueue(nodeCtr);
	int preLv = -1, tmpCtr = 1;
	double tmpSum = root->val;
	addQueue(q, root, 0);    
	while (!isEmpty(q))
	{
		DATA tmp = delQueue(q);
		struct TreeNode *cur = tmp.n;
		if (preLv != tmp.lv)
		{
			if (preLv >= 0)
			{
				ret[preLv] = tmpSum/tmpCtr;
			}
			tmpSum = cur->val;
			tmpCtr = 1;

		} else
		{
			tmpSum += cur->val;
			tmpCtr += 1;
		}

		if (cur->left)
		{
			addQueue(q, cur->left, tmp.lv+1);    
		}
		if (cur->right)
		{
			addQueue(q, cur->right, tmp.lv+1);    
		}

		preLv = tmp.lv;
	}

	ret[h-1] = tmpSum/tmpCtr;
	destroyQueue(q);
	return ret;
}


