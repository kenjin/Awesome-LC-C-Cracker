/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

typedef struct listNode
{    
	struct listNode* head;
	struct TreeNode* node;
	struct listNode* next;
} LIST;

void pathSumHelper(struct TreeNode* root, LIST *l, int sum, int target, int *ret)
{
	if (NULL == root)
	{
		return 0;
	}

	// create new list node
	LIST *newList = calloc(1, sizeof(LIST));
	newList->head = l->head;
	l->node = root;
	l->next = newList;    
	sum += root->val;

	// check all posible sum
	struct listNode* rList = l->head;
	int tmpSum = sum;
	while (NULL != rList->next)
	{
		if (tmpSum == target)
		{
			*ret += 1;
		}
		tmpSum -= rList->node->val; 
		rList = rList->next;        
	}

	pathSumHelper(root->left , l->next, sum, target, ret);
	pathSumHelper(root->right, l->next, sum, target, ret);

	// free new list node
	free(newList);
}

int pathSum(struct TreeNode* root, int sum)
{
	int ret = 0;
	int curSum = 0;
	LIST *l = calloc(1, sizeof(LIST));
	l->head = l;

	pathSumHelper(root, l, 0, sum, &ret);

	free(l);
	return ret;
}


