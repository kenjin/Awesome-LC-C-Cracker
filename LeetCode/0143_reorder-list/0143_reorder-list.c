/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


typedef struct ListNode NODE;
void reorderList(struct ListNode *head)
{
    if (!head)
        return;

    NODE *p1 = head, *p2 = head;
    int len = 0;
    while (p2 && p2->next) {
        len++;
        p2 = p2->next->next;
        p1 = (!p2 ? p1 : p1->next);
    }

    NODE **stack = malloc(sizeof(NODE *) * (len + 1));
    int s_ctr = 0;
    p1 = p1->next;
    while (p1) {
        stack[s_ctr++] = p1;
        p1 = p1->next;
    }
    NODE *cur = head, *tmp = NULL;
    for (int i = s_ctr - 1; i >= 0; i--) {
        tmp = cur->next;
        cur->next = stack[i];
        stack[i]->next = tmp;
        cur = tmp;
    }

    if (tmp)
        tmp->next = NULL;

    free(stack);
}