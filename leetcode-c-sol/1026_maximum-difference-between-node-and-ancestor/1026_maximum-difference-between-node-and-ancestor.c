
#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)

void postorder(struct TreeNode* root, int *ret, int *min, int *max)
{
    if (!root)
        return;

    int lmin = root->val, lmax = root->val, rmin = root->val, rmax = root->val;
    postorder(root->left, ret, &lmin, &lmax);
    postorder(root->right, ret, &rmin, &rmax);

    *min = MIN(*min, lmin);
    *max = MAX(*max, lmax);
    *min = MIN(*min, rmin);
    *max = MAX(*max, rmax);

    int diff1 = abs(root->val - *min);
    int diff2 = abs(root->val - *max);
    if (*ret < diff1 || *ret < diff2)
        *ret = MAX(diff1, diff2);

    if (root->val < *min)
        *min = root->val;
    if (root->val > *max)
        *max = root->val;
}

int maxAncestorDiff(struct TreeNode* root)
{
    int ret = 0, min = 50001, max = -1;
    postorder(root, &ret, &min, &max);
    return ret;
}
