/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

typedef struct ListNode node_t;

static node_t *insert(node_t *ret, node_t *cur)
{
    node_t *root = ret, *prev = NULL;
    while (root) {
        if (cur->val <= root->val)
            break;
        prev = root;
        root = root->next;
    }

    if (prev)
        prev->next = cur;
    else
        ret = cur;

    cur->next = root;
    return ret;
}

struct ListNode *insertionSortList(struct ListNode *head)
{
    if (!head)
        return NULL;

    /* add first node to ret, so param ret in insert() won't be NULL */
    node_t *ret = head;
    head = head->next;
    ret->next = NULL;
    while (head) {
        node_t *nextn = head->next;
        head->next = NULL;
        ret = insert(ret, head);
        head = nextn;
    }

    return ret;
}