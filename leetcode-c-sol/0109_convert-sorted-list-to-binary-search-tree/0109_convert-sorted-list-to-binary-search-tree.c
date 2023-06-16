/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


typedef struct TreeNode tree_t;
typedef struct ListNode list_t;

static list_t *cut_list_half(list_t *head)
{
    list_t *p1 = head, *p2 = head, *prev = NULL;
    while (p2 && p2->next) {
        prev = p1;
        p1 = p1->next;
        p2 = p2->next->next;
    }
    if (prev)
        prev->next = NULL;
    return p1;
}
struct TreeNode *sortedListToBST(list_t *head)
{
    if (!head)
        return NULL;

    tree_t *cur = calloc(1, sizeof(tree_t));
    if (!head->next) {
        /* one node in list */
        cur->val = head->val;
    } else {
        /* separate to left-half and right-half */
        list_t *mid = cut_list_half(head);
        cur->val = mid->val;
        cur->left = sortedListToBST(head);
        cur->right = sortedListToBST(mid->next);
    }
out:
    return cur;
}