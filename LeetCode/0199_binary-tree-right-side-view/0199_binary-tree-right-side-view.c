typedef struct
{
	int size;
	int cur;
	struct TreeNode **ptr;
} STACK;

STACK* stackCreate(int size) 
{
	STACK *obj = malloc(sizeof(STACK));
	obj->size = size;
	obj->cur = -1;
	obj->ptr = malloc(sizeof(struct TreeNode *)*size);
	return obj;
}

bool stackIsEmpty(STACK *obj)
{
	return (obj->cur == -1 ? true : false);
}

void stackPush(STACK* obj, struct TreeNode *p)
{
	obj->cur += 1;
	obj->ptr[obj->cur] = p;
}

struct TreeNode * stackPop(STACK* obj)
{
	if (stackIsEmpty(obj))
	{
		printf("WARNING: empty stack!\n");
		return NULL;
	}

	obj->cur -= 1;
	return obj->ptr[obj->cur+1];
}

void stackFree(STACK* obj) 
{
	free(obj->ptr);
	free(obj);
}

int countNode(struct TreeNode* root)
{
	if (root == NULL)
	{
		return 0;
	}
	return countNode(root->left) + countNode(root->right) + 1;
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* rightSideView(struct TreeNode* root, int* returnSize)
{
	if (root == NULL)
	{
		*returnSize = 0;
		return NULL;
	}

	int nodes = countNode(root);
	STACK *s1 = stackCreate(nodes);
	STACK *s2 = stackCreate(nodes);
	stackPush(s1, root);

	int *ret = malloc(sizeof(int)*nodes);
	int retCtr = 0;
	struct TreeNode *tmp;
	while (1)
	{              
		// no child
		if (stackIsEmpty(s1))
		{
			break;
		}

		char isFirst = 1;  
		while (!stackIsEmpty(s1))
		{
			tmp = stackPop(s1);
			if (isFirst)
			{
				ret[retCtr] = tmp->val;
				retCtr++;
				isFirst = 0;
			}
			stackPush(s2, tmp);
		}
		isFirst = 1;

		while (!stackIsEmpty(s2))
		{
			tmp = stackPop(s2);
			if (NULL != tmp->left)
			{
				stackPush(s1, tmp->left);
			}
			if (NULL != tmp->right)
			{
				stackPush(s1, tmp->right);
			}
		}
	}

	stackFree(s1);
	stackFree(s2);

	*returnSize = retCtr;
	return ret;
}

