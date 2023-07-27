/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

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
    if (NULL == head || NULL == head->next)
        return;

    // Find the mid of the list
    struct ListNode *fast = head, *slow = head, *prev = NULL;
    while (fast && fast->next) {
        fast = fast->next->next;
        prev = slow;
        slow = slow->next;
    }

    struct ListNode *half;
    if (fast && NULL == fast->next) {
        // odd len
        half = slow->next;
        slow->next = NULL;
    } else {
        // even len
        half = slow;
        prev->next = NULL;
    }

    // reverse
    half = reverse_list(half);
    while (half) {
        struct ListNode *tmp1 = head->next;
        struct ListNode *tmp2 = half->next;
        head->next = half;
        half->next = tmp1;
        half = tmp2;
        head = tmp1;
    }
}
