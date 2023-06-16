/**

103. Binary Tree Zigzag Level Order Traversal [Medium]

Given a binary tree, return the zigzag level order traversal of its
nodes' values. (ie, from left to right, then right to left for the next level
and alternate between).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7

return its zigzag level order traversal as:
[
  [3],
  [20,9],
  [15,7]
]

 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

typedef struct TreeNode NODE;

static int max_height(NODE *root)
{
    if (!root)
        return 0;

    int lmax = max_height(root->left);
    int rmax = max_height(root->right);
    return (lmax > rmax ? lmax : rmax) + 1;
}

static void lvorder_trav(NODE *root, int **ret, int level, int *col)
{
    if (!root)
        return;

    ret[level] = realloc(ret[level], sizeof(int) * (col[level] + 1));
    ret[level][(col[level])] = root->val;
    col[level] += 1;

    lvorder_trav(root->left, ret, level + 1, col);
    lvorder_trav(root->right, ret, level + 1, col);
}

static void reverse(int *ret, int start, int end)
{
    while (start < end) {
        int tmp = ret[start];
        ret[start] = ret[end];
        ret[end] = tmp;
        start++;
        end--;
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume
 * caller calls free().
 */
int **zigzagLevelOrder(struct TreeNode *root, int *ret_sz, int **ret_colsz)
{
    *ret_sz = max_height(root);

    if (!(*ret_sz))
        return NULL;

    int **ret = (int **) malloc(sizeof(int *) * (*ret_sz));
    *ret_colsz = (int *) calloc(*ret_sz, sizeof(int));
    for (int i = 0; i < (*ret_sz); i++)
        ret[i] = malloc(sizeof(int));

    lvorder_trav(root, ret, 0, *ret_colsz);

    /* zigzag level process */
    for (int x = 1; x < *ret_sz; x += 2)
        reverse(ret[x], 0, (*ret_colsz)[x] - 1);

    return ret;
}
