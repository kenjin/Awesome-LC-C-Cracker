/**

  100. Same Tree [E]
Ref: https://leetcode.com/problems/same-tree/

 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

bool isSameTree(struct TreeNode *p, struct TreeNode *q)
{
    if (p == NULL && q == NULL) {
        return true;
    } else if (p != NULL && q != NULL) {
        if (p->val == q->val) {
            if (!isSameTree(p->left, q->left))
                return false;

            return isSameTree(p->right, q->right);
        }
    }

    return false;
}
