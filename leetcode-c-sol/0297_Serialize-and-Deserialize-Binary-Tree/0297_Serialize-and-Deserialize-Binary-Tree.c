/**

297. Serialize and Deserialize Binary Tree [Hard]

Ref: https://leetcode.com/problems/serialize-and-deserialize-binary-tree/
   
 */

#define STR_MALLOC_UNIT (500)

typedef struct queue
{
	int size;
	int curSize;
	int rear;
	int front;
	struct TreeNode **node;
} QUEUE;

QUEUE* createQueue(int size)
{
	QUEUE *obj = malloc(sizeof(QUEUE));
	obj->size = size;
	obj->curSize = 0;
	obj->rear =-1;
	obj->front = 0;
	obj->node = malloc(sizeof(struct TreeNode*)*size);
	return obj;
}

void freeQueue(QUEUE *obj)
{
	free(obj->node);
	free(obj);
}

bool isFull(QUEUE *obj)
{
	return (obj->curSize == obj->size ? true : false);
}

bool isEmpty(QUEUE *obj)
{
	return (obj->curSize == 0 ? true : false);
}

void enqueue(QUEUE *obj, struct TreeNode* newNode)
{
	if (isFull(obj))
	{
		return;
	}

	obj->rear = (obj->rear+1) % obj->size;
	obj->node[obj->rear] = newNode;
	obj->curSize++;
}

struct TreeNode* dequeue(QUEUE *obj)
{
	if (isEmpty(obj))
	{
		return NULL;
	}


	struct TreeNode *ret = obj->node[obj->front];
	obj->front = (obj->front+1) % obj->size;
	obj->curSize--;

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

int getNodeCount(struct TreeNode* root)
{
	if (root == NULL)
	{
		return 1;
	}
	return (getNodeCount(root->left) + getNodeCount(root->right) + 1);
}

char* addChar(char *s, char c, int *addCtr)
{
	/* Realloc when adding string size to the limit */
	if (*addCtr != 0 && (*addCtr % STR_MALLOC_UNIT) == 0)
	{
		s = realloc(s, sizeof(char)*(*addCtr+STR_MALLOC_UNIT));
	}
	s[*addCtr] = c;
	*addCtr += 1;

	return s;
}

void reverseString(char *ret, int start, int end)
{
	while (start < end)
	{
		char cTmp = ret[start];
		ret[start] = ret[end];
		ret[end] = cTmp;
		start++;
		end--;
	}   
}

/** Encodes a tree to a single string. */
char* serialize(struct TreeNode* root) 
{
	/* Empty Node */
	if (root == NULL)
	{
		return "";
	}

	int nodeCount = getNodeCount(root);
	char *ret = calloc(STR_MALLOC_UNIT, sizeof(char));
	int addCtr = 0;

	QUEUE *q = createQueue(nodeCount);
	enqueue(q, root);
	while (!isEmpty(q) && nodeCount > 0)
	{
		struct TreeNode* node = dequeue(q);
		/* Skip NULL node and no need to BFS */
		if (node == NULL)
		{
			ret = addChar(ret, 'X', &addCtr);
			nodeCount--;
			continue;
		}

		/* Ex: 999 (>1 digits) */
		if (node->val < 0)
		{
			ret = addChar(ret, '-', &addCtr);
			node->val *= -1;
		}
		int start = addCtr;
		do
		{
			ret = addChar(ret, (node->val % 10) + '0', &addCtr);
			node->val /= 10;
		} while (node->val > 0);

		/* Reverse num string (123 => 321) for easy-transfering later*/
		reverseString(ret, start, addCtr-1);     
		/* Add end point for each number */
		ret = addChar(ret, '.', &addCtr);
		nodeCount--;

		if (node->left == NULL)
		{
			enqueue(q, NULL);
		} else
		{
			enqueue(q, node->left);
		}
		if (node->right == NULL)
		{
			enqueue(q, NULL);
		} else
		{
			enqueue(q, node->right);
		}
	}

	ret = addChar(ret, NULL, &addCtr);
	freeQueue(q);
	return ret;
}

struct TreeNode* createNode(char *data, int *addCtr)
{
	if (data[*addCtr] == 'X' || data[*addCtr] == NULL)
	{
		*addCtr += 1;
		return NULL;
	} else 
	{
		int sum = 0;
		int sign = 1;
		if (data[*addCtr]  == '-')
		{
			sign = -1;
			*addCtr += 1;
		}
		while (data[*addCtr] != '.')
		{
			sum = sum*10 + (data[*addCtr]-'0');
			*addCtr += 1;            
		}
		sum *= sign;
		*addCtr += 1; /* Skip '.' */

		struct TreeNode* newNode = malloc(sizeof(struct TreeNode));
		newNode->val = sum;
		newNode->left = newNode->right = NULL;
		return newNode;
	}
}

/** Decodes your encoded data to tree. */
struct TreeNode* deserialize(char* data) 
{
	int dataLen = strlen(data);
	/* Empty String: "" */
	if (dataLen == 0)
	{
		return NULL;
	}

	int addCtr = 0;
	QUEUE *q = createQueue(dataLen);

	struct TreeNode* root = createNode(data, &addCtr);    
	enqueue(q, root);
	while (!isEmpty(q) && addCtr < dataLen)
	{
		struct TreeNode* node = dequeue(q);

		node->left = createNode(data, &addCtr);
		if (node->left != NULL)
		{
			enqueue(q, node->left);
		}

		node->right = createNode(data, &addCtr);
		if (node->right != NULL)
		{
			enqueue(q, node->right);
		}
	}

	freeQueue(q);
	return root;
}

// Your functions will be called as such:
// char* data = serialize(root);
// deserialize(data);
