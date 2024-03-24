/*
 * Approach: Fast-Slow pointers
 *
 * [R]: root
 * [M]: meet point
 * [*]: start point in cycle
 *
 *       "X"      "Y"
 * [R] ------[*]------- [M]---
 *            |     "Z"      |
 *             ---------------
 *
 * Distance(Slow) = X + Y          (R->*->M)
 * Distance(Fast) = X + Y + Y + Z  (R->*->M->*->M)
 * => Fast travels with double speed and two pointers meet at the same time.
 * => 2*Distance(Slow) = Distance(Fast)
 * => 2*(X+Y) = X+Y+Y+Z
 * =>       X = Z
 *
 * It means that [R] and [M] will meet at [*] after X moves of [R] and Z moves of [M].
 */

static inline struct ListNode* find_meet(struct ListNode* head)
{
    struct ListNode *fast = head, *slow = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast)
            return slow;
    }
    return NULL;
}

struct ListNode* detectCycle(struct ListNode* head)
{
    struct ListNode *meet = find_meet(head);    
    while (meet) {
        if (head == meet)
            return head;
        head = head->next;
        meet = meet->next;
    }   

    return NULL;
}
