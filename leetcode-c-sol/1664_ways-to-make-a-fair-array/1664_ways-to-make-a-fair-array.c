
int waysToMakeFair(int* nums, int numsSize)
{
    // odd_prefix_sum[i]: sum of odd-indexed elements from index 0 to index i
    // even_prefix_sum[i]: sum of even-indexed elements from index 0 to index i
    int *odd_prefix_sum = malloc(sizeof(int) * numsSize);
    int *even_prefix_sum = malloc(sizeof(int) * numsSize);

    odd_prefix_sum[0] = 0;
    even_prefix_sum[0] = nums[0];
    for (int i = 1; i < numsSize; i++) {
        if (i & 0x1) {
            odd_prefix_sum[i] = odd_prefix_sum[i-1] + nums[i];
            even_prefix_sum[i] = even_prefix_sum[i-1];
        } else {
            odd_prefix_sum[i] = odd_prefix_sum[i-1];
            even_prefix_sum[i] = even_prefix_sum[i-1] + nums[i];
        }
    }

    int ret = 0;
    // pivot:0
    if (even_prefix_sum[numsSize - 1] - even_prefix_sum[0] == odd_prefix_sum[numsSize - 1] - odd_prefix_sum[0])
        ret++;
    // pivot: from 1 to (numsSize - 1)
    for (int pivot = 1; pivot < numsSize; pivot++) {
        // After removing the pivot element, the odd/even prefix sums of the right half side will be swapped.
        // That is, right half odd_prefix_sum(odd_sum_r) actually represents the sum of even-indexed elements.
        int even_sum_r = even_prefix_sum[numsSize - 1] - even_prefix_sum[pivot];
        int odd_sum_r = odd_prefix_sum[numsSize - 1] - odd_prefix_sum[pivot];
        if (odd_prefix_sum[pivot - 1] + even_sum_r == even_prefix_sum[pivot - 1] + odd_sum_r)
            ret++;
    }

    free(odd_prefix_sum);
    free(even_prefix_sum);
    return ret;
}
