/**

117. Populating Next Right Pointers in Each Node II [M]
Ref: https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/

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

			/* Find the same level next node from right sub-tree */
			Node *tmpNext = root->next;
			while (tmpNext)
			{
				if (tmpNext->left)
				{
					tmpNext = tmpNext->left;
					break;
				} else if (tmpNext->right)
				{
					tmpNext = tmpNext->right;
					break;
				} else
				{
					tmpNext = tmpNext->next;
				}
			}

			if (root->left)
			{
				if (root->right)
				{
					root->left->next = root->right;
				} else
				{
					root->left->next = tmpNext;
				}
			}
			if (root->right)
			{
				root->right->next = tmpNext;
			}

			/* Must check right sub-tree first */
			connectRecursive(root->right);
			connectRecursive(root->left);
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
