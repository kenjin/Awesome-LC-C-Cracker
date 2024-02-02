/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

static int get_height(struct TreeNode* root)
{
    if (!root)
        return 0;
    
    int l = get_height(root->left);
    int r = get_height(root->right);
    return (l > r ? l : r) + 1;
}

static void lv_traversal(struct TreeNode* root, int *ret, int lv)
{
    if (!root)
        return;
    
    lv_traversal(root->left, ret, lv+1);
    ret[lv] = root->val;
    lv_traversal(root->right, ret, lv+1);
}

int* rightSideView(struct TreeNode* root, int* returnSize)
{
    int h = get_height(root);
    int *ret = malloc(sizeof(int)*h);
    *returnSize = h;
    lv_traversal(root, ret, 0);
    return ret;
}
