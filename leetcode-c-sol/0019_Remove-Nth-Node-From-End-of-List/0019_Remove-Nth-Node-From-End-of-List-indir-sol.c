struct ListNode* removeNthFromEnd(struct ListNode* head, int n)
{
    struct ListNode *fast = head, **indir = &head;
    for (int i = 0; i < n; i++)
        fast = fast->next;
    for (; fast; fast = fast->next)
        indir = &(*indir)->next;

    *indir = (*indir)->next;
    return head;
}
