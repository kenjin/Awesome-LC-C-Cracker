#define MAX(a, b) (a > b ? a : b)

static int compare(const void* a, const void* b) { return *(int*)a - *(int*)b; }

/*
 * Sort all elements first, then use a greedy approach to determine whether the
 * sum of the previous edge lengths is greater than this edge length, starting from
 * the third edge length.
 */
long long largestPerimeter(int* nums, int numsSize) {
    // Constraints:
    // 3 <= n <= 10^5
    // 1 <= nums[i] <= 10^9
    qsort(nums, numsSize, sizeof(int), compare);
    long long ret = -1;
    long long sum = nums[0] + nums[1];
    int last_idx = 2;
    while (last_idx < numsSize) {
        if (sum > nums[last_idx])
            ret = MAX(ret, sum + nums[last_idx]);
        sum += nums[last_idx];
        last_idx++;
    }

    return ret;
}
