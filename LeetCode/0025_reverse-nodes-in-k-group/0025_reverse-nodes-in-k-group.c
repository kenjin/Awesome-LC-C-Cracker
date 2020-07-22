/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

typedef struct ListNode NODE;

static void reverse_list(NODE *head, NODE *tail)
{
    NODE *prev = NULL;
    NODE *curr = head;
    while (curr != tail) {
        NODE *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    curr->next = prev;
    NODE *root = curr;
}

struct ListNode *reverseKGroup(struct ListNode *head, int k)
{
    int ctr = 0;
    NODE *curr = head, *prev = NULL, *tmp_head = NULL, *tmp_tail = NULL;
    while (curr) {
        if (ctr == 0)
            tmp_head = curr;

        ctr++;
        if (ctr == k) {
            tmp_tail = curr;
            curr = curr->next;
            reverse_list(tmp_head, tmp_tail);
            if (!prev) /* first time to reverse */
                head = tmp_tail;
            else
                prev->next = tmp_tail;

            prev = tmp_head;
            ctr = 0;
        } else {
            curr = curr->next;
        }
    }

    if (ctr && prev)
        prev->next = tmp_head;

    return head;
}