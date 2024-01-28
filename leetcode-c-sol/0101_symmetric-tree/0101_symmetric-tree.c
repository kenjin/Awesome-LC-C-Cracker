/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

bool check_symmetric(struct TreeNode* r1, struct TreeNode* r2)
{
    if (!r1 || !r2) {
        return (!r1 && !r2);
    } else {
        if (r1->val != r2->val)
            return false;
        return check_symmetric(r1->left, r2->right) && check_symmetric(r1->right, r2->left);
    }
}

bool isSymmetric(struct TreeNode* root)
{
    return check_symmetric(root->left, root->right);
}
