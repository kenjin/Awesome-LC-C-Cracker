/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int leftmost(struct TreeNode *root)
{
    int lv = 0;
    while (root != NULL) {
        lv++;
        root = root->left;
    }
    return lv;
}

int countNodes_helper(struct TreeNode *root, int level)
{
    if (root == NULL)
        return 0;

    struct TreeNode *l = root, *r = root;
    int leftmost_lv_lchild = level - 1;
    int leftmost_lv_rchild = leftmost(root->right);
    int count = 1; /* count current node */

    if (r_leftmost_lv == l_leftmost_lv) {
        count += (1 << l_leftmost_lv) - 1;
        count += countNodes_helper(root->right, r_leftmost_lv);
    } else {
        count += countNodes_helper(root->left, l_leftmost_lv);
        count += (1 << r_leftmost_lv) - 1;
    }

    return count;
}

int countNodes(struct TreeNode *root)
{
    int level = leftmost(root);
    return countNodes_helper(root, level);
}
