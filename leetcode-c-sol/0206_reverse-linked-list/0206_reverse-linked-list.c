/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* reverseList(struct ListNode* head)
{
    struct ListNode root = {.next = NULL};
    while (head) {
        struct ListNode *tmp = head->next;
        head->next = root.next;
        root.next = head;
        head = tmp;
    }
    return root.next;
}
