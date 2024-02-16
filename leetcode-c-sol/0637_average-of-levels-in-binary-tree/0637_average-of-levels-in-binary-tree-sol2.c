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

static int get_height(struct TreeNode* root) {
    if (!root)
        return 0;
    int l = get_height(root->left);
    int r = get_height(root->right);
    return (l > r ? l : r) + 1;
}

static void traversal(struct TreeNode* root, int lv, double* ret, int* ctr) {
    if (!root)
        return;

    ret[lv] += root->val;
    ctr[lv] += 1;
    traversal(root->left, lv + 1, ret, ctr);
    traversal(root->right, lv + 1, ret, ctr);
}

double* averageOfLevels(struct TreeNode* root, int* returnSize) {
    int height = get_height(root);
    int* ctr = calloc(height, sizeof(int));
    double* ret = calloc(height, sizeof(double));
    *returnSize = height;

    traversal(root, 0, ret, ctr);

    for (int i = 0; i < height; i++)
        ret[i] /= ctr[i];

    free(ctr);
    return ret;
}
