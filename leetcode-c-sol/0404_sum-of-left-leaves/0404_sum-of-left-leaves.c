/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

typedef struct TreeNode node_t;
static int count_left_leaf(node_t *root, bool is_left)
{
    if (!root)
        return 0;

    if (!root->left && !root->right)
        return (is_left ? root->val : 0);

    return count_left_leaf(root->left, true) +
           count_left_leaf(root->right, false);
}

int sumOfLeftLeaves(node_t *root)
{
    return count_left_leaf(root, false);
}