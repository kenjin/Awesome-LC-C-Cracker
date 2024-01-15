int lca_runner(struct TreeNode *root, struct TreeNode *p, struct TreeNode *q, struct TreeNode **ret)
{
    if (!root || *ret)
        return 0;

    int num = lca_runner(root->left, p, q, ret);
    if (*ret)
        return 0;

    num += lca_runner(root->right, p, q, ret);
    num += (root == p || root == q ? 1 : 0);
    if (NULL == *ret && num == 2) {
        *ret = root;
    }
    return num;
}

struct TreeNode *lowestCommonAncestor(struct TreeNode *root, struct TreeNode *p, struct TreeNode *q) {
    struct TreeNode *ret = NULL;
    lca_runner(root, p, q, &ret);
    return ret;
}
