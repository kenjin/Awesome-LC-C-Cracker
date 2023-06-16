/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

typedef struct TreeNode NODE;
#define MAX(a, b)   (a > b ? a : b)

typedef struct
{
	int lv;
	NODE *n;
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

void addQueue(QUEUE *obj, struct TreeNode *root, int lv)
{
	if (isFull(obj))
	{
		return;
	}
	obj->rear = (obj->rear+1) % obj->size;
	obj->data[obj->rear].n = root;
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

int getTreeHeightAndNodes(NODE *root, int *ctr)
{
	if (NULL == root)
	{
		return 0;
	}

	*ctr += 1;

	int retL = getTreeHeightAndNodes(root->left, ctr);
	int retR = getTreeHeightAndNodes(root->right, ctr);
	return MAX(retL, retR) + 1;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* largestValues(struct TreeNode* root, int* returnSize)
{
	if (NULL == root)
	{
		*returnSize = 0;
		return NULL;
	}

	int nodeCtr = 0;
	int treeHeight = getTreeHeightAndNodes(root, &nodeCtr);
	int maxCtr = (int)pow(2, treeHeight);

	*returnSize = treeHeight;
	int *ret = calloc(treeHeight, sizeof(int)); 

	for (int i = 0; i < treeHeight; i++)
	{
		ret[i] = INT_MIN;
	}

	QUEUE *q = createQueue(nodeCtr+1);
	addQueue(q, root, 0);
	while (!isEmpty(q))
	{
		DATA tmp = delQueue(q);
		ret[tmp.lv] = MAX(ret[tmp.lv], tmp.n->val);
		if (tmp.n->left)
		{
			addQueue(q, tmp.n->left, tmp.lv+1);
		}
		if (tmp.n->right)
		{
			addQueue(q, tmp.n->right, tmp.lv+1);
		}
	}

	delQueue(q);       
	return ret;
}

