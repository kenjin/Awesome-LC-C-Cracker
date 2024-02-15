// BT recursive approach:
// Return 0 to represent that the current node has NOT been covered.
// Return 1 to represent that the current node is a camera.
// Return -1 to represent that the node has been covered by a camera or the node
// does not exist.
static int min_cam_check(struct TreeNode* root, int* ret) {
    if (!root)
        return -1;

    int left_ret = min_cam_check(root->left, ret);
    int right_ret = min_cam_check(root->right, ret);

    // Set current node as a camera if find at least one node has not been
    // covered.
    if (left_ret == 0 || right_ret == 0) {
        *ret += 1;
        return 1;
    }

    // If one of the children is set as a camera, return -1 to represent that
    // the current node has been covered; otherwise, return 0.
    return (left_ret == 1 || right_ret == 1 ? -1 : 0);
}

int minCameraCover(struct TreeNode* root) {
    int ret = 0;
    if (min_cam_check(root, &ret) == 0)
        ret += 1;

    return ret;
}
