/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* removeLeafNodes(struct TreeNode* root, int target)
{
    if (!root)
        return NULL;

    root->left = removeLeafNodes(root->left, target);
    root->right = removeLeafNodes(root->right, target);

    // leaf node checks given value
    if (root->left == NULL && root->right == NULL && root->val == target) {
        free(root);
        return NULL;
    }

    return root;
}
