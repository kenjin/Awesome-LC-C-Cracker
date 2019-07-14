int maxPathSumHelper(struct TreeNode* root, int *max)
{
	if (root == NULL)
	{
		return 0;
	}
	int lMax = INT_MIN, rMax = INT_MIN;
	int lSubMaxLen = maxPathSumHelper(root->left, &lMax);
	int rSubMaxLen = maxPathSumHelper(root->right, &rMax);    

	// count the sub-tree maxPathSum 
	int tmpMax = root->val;
	if (lSubMaxLen > 0)
	{
		tmpMax += lSubMaxLen;
	}
	if (rSubMaxLen > 0)
	{
		tmpMax += rSubMaxLen;
	}

	if (lMax > tmpMax)
	{
		tmpMax = lMax;
	}
	if (rMax > tmpMax)
	{
		tmpMax = rMax;
	}
	*max = tmpMax;

	// return the max path (root, root+left-path, root+right-path)
	int tmpRet = root->val;
	if (lSubMaxLen < 0 && rSubMaxLen < 0)
	{
		return tmpRet;
	} else
	{
		return lSubMaxLen > rSubMaxLen ? (lSubMaxLen + root->val) : (rSubMaxLen + root->val);
	}
}

int maxPathSum(struct TreeNode* root)
{
	int max = 0;
	maxPathSumHelper(root, &max);    
	return max;
}

