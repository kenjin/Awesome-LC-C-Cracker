
int getVoyagaPosition(int *record, struct TreeNode *root)
{
	if (NULL == root)
	{
		return -1;
	}
	return record[root->val];
}

bool flipBT(struct TreeNode *root, int *record, int *ret, int *retSize, int *tmp, int *tmpCtr)
{
	if (NULL == root)
	{
		return true;
	}

	// preorder travrsal
	tmp[*tmpCtr] = root->val;
	*tmpCtr += 1;

	int rootPos = getVoyagaPosition(record, root);
	int lPos = getVoyagaPosition(record, root->left);
	int rPos = getVoyagaPosition(record, root->right);
	if (-1 != lPos && -1 != rPos)
	{
		// No chance to flip
		if (rootPos > lPos && rootPos > rPos)
		{
			return false;
		}
		// Flip
		if (rPos < lPos)
		{
			ret[*retSize] = root->val;
			*retSize += 1;

			struct TreeNode *flipNode = root->left;
			root->left = root->right;
			root->right = flipNode;
		}

	} else if (-1 == lPos && -1 == rPos)
	{
		return true;
	} else if ((-1 == lPos && rPos < rootPos) ||
			(-1 == rPos && lPos < rootPos))
	{
		return false;
	} 

	if (!flipBT(root->left, record, ret, retSize, tmp , tmpCtr))
	{
		return false;
	}

	return flipBT(root->right, record, ret, retSize, tmp , tmpCtr);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* flipMatchVoyage(struct TreeNode* root, int* voyage, int voyageSize, int* returnSize)
{
	int *tmp = calloc(voyageSize, sizeof(int));
	int tmpCtr = 0;
	int *ret = malloc(sizeof(int)*voyageSize);
	*returnSize = 0;
	int *record = malloc(sizeof(int)*(voyageSize+1));

	for (int i = 0; i < voyageSize; i++)
	{
		record[voyage[i]] = i;
	}

	if (!flipBT(root, record, ret, returnSize, tmp, &tmpCtr))
	{
		*returnSize = 1;
		ret[0] = -1;
	}

	for (int x = 0; x < voyageSize; x++)
	{
		if (tmp[x] != voyage[x])
		{
			*returnSize = 1;
			ret[0] = -1;
			break;
		}
	}

	return ret;
}

