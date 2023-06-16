/**

426. Convert Binary Search Tree to Sorted Doubly Linked List [M]
Ref: https://leetcode.com/problems/convert-binary-search-tree-to-sorted-doubly-linked-list/

 */

/*
// Definition for a Node.
class Node {
public:
int val;
Node* left;
Node* right;

Node() {}

Node(int _val, Node* _left, Node* _right) {
val = _val;
left = _left;
right = _right;
}
};
 */
class Solution {
	public:
		void inorder(Node **head, Node **last, Node *root)
		{
			if (root == nullptr)
			{
				return;
			}

			inorder(head, last, root->left);
			if (*head == nullptr)
			{
				*head = root;
				*last = root;
			} else 
			{
				(*last)->right = root;
				root->left = *last;
				*last = root;
			}       
			inorder(head, last, root->right);
		}

		Node* treeToDoublyList(Node* root) 
		{
			if (root == nullptr)
			{
				return nullptr;
			}

			Node *head = nullptr;
			Node *last = nullptr;
			inorder(&head, &last, root);      
			last->right = head;
			head->left  = last;
			return head;
		}
};
