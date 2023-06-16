/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

typedef struct ListNode node_t;
static node_t *revert_list(node_t *head)
{
    node_t *prev = NULL;
    while (head) {
        node_t *nextn = head->next;
        head->next = prev;
        prev = head;
        head = nextn;
    }
    return prev;
}

bool isPalindrome(node_t *head)
{
    /* make sure that there are at least two nodes in list */
    if (!head || !head->next)
        return true;

    node_t *p1 = head, *p2 = head, *prev = NULL;
    while (p2 && p2->next) {
        prev = p1;
        p1 = p1->next;
        p2 = p2->next->next;
    }

    prev->next = NULL;
    p1 = revert_list(p1);
    while (p1 && head) {
        if (head->val != p1->val)
            return false;

        p1 = p1->next;
        head = head->next;
    }

    return true;
}