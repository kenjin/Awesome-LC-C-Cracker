#define MAX(a, b) (a > b ? a : b);

int largestBSTSubtreeHelper(struct TreeNode* root, int *max, int *min, int *ret)
{
	// leaf node
	if (!root->left && !root->right)
	{
		*max = root->val;
		*min = root->val;        
		*ret = (*ret == 0) ? 1 : *ret;
		return 1;
	}

	int tmpMin, tmpMax, lRet = 0, rRet = 0;
	if (root->left)
	{
		lRet = largestBSTSubtreeHelper(root->left, max, min, ret);
		tmpMin = *min;
		tmpMax = *max;     
	}

	if (root->right)
	{
		rRet = largestBSTSubtreeHelper(root->right, max, min, ret);
		if (rRet == 0 || *min <= root->val)
		{
			return 0;
		}        
	}

	if ((root->left) && 
			(lRet == 0 || tmpMax >= root->val))
	{
		return 0;
	}

	*min = (root->left) ? tmpMin : root->val;    
	*max = (root->right) ? *max : root->val;
	// Update Sub-BST result
	int tmpRet = lRet + rRet + 1;
	*ret = MAX(*ret, tmpRet);
	return tmpRet;
}

int largestBSTSubtree(struct TreeNode* root)
{
	if (NULL == root)
	{
		return 0;
	}

	int min, max;
	int ret = 0;
	largestBSTSubtreeHelper(root, &max, &min, &ret);

	return ret;
}

