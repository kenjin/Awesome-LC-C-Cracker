/*
708. Insert into a Cyclic Sorted List [M]
Ref: https://leetcode.com/problems/insert-into-a-cyclic-sorted-list/

Given a node from a cyclic linked list which is sorted in ascending order, write a function to insert a value into the list such that it remains a cyclic sorted list. The given node can be a reference to any single node in the list, and may not be necessarily the smallest value in the cyclic list.

If there are multiple suitable places for insertion, you may choose any place to insert the new value. After the insertion, the cyclic list should remain sorted.

If the list is empty (i.e., given node is null), you should create a new single cyclic list and return the reference to that single node. Otherwise, you should return the original given node.

 */

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;

    Node() {}

    Node(int _val, Node* _next) {
        val = _val;
        next = _next;
    }
};
*/
class Solution {
	public:
		Node* insert(Node* head, int insertVal) 
		{
			if (head == NULL)
			{
				head = new Node(insertVal, NULL);
				head->next = head;
				return head;
			}
			Node *pre = head, *cur = pre->next;
			while (cur != head)
			{
				// edge case: insert [6] or [-1] between 5 and 0
				// 5  ->  [6/-1]  ->  0            
				// ^pre               ^cur
				if ((pre->val > cur->val && (insertVal > pre->val || insertVal < cur->val)) ||
						(insertVal >= pre->val && insertVal <= cur->val))
				{
					break;   
				}
				pre = cur;
				cur = cur->next;
			}
			pre->next = new Node(insertVal, cur);
			return head;
		}
};
