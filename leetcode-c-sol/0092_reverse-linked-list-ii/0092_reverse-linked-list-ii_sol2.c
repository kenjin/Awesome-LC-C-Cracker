/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

typedef struct ListNode node_t;

static inline void revert(node_t *head, node_t *tail)
{
    node_t *prev = NULL;
    while (head != tail) {
        node_t *nextn = head->next;
        head->next = prev;
        prev = head;
        head = nextn;
    }
    tail->next = prev;
}

struct ListNode *reverseBetween(struct ListNode *head, int m, int n)
{
    int ctr = 1;
    node_t *cur = head;
    node_t *p1 = NULL, *p2 = NULL;
    for (int ctr = 1; ctr <= n; ctr++, cur = cur->next) {
        if (ctr == m - 1)
            p1 = cur;
        if (ctr == n)
            p2 = cur;
    }

    if (p1) {
        node_t *tmp = p1->next;
        revert(p1->next, p2);
        p1->next = p2;
        tmp->next = cur;
    } else {
        revert(head, p2);
        head->next = cur;
        head = p2;
    }

    return head;
}