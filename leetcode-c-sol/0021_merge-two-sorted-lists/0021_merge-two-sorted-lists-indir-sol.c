struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2)
{
    struct ListNode *root = NULL;
    struct ListNode **indirect = &root;
    while (list1 && list2) {
        if (list1->val < list2->val) {
            *indirect = list1;
            list1 = list1->next;
        } else {
            *indirect = list2;
            list2 = list2->next;
        }
        indirect = &((*indirect)->next);
    }

    if (list1)
        *indirect = list1;

    if (list2)
        *indirect = list2;

    return root;
}
