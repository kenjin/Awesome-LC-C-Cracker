static int bst_greater(struct TreeNode* root, int sum)
{
    if (!root)
        return sum;

    root->val += bst_greater(root->right, sum);
    return bst_greater(root->left, root->val);
}

struct TreeNode* bstToGst(struct TreeNode* root)
{
    bst_greater(root, 0);
    return root;
}
