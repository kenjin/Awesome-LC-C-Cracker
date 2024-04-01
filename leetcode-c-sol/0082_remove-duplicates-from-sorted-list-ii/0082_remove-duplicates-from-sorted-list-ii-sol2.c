/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

/**
 * Delete duplicate nodes in a linked list.
 * @param head The head pointer of the linked list.
 * @return The head pointer of the linked list without duplicate nodes.
 */
struct ListNode* deleteDuplicates(struct ListNode* head) {
    struct ListNode *prev = NULL;  // Pointer to the previous node
    struct ListNode *root = head;  // Pointer to the root node of the list
    struct ListNode *cur = head;   // Pointer to the current node

    // Traverse the linked list
    while (cur && cur->next) {
        // If the current node and the next node are different
        if (cur->val != cur->next->val) {
            prev = cur;
            cur = cur->next;
            continue;
        }
        // Otherwise, find all subsequent nodes with the same value
        while (cur->next && cur->val == cur->next->val) {
            cur = cur->next;
        }
        // Delete duplicate nodes
        if (prev)
            prev->next = cur->next;
        else
            root = cur->next;

        cur = cur->next;
    }
    return root;  // Return the head pointer of the processed linked list
}

