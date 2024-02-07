/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int* nextGreaterElements(int* nums, int numsSize, int* returnSize) {
    // Simple stack structure
    int* stack = malloc(sizeof(int) * numsSize);
    int s_ctr = 0;

    // Init ret
    int* ret = malloc(sizeof(int) * numsSize);
    *returnSize = numsSize;
    for (int i = 0; i < numsSize; i++)
        ret[i] = -1;

    // Check next greater element via monotonic stack
    for (int i = 0; i < numsSize; i++) {
        while (s_ctr > 0) {
            int top_idx = stack[s_ctr - 1];
            if (nums[top_idx] >= nums[i])
                break;

            ret[top_idx] = nums[i];
            s_ctr--;
        }
        stack[s_ctr++] = i;
    }

    // Check wrap-around elements (from the 1st to the "n-1"th)
    for (int i = 0; i < numsSize - 1; i++) {
        while (s_ctr > 0) {
            int top_idx = stack[s_ctr - 1];
            if (nums[top_idx] >= nums[i])
                break;

            ret[top_idx] = nums[i];
            s_ctr--;
        }
    }
    return ret;
}
