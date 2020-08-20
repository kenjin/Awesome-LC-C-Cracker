/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

typedef struct ListNode NODE;
static NODE *reverse_list(struct ListNode *cur)
{
    NODE *prev = NULL;
    while (cur) {
        NODE *next_one = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next_one;
    }
    return prev;
}

void reorderList(struct ListNode *head)
{
    if (!head || !head->next)
        return;

    NODE *p1 = head, *p2 = head;
    int size = 0;
    while (p2 && p2->next) {
        size++;
        p2 = p2->next->next;
        p1 = (!p2 ? p1 : p1->next);
    }

    NODE *r_half = p1->next;
    p1->next = NULL;
    r_half = reverse_list(r_half);
    while (head && r_half) {
        NODE *h_next = head->next, *c_next = r_half->next;
        head->next = r_half;
        r_half->next = h_next;
        r_half = c_next;
        head = h_next;
    }
}
