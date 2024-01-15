#define MAX(a, b) (a > b ? a : b)

int mps_helper(struct TreeNode* root, int *max)
{
    if (!root)
        return 0;

    int lmax = INT_MIN, rmax= INT_MIN;
    int lret = mps_helper(root->left, &lmax);
    int rret = mps_helper(root->right, &rmax);

    int tmp_max = root->val;
    if (lret > 0)
        tmp_max += lret;
    if (rret > 0)
        tmp_max += rret;

    *max = MAX(rmax, lmax);
    *max = MAX(*max, tmp_max);

    // return max path sum(root / root+left / root+right) with current node
    if (lret < 0  && rret < 0)
        return root->val;
    else
        return (root->val + MAX(lret, rret));
}

int maxPathSum(struct TreeNode* root)
{
    int max = INT_MIN;
    mps_helper(root, &max);
    return max;
}
