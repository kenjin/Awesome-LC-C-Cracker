/*
430. Flatten a Multilevel Doubly Linked List [M]
Ref: https://leetcode.com/problems/flatten-a-multilevel-doubly-linked-list/

You are given a doubly linked list which in addition to the next and 
previous pointers, it could have a child pointer, which may or may not 
point to a separate doubly linked list. These child lists may have one 
or more children of their own, and so on, to produce a multilevel data 
structure, as shown in the example below.

Flatten the list so that all the nodes appear in a single-level, doubly 
linked list. You are given the head of the first level of the list.

 

Example:

Input:
1---2---3---4---5---6--NULL
        |
        7---8---9---10--NULL
            |
            11--12--NULL

Output:
1-2-3-7-8-11-12-9-10-4-5-6-NULL

 */

/*
// Definition for a Node.
class Node {
public:
int val;
Node* prev;
Node* next;
Node* child;

Node() {}

Node(int _val, Node* _prev, Node* _next, Node* _child) {
val = _val;
prev = _prev;
next = _next;
child = _child;
}
};
 */
class Solution {
	public:
		Node* flatten_recursion(Node *pre, Node *cur) 
		{
			if (cur == NULL)
			{
				return NULL;
			}
			// Backup the pointer
			Node *t1 = pre;
			Node *t2 = cur;
			Node *tmpChild = cur->child;
			Node *tmpNext = cur->next;   
			// Traverse "child(left)" sub-tree
			pre = cur;
			Node *lChild = flatten_recursion(pre, tmpChild);
			// Traverse "next(right)" sub-tree
			pre = (lChild == NULL ? cur : lChild);
			Node *rChild = flatten_recursion(pre, tmpNext);

			// Update the link between prev and cur
			if (t1 != NULL)
			{
				t1->next = t2;
			}
			t2->prev = t1;
			t2->child = NULL;

			// return cur node or last child node
			return (rChild == NULL ? cur: rChild);
		}

		Node* flatten(Node* head) 
		{
			if (head == NULL)
			{
				return NULL;
			}

			Node *pre = NULL;
			flatten_recursion(pre, head);
			return head;
		}
};
