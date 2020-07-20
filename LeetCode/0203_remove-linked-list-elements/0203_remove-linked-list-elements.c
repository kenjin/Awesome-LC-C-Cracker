/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

typedef struct ListNode NODE;
struct ListNode* removeElements(struct ListNode* head, int val)
{
    NODE *prev = NULL, *cur = head;    
    /* Remove the val in the head of position */
    while (cur) {
        if (cur->val != val)
            break;        
        head = cur->next;
        free(cur);
        cur = head;
    }

    while (cur) {
        if (cur->val == val) {            
            prev->next = cur->next;
            free(cur);
            cur = prev;            
        }
        prev = cur;
        cur = cur->next;        
    }
    
    return head;
}