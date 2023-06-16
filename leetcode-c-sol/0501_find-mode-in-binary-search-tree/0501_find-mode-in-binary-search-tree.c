void updateMax(int **ret, int *returnSize, int *ctr, int *max, int val)
{
	if (*ctr < *max)
	{
		return;
	} else if (*ctr == *max)
	{
		*returnSize += 1;
	} else // *ctr > *max
	{
		*max = *ctr;
		*returnSize = 1;
	}
	*ret = realloc(*ret, sizeof(int)*(*returnSize));
	(*ret)[*returnSize - 1] = val;
}

void findModeHelper(struct TreeNode* root, int **ret, int *returnSize, int *isFirst, int *pre, int *ctr, int *max)
{
	if (!root)
	{
		return;
	}

	findModeHelper(root->left, ret, returnSize, isFirst, pre, ctr, max);

	do {
		if (*isFirst)
		{
			*isFirst = 0;
			break;
		}

		if (root->val != *pre)
		{        
			*ctr = 1;
		} else    
		{
			*ctr += 1;
		}
	} while (0);
	updateMax(ret, returnSize, ctr, max, root->val); 
	*pre = root->val;

	findModeHelper(root->right, ret, returnSize, isFirst, pre, ctr, max);
}

int* findMode(struct TreeNode* root, int* returnSize)
{   
	int *ret = malloc(sizeof(int));
	*returnSize = 0;
	if (!root)
	{
		return ret;
	}

	int dupCtr = 1, max = 0;
	int isFirst = 1, pre = 0;
	findModeHelper(root, &ret, returnSize, &isFirst, &pre, &dupCtr, &max);
	return ret;
}

