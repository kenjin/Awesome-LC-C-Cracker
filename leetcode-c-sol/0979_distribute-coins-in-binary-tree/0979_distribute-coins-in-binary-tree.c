/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int dis_handler(struct TreeNode* root, int* moves) {
    if (!root)
        return 0;

    int l_moves = dis_handler(root->left, moves);
    int r_moves = dis_handler(root->right, moves);

    // Add total moves needed from left/right sub-tree
    root->val += l_moves;
    root->val += r_moves;
    *moves += abs(l_moves);
    *moves += abs(r_moves);
    // - Return the total moves needed for the sub-tree, minus 1 for itself.
    // - If the return value is positive, it means the sub-tree has extra coins
    //   to return.
    // - If the return value is negative, it means the sub-tree needs coins to
    //   be returned. 
    // - If the return value is zero, it means the sub-tree. does NOT need any 
    //   moves for coins.
    return root->val - 1;
}

int distributeCoins(struct TreeNode* root) {
    int moves = 0;
    dis_handler(root, &moves);
    return moves;
}
