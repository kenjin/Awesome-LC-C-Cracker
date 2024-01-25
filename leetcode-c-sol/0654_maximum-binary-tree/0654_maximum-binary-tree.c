struct TreeNode* builder(int* nums, int head, int tail)
{
    if (head > tail)
        return NULL;

    int max_idx = head;
    for (int i = head + 1; i <= tail; i++) {
        if (nums[i] > nums[max_idx])
            max_idx = i;
    }

    struct TreeNode *node = malloc(sizeof(struct TreeNode));
    node->val = nums[max_idx];
    node->left = builder(nums, head, max_idx - 1);
    node->right = builder(nums, max_idx + 1, tail);
    return node;
}

struct TreeNode* constructMaximumBinaryTree(int* nums, int numsSize)
{
    return builder(nums, 0, numsSize-1);
}
