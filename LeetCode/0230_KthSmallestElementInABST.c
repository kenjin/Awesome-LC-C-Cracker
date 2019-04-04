/**
230. Kth Smallest Element in a BST [M]

Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.

Note: 
You may assume k is always valid, 1 ≤ k ≤ BST's total elements.

Example 1:

Input: root = [3,1,4,null,2], k = 1
   3
  / \
 1   4
  \
   2

Output: 1


Example 2:

Input: root = [5,3,6,2,4,null,null,1], k = 3
       5
      / \
     3   6
    / \
   2   4
  /
 1

Output: 3

Follow up:
What if the BST is modified (insert/delete operations) often and you need to find the kth smallest frequently? How would you optimize the kthSmallest routine?

*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int inorder(struct TreeNode* root, int *index, int k)
{
    int target = 0;
    if (root == NULL)
    {
        return 0;
    }
    if ((target = inorder(root->left, index, k)) != 0)
    {
        return target;
    }

    *index += 1;
    if (*index == k)
    {
        return root->val;
    }

    if ((target = inorder(root->right, index, k)) != 0)
    {
        return target;
    }

    return 0;
}

int kthSmallest(struct TreeNode* root, int k) {
    int index = 0;
    return inorder(root, &index, k);
}

