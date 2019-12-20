#define MAX(a, b) (a > b ? a : b)
typedef struct
{
	int inc;
	int dec;
} DATA;

DATA createData(int inc, int dec)
{
	DATA d;
	d.inc = inc;
	d.dec = dec;
	return d;
}
DATA traverseHelper(struct TreeNode* root, int *max)
{
	DATA cur = createData(0, 0);
	if (NULL == root)
	{

		return cur;
	}

	cur.inc = 1;
	cur.dec = 1;
	if (root->left)
	{
		DATA lRet = traverseHelper(root->left, max);        
		if (root->val+1 == root->left->val)
		{
			cur.inc = lRet.inc + 1;
		}

		if (root->val-1 == root->left->val)
		{
			cur.dec = lRet.dec + 1;
		}
	}

	if (root->right)
	{
		DATA rRet = traverseHelper(root->right, max);
		if (root->val+1 == root->right->val)
		{
			cur.inc = MAX(cur.inc, rRet.inc + 1);
		}
		if (root->val-1 == root->right->val)
		{
			cur.dec = MAX(cur.dec, rRet.dec + 1);
		}        
	}

	*max = MAX(*max, cur.inc+cur.dec-1);
	return cur;
}

int longestConsecutive(struct TreeNode* root)
{
	int max = 0;    
	traverseHelper(root, &max);
	return max;
}

