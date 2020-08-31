/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

typedef struct TreeNode node_t;

static node_t *find_lmost(node_t *root, node_t *parent)
{
    if (NULL == root->left) {
        /* Update parent->left to current's right child */
        if (parent)
            parent->left = root->right;
        return root;
    }

    return find_lmost(root->left, root);
}

static node_t *find_rmost(node_t *root, node_t *parent)
{
    if (NULL == root->right) {
        /* Update parent->right to current's left child */
        if (parent)
            parent->right = root->left;
        return root;
    }

    return find_rmost(root->right, root);
}
struct TreeNode *deleteNode(struct TreeNode *root, int key)
{
    if (!root)
        return NULL;

    if (root->val == key) {
        node_t *tmp = NULL;
        if (root->left) {
            /**
             * Case 1: have left sub-tree
             * Find right-most child from left sub-tree
             */
            tmp = find_rmost(root->left, NULL);
            tmp->left = (root->left == tmp ? root->left->left : root->left);
            tmp->right = root->right;
        } else if (root->right) {
            /**
             * Case 2: have only right sub-tree
             * Find left-most child from right sub-tree
             */
            tmp = find_lmost(root->right, NULL);
            tmp->right =
                (root->right == tmp ? root->right->right : root->right);
            tmp->left = NULL;
        }
        free(root);
        return tmp;
    }

    if (root->val > key)
        root->left = deleteNode(root->left, key);
    else
        root->right = deleteNode(root->right, key);

    return root;
}