/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

double cal_max_avg(struct TreeNode *root, double *max_avg, int *cur_nodes) {
    if (!root)
        return 0;

    int nodes_l = 0, nodes_r = 0;
    double sum_l = cal_max_avg(root->left, max_avg, &nodes_l);
    double sum_r = cal_max_avg(root->right, max_avg, &nodes_r);

    *cur_nodes = nodes_l + nodes_r + 1;
    double tmp = (sum_l + sum_r + root->val) / *cur_nodes;
    if (tmp > *max_avg)
        *max_avg = tmp;

    return (sum_l + sum_r + root->val);
}

double maximumAverageSubtree(struct TreeNode *root) {
    double max_avg = 0;
    int nodes = 0;
    cal_max_avg(root, &max_avg, &nodes);
    return max_avg;
}
