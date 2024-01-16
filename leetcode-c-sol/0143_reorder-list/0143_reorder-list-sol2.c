static inline struct ListNode* reverse_list(struct ListNode* head)
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

void reorderList(struct ListNode* head)
{
    if (!head || !(head->next))
        return;

    struct ListNode *fast = head, *slow = head, *prev = NULL;
    while (fast && fast->next) {
        fast = fast->next->next;
        prev = slow;
        slow = slow->next;
    }
    prev->next = NULL;

    struct ListNode *half = reverse_list(slow);
    struct ListNode *t1 = head->next, *t2 = NULL;
    head->next = half;
    head = t1;
    while (head) {
        t1 = head->next;
        t2 = half->next;
        half->next = head;
        head->next = t2;
        head = t1;
        half = t2;
    }
}
