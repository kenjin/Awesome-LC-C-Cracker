/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

static void dfs(struct TreeNode* root, int *set, int *ret)
{
    if (!root)
        return;

    set[root->val - 1]++;
    if (!root->left && !root->right) {
        int single = 0;
        for (int i = 0; i < 9; i++) {
            if (set[i] & 0x1)
                single++;
        }
        if (single <= 1)
            *ret += 1;
    }
    dfs(root->left, set, ret);
    dfs(root->right, set, ret);
    set[root->val - 1]--;
}

int pseudoPalindromicPaths(struct TreeNode* root)
{
    int set[9] = {0}, ret = 0;
    dfs(root, set, &ret);
    return ret;
}
