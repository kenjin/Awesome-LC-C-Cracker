typedef struct
{
	int pId;
	struct TreeNode *n;
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

void addQueue(QUEUE *obj, struct TreeNode *n, int pId)
{
	obj->rear = (obj->rear+1) % obj->size;
	obj->d[obj->rear].n = n;
	obj->d[obj->rear].pId = pId;
	obj->cur++;
}

DATA delQueue(QUEUE *obj)
{
	DATA ret = obj->d[obj->front];
	obj->front = (obj->front+1) % obj->size;
	obj->cur--;    
	return ret;
}

int countNodes(struct TreeNode* root)
{
	if (NULL == root)
	{
		return 0;
	}

	return 1 + countNodes(root->left) + countNodes(root->right);
}

typedef struct nodeInfo
{
	int val;
	int chd;
	int pId;
} NODE;
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** findLeaves(struct TreeNode* root, int* returnSize, int** returnColumnSizes)
{
	int counts = countNodes(root);
	if (counts == 0)
	{
		*returnSize = 0;
		return NULL;
	}

	int *chk = malloc(sizeof(int)*counts);
	int chkCtr = 0;

	NODE *n = calloc(counts, sizeof(NODE));
	int nCtr = 0, p = -1;
	QUEUE *q = createQueue(counts);    
	addQueue(q, root, -1);
	while (!isEmpty(q))
	{
		DATA deleteRet = delQueue(q);
		struct TreeNode *tmp = deleteRet.n;
		int p = deleteRet.pId;
		n[nCtr].val = tmp->val;
		if (tmp->left)
		{
			n[nCtr].chd += 1;
			addQueue(q, tmp->left, nCtr);
		}
		if (tmp->right)
		{
			n[nCtr].chd += 1;
			addQueue(q, tmp->right, nCtr);
		}
		n[nCtr].pId = p;

		if (0 == n[nCtr].chd)
		{
			chk[chkCtr] = nCtr;
			chkCtr++;
		}
		nCtr ++;
	}

	int **ret = malloc(sizeof(int *));
	*returnColumnSizes = malloc(sizeof(int));
	*returnSize = 0;

	int findRoot = 0;
	while (!findRoot)
	{
		int maxCtr = chkCtr;
		ret = realloc(ret, sizeof(int *)*(*returnSize + 1));
		*returnColumnSizes = realloc(*returnColumnSizes, sizeof(int)*(*returnSize + 1));
		ret[*returnSize] = malloc(sizeof(int)*chkCtr);
		(*returnColumnSizes)[*returnSize] = chkCtr;
		// Reset
		chkCtr = 0;
		for (int i = 0; i < maxCtr; i++)
		{
			ret[*returnSize][i] = n[chk[i]].val;
			if (-1 == n[chk[i]].pId) // Final root node
			{
				findRoot = 1;
				break;
			}

			n[n[chk[i]].pId].chd --;
			if (0 == n[n[chk[i]].pId].chd)
			{
				chk[chkCtr] = n[chk[i]].pId;
				chkCtr++;
			}
		}
		*returnSize += 1;
	}

	free(chk);
	free(n);
	destroyQueue(q);
	return ret;
}


