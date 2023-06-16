struct TreeNode* 
countExclude(struct TreeNode *root, int x, int *ctr)
{
	if (NULL == root)
	{
		return NULL;
	}

	if (x == root->val)
	{        
		return root;
	}

	*ctr += 1;

	struct TreeNode *lRet = countExclude(root->left, x, ctr);
	struct TreeNode *rRet = countExclude(root->right, x, ctr);    

	return (lRet != NULL ? lRet : rRet);
}

int countChilds(struct TreeNode *root)
{
	if (NULL == root)
	{
		return 0;
	}

	return (1 + countChilds(root->left) + countChilds(root->right));
}


bool btreeGameWinningMove(struct TreeNode* root, int n, int x)
{
	struct TreeNode *target;
	int ctrParent = 0, ctrLeftChd = 0, ctrRightChd = 0;
	target = countExclude(root, x, &ctrParent);

	ctrLeftChd = countChilds(target->left);
	ctrRightChd = countChilds(target->right);

	int max = ctrParent;    
	max = (max > ctrLeftChd ? max : ctrLeftChd);
	max = (max > ctrRightChd ? max : ctrRightChd);

	return (ctrParent+ctrLeftChd+ctrRightChd - max < max ? true : false);
}

