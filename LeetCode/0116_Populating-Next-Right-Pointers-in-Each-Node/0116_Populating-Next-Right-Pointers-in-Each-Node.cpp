/**

116. Populating Next Right Pointers in Each Node [M]
Ref: https://leetcode.com/problems/populating-next-right-pointers-in-each-node/

 */

/*
// Definition for a Node.
class Node {
public:
int val;
Node* left;
Node* right;
Node* next;

Node() {}

Node(int _val, Node* _left, Node* _right, Node* _next) {
val = _val;
left = _left;
right = _right;
next = _next;
}
};
 */
class Solution {
	public:
		void connectRecursive(Node *root)
		{
			if (root == NULL)
			{
				return ;
			}

			if (root->left)
			{
				root->left->next = root->right;
			}
			if (root->right)
			{
				root->right->next = root->next ? root->next->left : NULL;
			}

			connectRecursive(root->left);
			connectRecursive(root->right);
		}

		Node* connect(Node* root) 
		{
			if (root == NULL)
			{
				return NULL;
			}

			root->next = NULL;
			connectRecursive(root);
			return root;
		}    
};
