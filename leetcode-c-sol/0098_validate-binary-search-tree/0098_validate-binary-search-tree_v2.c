bool valid_bst_runner(struct TreeNode* root, int *min, int *max)
{
    if (!root)
        return true;

    int l_min, l_max, r_min, r_max;
    if (valid_bst_runner(root->left, &l_min, &l_max) &&
        valid_bst_runner(root->right, &r_min, &r_max)) {

        if ((root->left && root->val <= l_max) ||
            (root->right && root->val >= r_min))
            return false;

        *min = (root->left ? l_min : root->val);
        *max = (root->right ? r_max : root->val);
        return true;
    }

    return false;
}

bool isValidBST(struct TreeNode* root)
{
    int min, max;
    return valid_bst_runner(root, &min, &max);
}
