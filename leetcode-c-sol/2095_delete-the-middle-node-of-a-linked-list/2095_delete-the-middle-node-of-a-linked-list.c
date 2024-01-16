struct ListNode* deleteMiddle(struct ListNode* head)
{
    if (!head || !(head->next))
        return NULL;

    struct ListNode *fast = head, *slow = head, *prev = NULL;
    while (fast && fast->next) {
        fast = fast->next->next;
        prev = slow;
        slow = slow->next;
    }
    prev->next = slow->next;
    return head;
}
