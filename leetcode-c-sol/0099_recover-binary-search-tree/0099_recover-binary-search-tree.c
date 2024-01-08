/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

static int bst_cnt(struct TreeNode* root)
{
    if (!root)
        return 0;
    return bst_cnt(root->left) + bst_cnt(root->right) + 1;
}

static void traverse(struct TreeNode* root, int *inorder, int *cnt)
{
    if (!root)
        return;

    traverse(root->left, inorder, cnt);
    inorder[*cnt] = root->val;
    (*cnt)++;
    traverse(root->right, inorder, cnt);
}

static void recover_bst(struct TreeNode* root, int *inorder, int *cnt)
{
    if (!root)
        return;

    recover_bst(root->left, inorder, cnt);
    root->val = inorder[*cnt];
    (*cnt)++;
    recover_bst(root->right, inorder, cnt);
}


static int compare(const void *a, const void*b)
{
    return (*(int *)a > *(int *)b ? 1 : -1);
}

void recoverTree(struct TreeNode* root)
{
    int nodes = bst_cnt(root), cnt = 0;
    int *inorder = malloc(sizeof(int)*nodes);

    // inorder traversal
    traverse(root, inorder, &cnt);
    // sort the inorder list
    qsort(inorder, nodes, sizeof(int), compare);
    // recover the BST
    cnt = 0;
    recover_bst(root, inorder, &cnt);
    free(inorder);
}
