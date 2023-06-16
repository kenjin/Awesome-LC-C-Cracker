/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

static struct ListNode* inverse(struct ListNode* head)
{
    struct ListNode *prev = NULL;
    while (head)
    {
        struct ListNode *tmp = head->next;
        head->next = prev;
        prev = head;
        head = tmp;
    }

    return prev;
}

int pairSum(struct ListNode* head)
{
    struct ListNode *fast = head;
    struct ListNode *slow = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    slow = inverse(slow);

    int ret = -1; // 1 <= Node.val <= 10^5
    while (slow)
    {
        int tmp = head->val + slow->val;
        ret = (tmp > ret ? tmp : ret);
        head = head->next;
        slow = slow->next;
    }
    return ret;
}
