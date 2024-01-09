/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

#define PUSH_TO_STACK(stack, node)          \
do {                                        \
    struct ListNode *next_one = node->next; \
    node->next = stack.next;                \
    stack.next = node;                      \
    node = next_one;                        \
} while (0)

struct ListNode* removeNodes(struct ListNode* head)
{
    if (!head)
        return NULL;

    struct ListNode stack = {.next = NULL};
    while (head) {
        while (stack.next && head->val > (stack.next)->val) {
            // Pop the smaller node
            struct ListNode *tmp = (stack.next)->next;
            free(stack.next);
            stack.next = tmp;
        }
        // Push to stack
        PUSH_TO_STACK(stack, head);
    }

    // Reverse the list
    head = stack.next;
    stack.next = NULL;
    while (head) {
        PUSH_TO_STACK(stack, head);
    }

    return stack.next;
}
