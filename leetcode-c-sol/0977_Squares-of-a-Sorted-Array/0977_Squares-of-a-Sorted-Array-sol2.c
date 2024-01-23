/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortedSquares(int* nums, int numsSize, int* returnSize)
{
    int *ret = malloc(sizeof(int)*numsSize);
    *returnSize = numsSize;

    int head = 0, tail = numsSize-1, k = numsSize-1;
    while (k >= 0) {
        if (nums[head]*nums[head] > nums[tail]*nums[tail]) {
            ret[k--] = nums[head] * nums[head];
            head++;
        } else {
            ret[k--] = nums[tail] * nums[tail];
            tail--;
        }
    }
    return ret;
}
