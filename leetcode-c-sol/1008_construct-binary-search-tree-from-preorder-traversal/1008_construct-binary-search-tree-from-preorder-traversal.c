/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


typedef struct TreeNode NODE;

static NODE *create_bst(int *pre,
                        int *in,
                        int pre_head,
                        int pre_tail,
                        int in_head,
                        int in_tail)
{
    if (in_head > in_tail)
        return NULL;

    NODE *n = malloc(sizeof(NODE));
    n->val = pre[pre_head];

    int ctr = 0;
    for (int idx = in_head; n->val != in[idx]; idx++, ctr++)
        ;

    n->left = create_bst(pre, in, pre_head + 1, pre_head + ctr, in_head,
                         in_head + ctr - 1);
    n->right = create_bst(pre, in, pre_head + ctr + 1, pre_tail,
                          in_head + ctr + 1, in_tail);

    return n;
}

static int compare(void *a, void *b)
{
    return *(int *) a - *(int *) b;
}

struct TreeNode *bstFromPreorder(int *preorder, int preorderSize)
{
    int *inorder = malloc(sizeof(int) * preorderSize);
    memcpy(inorder, preorder, sizeof(int) * preorderSize);
    qsort(inorder, preorderSize, sizeof(int), compare);
    NODE *ret =
        create_bst(preorder, inorder, 0, preorderSize - 1, 0, preorderSize - 1);

    return ret;
}
