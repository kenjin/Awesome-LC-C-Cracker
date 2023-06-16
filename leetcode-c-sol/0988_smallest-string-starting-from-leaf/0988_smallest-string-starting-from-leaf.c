/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

void reverseStr(char *s, int head, int tail)
{
	while (head < tail)
	{
		char tmp = s[head];
		s[head] = s[tail];
		s[tail] = tmp;
		head++;
		tail--;
	}
}

void smallestFromLeafHelper(struct TreeNode* root, char *ret, char *tmp, int tmpCtr)
{
	if (root == NULL)
	{
		return;
	}

	tmp[tmpCtr] = root->val +'a';
	if (root->left == NULL && root->right == NULL)
	{
		tmp[tmpCtr+1] = 0;
		reverseStr(tmp, 0, tmpCtr);
		if (*ret == 0 || strcmp(tmp, ret) < 0)
		{
			strcpy(ret, tmp);
		}
		reverseStr(tmp, 0, tmpCtr);
	}

	smallestFromLeafHelper(root->left, ret, tmp, tmpCtr+1);
	smallestFromLeafHelper(root->right, ret, tmp, tmpCtr+1);
}

char * smallestFromLeaf(struct TreeNode* root)
{
	char *ret = calloc(8501, sizeof(char));
	char *tmp = calloc(8501, sizeof(char));
	int tmpCtr = 0;

	smallestFromLeafHelper(root, ret, tmp, 0);

	free(tmp);
	return ret;
}

