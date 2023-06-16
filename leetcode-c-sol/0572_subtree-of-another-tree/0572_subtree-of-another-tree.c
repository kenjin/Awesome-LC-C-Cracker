/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

bool isSubtreeHelper(struct TreeNode* s, struct TreeNode* t, int *first)
{
	if (NULL == s || NULL == t)
	{
		return (NULL == s && NULL == t) ? true : false;
	}

	bool leftRet, rightRet;
	if (s->val == t->val)
	{
		if (*first == 0)
		{
			*first = 1;
		}

		leftRet = isSubtreeHelper(s->left, t->left, first);
		rightRet = isSubtreeHelper(s->right, t->right, first);
		if (leftRet & rightRet)
		{
			return true;
		}
		*first = 0;
	}

	// if current s and t is not equal but we have found prev node is equal 
	// => not continuous equal (not a correct sub-tree)
	if (*first)
	{
		return false;
	}

	// Re-start to find t again
	leftRet = isSubtreeHelper(s->left, t, first);
	if (leftRet)
	{
		return true;
	}
	return isSubtreeHelper(s->right, t, first);
}

bool isSubtree(struct TreeNode* s, struct TreeNode* t)
{
	int first = 0;
	return isSubtreeHelper(s, t, &first);
}

