/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* mergeInBetween(struct ListNode* list1, int a, int b, struct ListNode* list2)
{
    struct ListNode **a_indir = &list1;
    struct ListNode *b_next = NULL;
    int idx = 0;
    // Locate the pointer a_ptr
    while (idx < a) {
        a_indir = &((*a_indir)->next);
        idx++;
    }
    // Determine the pointer b_next that follows after b(th) node
    b_next = *a_indir;
    while (idx <= b) {
        b_next = b_next->next;
        idx++;
    }
    // Update a_ptr to reference list2, and then link the last node of list2 to
    // b_next.
    *a_indir = list2;
    while (list2->next)
        list2 = list2->next;
    list2->next = b_next;

    return list1;
}
