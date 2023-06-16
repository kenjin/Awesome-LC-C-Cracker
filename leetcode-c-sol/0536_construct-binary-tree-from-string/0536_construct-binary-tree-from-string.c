typedef struct TreeNode NODE;
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int checkParen(char *s, int *idx /* current idx */, int len)
{
	int parenStart = -1;
	int parenCtr = 0;
	while (*idx < len)
	{
		if (s[*idx] == '(')
		{
			parenCtr++;
			if (parenCtr == 1)
			{
				parenStart = *idx;
			}
		} else if (s[*idx] == ')')
		{
			parenCtr--;
			if (parenCtr == 0)
			{
				s[*idx] = 0;
				return parenStart;
			}
		}
		*idx += 1;
	}

	return -1;
}

struct TreeNode* str2tree(char * s)
{
	int len = strlen(s);
	if (len == 0)
	{
		return NULL;
	}

	NODE *root = calloc(1, sizeof(NODE));
	// Get Value    
	int idx = 0, num = 0;
	bool negative = false;
	while (idx < len)
	{
		if (s[idx] == '-')
		{
			negative = true;
			idx++;
			continue;
		}
		if (s[idx] < '0' || s[idx] > '9')
		{
			break;
		}        
		num *= 10;
		num += s[idx]-'0';
		idx++;
	}
	root->val = (negative ? num*(-1) : num);

	// Check Left Part
	int parenIdx = checkParen(s, &idx, len);
	if (parenIdx != -1)
	{
		root->left = str2tree(&(s[parenIdx+1]));
		// Check Right Part
		parenIdx = checkParen(s, &idx, len);
		if (parenIdx != -1)
		{
			root->right = str2tree(&(s[parenIdx+1]));
		}
	}

	return root;
}

