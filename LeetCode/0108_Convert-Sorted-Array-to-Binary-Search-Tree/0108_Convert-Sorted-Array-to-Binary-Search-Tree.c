/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct TreeNode* createBST(int *nums, int head, int tail)
{
	if (head < 0 || head > tail)
	{
		return NULL;
	}
	int mid = head + (tail-head)/2;
	struct TreeNode* newNode = malloc(sizeof(struct TreeNode));
	newNode->val = nums[mid];
	newNode->left  = createBST(nums, head, mid-1);
	newNode->right = createBST(nums, mid+1, tail);
	return newNode;    
}

struct TreeNode* sortedArrayToBST(int* nums, int numsSize)
{
	return createBST(nums, 0, numsSize-1);
}

