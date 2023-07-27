/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
bool hasCycle(struct ListNode *head)
{
    struct ListNode *fast = head, *slow = head;
    while (slow && slow->next)
    {
        fast = fast->next;
        slow = slow->next->next;
        if (fast == slow)
            return true;
    }

    return false;
}
