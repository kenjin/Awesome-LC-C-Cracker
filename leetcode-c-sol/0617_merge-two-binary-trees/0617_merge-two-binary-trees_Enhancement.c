typedef struct TreeNode NODE;

struct TreeNode* mergeTrees(struct TreeNode* t1, struct TreeNode* t2)
{
	if (t1 == NULL)
	{
		return t2;
	} else if (t1 != NULL && t2 == NULL)
	{
		return t1;
	} else
	{
		t1->val += t2->val;
		t1->left = mergeTrees(t1->left, t2->left);
		t1->right = mergeTrees(t1->right, t2->right);
		return t1;
	}
}

