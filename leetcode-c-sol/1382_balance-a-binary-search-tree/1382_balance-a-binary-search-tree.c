static struct TreeNode* create_bst(struct TreeNode** nums, int head, int tail) {
    if (head < 0 || head > tail)
        return NULL;

    int mid = head + ((tail - head) >> 1);
    nums[mid]->left = create_bst(nums, head, mid - 1);
    nums[mid]->right = create_bst(nums, mid + 1, tail);
    return nums[mid];
}

static void get_sorted_arr(struct TreeNode* root, struct TreeNode** nums,
                           int* idx) {
    if (!root)
        return;
    get_sorted_arr(root->left, nums, idx);
    nums[*idx] = root;
    *idx += 1;
    get_sorted_arr(root->right, nums, idx);
}

struct TreeNode* balanceBST(struct TreeNode* root) {
    struct TreeNode* nums[10000];
    int num_sz = 0;
    get_sorted_arr(root, nums, &num_sz);
    return create_bst(nums, 0, num_sz - 1);
}
