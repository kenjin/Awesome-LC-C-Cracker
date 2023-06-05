/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* mergeNodes(struct ListNode* head)
{
    struct ListNode ret;
    struct ListNode *prev = &ret;
    head = head->next;
    while (head) {
        int sum = 0;
        while (0 != head->val) {
            sum += head->val;
            head = head->next;
        }
        prev->next = head;
        head->val = sum;
        prev = head;
        head = head->next;
    }

    return ret.next;
}
