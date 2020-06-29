/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
#define MAX_NODE    501

void match_dist(struct TreeNode *root,
                int K,
                int distance,
                int *ret,
                int *retSize)
{
    if (root == NULL || K < distance)
        return;

    if (K == distance) {
        ret[(*retSize)++] = root->val;        
        return;
    }
    match_dist(root->left, K, distance + 1, ret, retSize);
    match_dist(root->right, K, distance + 1, ret, retSize);
}

int find_node(struct TreeNode *root,
              struct TreeNode *target,
              int K,
              int *ret,
              int *ret_sz)
{
    if (!root)
        return -1;

    /* Current node is the target */
    if (root == target) {
        match_dist(root, K, 0 /*distance*/, ret, ret_sz);
        return 1;
    }
    /* Find the target from left child */
    int lchild_dist = find_node(root->left, target, K, ret, ret_sz);
    if (lchild_dist != -1) {
        if (lchild_dist == K)
            ret[(*ret_sz)++] = root->val;

        match_dist(root->right, K, lchild_dist + 1, ret, ret_sz);
        return lchild_dist + 1;
    }
    /* Find the target from right child */
    int rchild_dist = find_node(root->right, target, K, ret, ret_sz);
    if (rchild_dist != -1) {
        if (rchild_dist == K)
            ret[(*ret_sz)++] = root->val;

        match_dist(root->left, K, rchild_dist + 1, ret, ret_sz);
        return rchild_dist + 1;
    }

    return -1;
}

int *distanceK(struct TreeNode *root,
               struct TreeNode *target,
               int K,
               int *returnSize)
{
    int *result = malloc(sizeof(int) * MAX_NODE);
    *returnSize = 0;

    find_node(root, target, K, result, returnSize);
    return result;
}