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
    NODE *cur = head, *prev = NULL;
    while (cur != tail) {
        NODE *next_one = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next_one;
    }
    cur->next = prev;
}

struct ListNode *reverseKGroup(struct ListNode *head, int k)
{
    int ctr = 0;
    NODE *cur = head, *prev = NULL, *tmp_head = NULL, *tmp_tail = NULL;
    while (cur) {
        NODE *next_one = cur->next;
        ctr++;
        if (ctr == 1) {
            tmp_head = cur;
        } else if (ctr == k) {
            tmp_tail = cur;
            reverse_list(tmp_head, tmp_tail);
            if (!prev)
                head = tmp_tail;
            else
                prev->next = tmp_tail;

            prev = tmp_head;
            ctr = 0;
        }
        cur = next_one;
    }

    if (ctr && prev)
        prev->next = tmp_head;

    return head;
}