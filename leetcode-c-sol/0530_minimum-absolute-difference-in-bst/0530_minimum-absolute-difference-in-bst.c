#define MIN(a, b) (a < b ? a : b)
static void runner(struct TreeNode* root, int *min, int *prev)
{
    if (!root)
        return;

    runner(root->left, min, prev);
    if (*prev != -1) {
        int diff = abs(root->val - *prev);
        *min = MIN(*min, diff);
    }
    *prev = root->val;
    runner(root->right, min, prev);
}

int getMinimumDifference(struct TreeNode* root)
{
    int min = INT_MAX, prev = -1;
    runner(root, &min, &prev);
    return min;    
}
