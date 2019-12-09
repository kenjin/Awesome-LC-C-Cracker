typedef struct
{
	int val;
	int x;
	int y;
} NODE_INFO;

void traverse(struct TreeNode* root, int x, int y, NODE_INFO *n, int *nCtr)
{
	if (root == NULL)
	{
		return;
	}

	traverse(root->left, x-1, y-1, n, nCtr);    
	n[*nCtr].val = root->val;
	n[*nCtr].x = x;
	n[*nCtr].y = y;
	*nCtr += 1;
	traverse(root->right, x+1, y-1, n, nCtr);
}

int countNodes(struct TreeNode* root)
{
	if (root == NULL)
	{
		return 0;
	}

	return countNodes(root->left)+countNodes(root->right)+1;
}

int compare(const void *a, const void *b)
{
	NODE_INFO n1 = *(NODE_INFO *)a;
	NODE_INFO n2 = *(NODE_INFO *)b;

	if (n1.x == n2.x)
	{
		return n2.y - n1.y;
	} else
	{
		return n1.x - n2.x;
	}
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** verticalOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes)
{
	if (root == NULL)
	{
		*returnSize = 0;
		return NULL;
	}

	int nodes = countNodes(root);
	NODE_INFO *n = malloc(sizeof(NODE_INFO)*nodes);
	int nCtr = 0;
	traverse(root, 0, 0, n, &nCtr);

	qsort(n, nCtr, sizeof(NODE_INFO), compare);

	int **ret = malloc(sizeof(int *)*nodes);
	for (int i = 0; i < nodes; i++)
	{
		// overtake
		ret[i] = malloc(sizeof(int)*nodes);
	}
	*returnColumnSizes = calloc(nodes, sizeof(int));    
	ret[0][0] = n[0].val;
	*returnSize = 1;
	(*returnColumnSizes)[0] = 1;
	for (int i = 1; i < nodes; i++)
	{
		if (n[i].x == n[i-1].x)
		{
			ret[*returnSize - 1][(*returnColumnSizes)[*returnSize - 1]] = n[i].val;
			(*returnColumnSizes)[*returnSize - 1] += 1;            
		} else
		{
			*returnSize += 1;
			ret[*returnSize - 1][0] = n[i].val;
			(*returnColumnSizes)[*returnSize - 1] = 1;
		}
	}

	free(n);
	return ret;
}


