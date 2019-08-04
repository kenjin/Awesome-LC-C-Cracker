/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int countNode(struct TreeNode* root) 
{
	if (root == NULL)
	{
		return 0;
	}

	return countNode(root->left) + countNode(root->right) + 1;        
}

void serializeHelper(struct TreeNode* root, char *ret, int idx)
{
	if (root == NULL)
	{
		return;
	}

	char str[12] = {0};


	sprintf(str, "%d", root->val);
	strcat(ret, str);
	strcat(ret, "[");
	serializeHelper(root->left, ret, idx);    
	strcat(ret, "][");
	serializeHelper(root->right, ret, idx);
	strcat(ret, "]");
}

/** Encodes a tree to a single string. */
char* serialize(struct TreeNode* root) 
{
	int totalNodes = countNode(root);
	if (totalNodes == 0)
	{
		return NULL;
	}

	char *ret = calloc(totalNodes*18 , sizeof(char));

	strcat(ret, "[");
	serializeHelper(root, ret, 1);
	strcat(ret, "]");
	return ret;
}

struct TreeNode* deserializeHelper(char *data, int *idx, int len)
{       
	int chkIdx = -1;
	int i;
	for (i = *idx; i < len; i++)
	{
		if (data[i] == '[')
		{
			if (-1 == chkIdx)
			{
				chkIdx = i+1;         
			} else
			{
				break;
			}
		} else if (data[i] == ']')
		{
			*idx = i;
			return NULL;
		}        
	}

	struct TreeNode* root = malloc(sizeof(struct TreeNode));
	data[i] = 0;            
	root->val = atoi(&(data[chkIdx]));
	*idx = i;
	data[i] = '[';

	root->left = deserializeHelper(data, idx, len);
	while (data[*idx] == ']' && *idx < len)
	{
		*idx += 1;
	}
	root->right = deserializeHelper(data, idx, len);

	while (data[*idx] == ']' && *idx < len)
	{
		*idx += 1;
	}
	return root;
}

/** Decodes your encoded data to tree. */
struct TreeNode* deserialize(char* data) 
{
	if (data == NULL)
	{
		return NULL;
	}
	int len = strlen(data);

	int idx = 0;
	struct TreeNode* root = deserializeHelper(data, &idx, len);
	return root;
}

// Your functions will be called as such:
// char* data = serialize(root);
// deserialize(data);
