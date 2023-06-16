typedef struct qData
{
	struct TreeNode *node;
	int sum;
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

void addQueue(QUEUE *obj, struct TreeNode *root, int sum)
{
	if (isFull(obj))
	{
		return;
	}
	obj->rear = (obj->rear+1) % obj->size;
	obj->data[obj->rear].node = root;
	obj->data[obj->rear].sum = sum;
	obj->cur++;
}

int getSizeQueue(QUEUE *obj)
{
	return obj->cur;
}

DATA delQueue(QUEUE *obj)
{
	DATA ret = obj->data[obj->front];
	obj->front = (obj->front+1) % obj->size;
	obj->cur--;
	return ret;
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int sumRootToLeaf(struct TreeNode* root)
{
	QUEUE *q = createQueue(1000);

	int ret = 0;
	addQueue(q, root, root->val);
	while (!isEmpty(q))
	{
		int curSize = getSizeQueue(q);
		for (int i = 0; i < curSize; i++)
		{
			DATA d = delQueue(q);
			if (d.node->left == NULL && d.node->right == NULL)
			{
				ret += d.sum;
			} else
			{
				if (d.node->left)
				{
					addQueue(q, d.node->left, (d.sum)*2 + d.node->left->val);
				}
				if (d.node->right)
				{
					addQueue(q, d.node->right, (d.sum)*2 + d.node->right->val);
				}
			}
		}
	}

	delQueue(q);
	return ret;    
}


