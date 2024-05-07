static struct ListNode* reverse(struct ListNode* head)
{
    struct ListNode* prev = NULL;
    while (head) {
        struct ListNode* tmp = head->next;
        head->next = prev;
        prev = head;
        head = tmp;
    }
    return prev;
}

struct ListNode* doubleIt(struct ListNode* head)
{
    head = reverse(head);
    struct ListNode* root = head;
    int carry = 0;
    while (root) {
        int cur = (root->val << 1) + carry;
        carry = cur / 10;
        root->val = cur % 10;
        root = root->next;
    }
    head = reverse(head);

    if (carry) {
        struct ListNode* carry_node = malloc(sizeof(struct ListNode));
        carry_node->val = 1;
        carry_node->next = head;
        head = carry_node;
    }

    return head;
}
