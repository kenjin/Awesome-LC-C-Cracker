/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* swapNodes(struct ListNode* head, int k)
{
    int ctr = 0;
    struct ListNode *p1 = head, *p2 = head;
    for (int i = 0; i < k; i ++)
        p1 = p1->next;

    while (p1) {
        p1 = p1->next;
        p2 = p2->next;
    }

    p1 = head;
    while (k > 1) {
        p1 = p1->next;
        k--;
    }

    if (p1->val != p2->val) {
        p1->val = p1->val ^ p2->val;
        p2->val = p1->val ^ p2->val;
        p1->val = p1->val ^ p2->val;
    }

    return head;
}
