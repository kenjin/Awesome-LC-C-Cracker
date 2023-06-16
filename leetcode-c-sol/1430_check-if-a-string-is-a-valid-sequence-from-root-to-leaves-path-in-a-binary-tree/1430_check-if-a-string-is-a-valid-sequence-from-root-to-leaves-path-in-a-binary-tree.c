/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


typedef struct TreeNode NODE;

static bool check_valid_seq(NODE *root, int *arr, int max_lv, int lv)
{
    if (!root || root->val != arr[lv])
        return false;

    if (max_lv == lv)
        return (!root->left && !root->right ? true : false);

    if (!check_valid_seq(root->left, arr, max_lv, lv + 1))
        return check_valid_seq(root->right, arr, max_lv, lv + 1);

    return true;
}

bool isValidSequence(struct TreeNode *root, int *arr, int arrSize)
{
    return check_valid_seq(root, arr, arrSize - 1, 0);
}
