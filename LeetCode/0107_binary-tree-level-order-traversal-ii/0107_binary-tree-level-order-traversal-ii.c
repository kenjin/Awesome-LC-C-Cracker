/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

void lvorder_traverse(struct TreeNode *root,
                      int **ret,
                      int *ret_sz,
                      int **ret_col_sz,
                      int level)
{
    if (root == NULL)
        return;

    lvorder_traverse(root->left, ret, ret_sz, ret_col_sz,
                     level - 1 /* bottom-up */);
    lvorder_traverse(root->right, ret, ret_sz, ret_col_sz,
                     level - 1 /* bottom-up */);

    ret[level] = realloc(ret[level], sizeof(int) * ((*ret_col_sz)[level] + 1));
    ret[level][(*ret_col_sz)[level]] = root->val;
    (*ret_col_sz)[level] += 1;
}

int get_height(struct TreeNode *root)
{
    if (!root)
        return 0;

    int l = get_height(root->left);
    int r = get_height(root->right);
    return (l > r ? l + 1 : r + 1);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume
 * caller calls free().
 */
int **levelOrderBottom(struct TreeNode *root,
                       int *returnSize,
                       int **returnColumnSizes)
{
    int height = get_height(root);
    int **ret = malloc(sizeof(int *) * height);
    for (int i = 0; i < height; i++)
        ret[i] = malloc(sizeof(int));

    *returnColumnSizes = calloc(height, sizeof(int));
    *returnSize = height;
    lvorder_traverse(root, ret, returnSize, returnColumnSizes,
                     height - 1 /* bottom-up */);

    return ret;
}
