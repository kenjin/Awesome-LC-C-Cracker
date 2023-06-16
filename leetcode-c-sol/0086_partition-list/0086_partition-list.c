/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

typedef struct ListNode list_t;
struct ListNode *partition(struct ListNode *head, int x)
{
    list_t *lt_head = calloc(1, sizeof(list_t));
    list_t *ge_head = calloc(1, sizeof(list_t));
    list_t *cur = head, *lt_cur = lt_head, *ge_cur = ge_head;
    while (cur) {
        if (cur->val < x) {
            lt_cur->next = cur;
            lt_cur = cur;
        } else {
            ge_cur->next = cur;
            ge_cur = cur;
        }
        cur = cur->next;
    }

    lt_cur->next = ge_head->next;
    ge_cur->next = NULL;
    head = lt_head->next;
    free(lt_head);
    free(ge_head);
    return head;
}