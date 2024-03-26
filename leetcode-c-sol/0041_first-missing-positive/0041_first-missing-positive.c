/*
 * Key: Use negative number to represent that a certain index has been used.
 *
 * The range of the smallest positive integer must be between 1 and (numsSize+1)
 * 1. We first ignore negative values and 0 because they are just noise. (We
 *    assign these values to `numsSize+1`.)
 * 2. After step 1, there are no negative values, so we use negative numbers to
 *    represent that this index already has a positive integer.
 * 3. Finally, we check all the elements to find the first element that is a
 *    positive value. It means (index + 1) is the smallest positive integer.
 * 4. Otherwise, numsSize + 1 is the result when all the elements have already
 *    been transformed to negative values.
 *
 * Note: Be aware of duplicate cases. e.g. [1, 1]
 */

int firstMissingPositive(int* nums, int numsSize) {
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] <= 0)
            nums[i] = numsSize + 1;
    }

    for (int i = 0; i < numsSize; i++) {
        int cur = abs(nums[i]);
        if (cur <= numsSize && nums[cur - 1] > 0)
            nums[cur - 1] *= -1;
    }

    int ret = numsSize + 1;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > 0) {
            ret = i + 1;
            break;
        }
    }
    return ret;
}
