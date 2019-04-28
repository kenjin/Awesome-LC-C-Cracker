/**
234. Palindrome Linked List [Easy]

Given a singly linked list, determine if it is a palindrome.

Example 1:
	Input: 1->2
	Output: false

Example 2:
	Input: 1->2->2->1
	Output: true

Follow up:
	Could you do it in O(n) time and O(1) space?

 */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
/*
void printNode(struct ListNode* node)
{
    struct ListNode *head = node;
    while (head)
    {
        printf("%d ", head->val);
        head = head->next;
    }
    printf("\n");
}
*/
void reverseLinkedList(struct ListNode* head)
{
    if (head == NULL)
    {
        return;
    }

    struct ListNode *tmpNode = NULL, *nextNode = NULL;
    while (head != NULL)
    {
        nextNode = head->next;
        head->next = tmpNode;
        tmpNode = head;
        head = nextNode;
    }
}

bool isPalindrome(struct ListNode* head)
{
    if (head == NULL || head->next == NULL)
    {
        return true;
    }

    struct ListNode *midNode = head, *tailNode = head;

    /* calculate location of mid and tail */
    while (tailNode->next != NULL && tailNode->next->next != NULL)
    {
        midNode = midNode->next;
        tailNode = tailNode->next->next;
    }

    /* 1->2->3->4->3->2->1
             ^        ^
             mid      tail  <= need to shift to the next
     */
    if (tailNode->next != NULL)
    {
        tailNode = tailNode->next;
    }

    reverseLinkedList(midNode->next);
    //printNode(tailNode);

    struct ListNode *tailNodeTmp = tailNode, *headNodeTmp = head;
    bool ret = true;
    while (tailNodeTmp != NULL)
    {
        if (tailNodeTmp->val != headNodeTmp->val)
        {
            ret = false;
            break;
        }
        tailNodeTmp = tailNodeTmp->next;
        headNodeTmp = headNodeTmp->next;
    }

    /* recover the linked list */
    reverseLinkedList(tailNode);
    //printNode(head);
    return ret;
}
