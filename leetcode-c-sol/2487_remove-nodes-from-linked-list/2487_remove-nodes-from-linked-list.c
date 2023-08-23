static inline struct ListNode* reverse(struct ListNode* head)
{
    struct ListNode *root = head, *prev = NULL;
    while (root) {
        struct ListNode *tmp = root->next;
        root->next = prev;
        prev = root;
        root = tmp;
    }
    return prev;
}

struct ListNode* removeNodes(struct ListNode* head)
{
    if (!head)
        return NULL;

    head = reverse(head);

    struct ListNode ret = {.next = head};
    struct ListNode *root = head->next;
    while (root) {
        if (root->val >= head->val) {
            head->next = root;
            head = root;
        }
        root = root->next;
    }
    head->next = NULL;

    ret.next = reverse(ret.next);
    return ret.next;
}
