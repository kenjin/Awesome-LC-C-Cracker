/**

  110. Balanced Binary Tree [Easy]

  Given a binary tree, determine if it is height-balanced.

  For this problem, a height-balanced binary tree is defined as:

  a binary tree in which the depth of the two subtrees of every node never differ by more than 1.

  Example 1:

  Given the following tree [3,9,20,null,null,15,7]:

      3
     / \
    9  20
   /  \
  15   7
  Return true.

  Example 2:

  Given the following tree [1,2,2,3,3,null,null,4,4]:

        1
       / \
      2   2
     / \
    3   3
   / \
  4   4
  Return false.

 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

bool checkBalance(struct TreeNode* root, int *height)
{
	if (root == NULL)
	{
		return true;
	}
	*height += 1;

	int leftH  = *height;
	int rightH = *height;
	if (checkBalance(root->left, &leftH) && checkBalance(root->right, &rightH))
	{
		*height = (leftH > rightH ? leftH : rightH);
		/* check height-balanced */
		if (abs(leftH - rightH) <= 1)
		{
			return true;
		}
	}    
	return false;    
}

bool isBalanced(struct TreeNode* root)
{
	int height = 0;
	return checkBalance(root, &height);
}


