/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

typedef struct TreeNode NODE;
typedef struct __list_node {
    int val;
    struct __list_node *head;
    struct __list_node *next;
} LIST;

void path_sum_traverse(NODE *root,
                       LIST *l,
                       int path_sum,
                       int target_sum,
                       int *ret)
{
    if (!root)
        return;

    LIST *newl = malloc(sizeof(LIST));
    newl->head = l->head;
    newl->next = NULL;
    newl->val = root->val;
    l->next = newl;

    int tmp_sum = path_sum + root->val;
    LIST *l_head =
        l->head->next; /* head is an empty node, start from the next */
    while (l_head) {
        if (tmp_sum == target_sum)
            *ret += 1;
        tmp_sum -= l_head->val;
        l_head = l_head->next;
    }

    path_sum_traverse(root->left, newl, path_sum + root->val, target_sum, ret);
    path_sum_traverse(root->right, newl, path_sum + root->val, target_sum, ret);
    free(newl);
}

int pathSum(struct TreeNode *root, int sum)
{
    /* Create an empty head list node */
    LIST *l = calloc(1, sizeof(LIST));
    l->head = l;
    int ret = 0;

    path_sum_traverse(root, l, 0, sum, &ret);
    free(l);
    return ret;
}
