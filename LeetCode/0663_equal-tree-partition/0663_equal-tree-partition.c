
int countSum(struct TreeNode *root)
{
	if (NULL == root)
	{
		return 0;
	}

	root->val += countSum(root->left) + countSum(root->right);
	return root->val;
}

bool partitionHelper(struct TreeNode *root, struct TreeNode *head, int sum)
{
	if (NULL == root)
	{
		return false;
	}

	bool lRet = partitionHelper(root->left, head, sum);
	if (true == lRet)
	{
		return true;
	}

	if (head != root && sum - root->val == root->val)
	{
		return true;
	} else
	{
		return partitionHelper(root->right, head, sum);
	}    
}

bool checkEqualTree(struct TreeNode* root)
{
	int sum = countSum(root);
	return partitionHelper(root, root, sum);    
}


