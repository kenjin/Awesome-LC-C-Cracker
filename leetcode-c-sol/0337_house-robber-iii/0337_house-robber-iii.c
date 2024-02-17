/***

Approach: Recursion

Use a rob_helper() to return the max amount of money robbed with the current
node as the root node.

- Utilize two parameters, l and r, representing the maximum amount of money that
  can be obtained by robbing starting from the left and right child nodes.
- If the current node does not exist, return 0 directly.
- Otherwise, call the recursive function for the left and right child nodes
  separately to get l and r. Additionally, use 4 variables(l_lchild, l_rchild,
  r_lchild, and r_rchild) for the left node's child and right node's child.
- The final return value is the comparison of 2 parts: one part is the sum of
  the cur node's value plus l_lchild, l_rchild, r_lchild, and r_rchild. This
  is understandable because if the current house is robbed, then the left and
  right child nodes cannot be robbed, but the 4 child nodes in the next level
  can still be robbed. The other part is not robbing the current house but 
  robbing its left and right child nodes, i.e., the value of l+r. Return the 
  larger value of the two parts.

***/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

static int rob_helper(struct TreeNode* root, int* l, int* r) {
    if (!root)
        return 0;

    int l_lchild = 0, l_rchild = 0, r_lchild = 0, r_rchild = 0;
    *l = rob_helper(root->left, &l_lchild, &l_rchild);
    *r = rob_helper(root->right, &r_lchild, &r_rchild);

    int rob_cur_sum = root->val + l_lchild + l_rchild + r_lchild + r_rchild;
    int rob_child_sum = *l + *r;
    return (rob_cur_sum > rob_child_sum ? rob_cur_sum : rob_child_sum);
}

int rob(struct TreeNode* root) {
    int l = 0, r = 0;
    return rob_helper(root, &l, &r);
}
