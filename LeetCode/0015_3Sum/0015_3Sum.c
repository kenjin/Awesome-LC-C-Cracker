/**
    Given an array nums of n integers, are there elements a, b, c in nums such
   that a + b + c = 0?
    Find all unique triplets in the array which gives the sum of zero.

    Note:
        The solution set must not contain duplicate triplets.

    Example:
        Given array nums = [-1, 0, 1, 2, -1, -4],
        A solution set is:
            [
                [-1, 0, 1],
                [-1, -1, 2]
            ]
*/
static int compare(void *a, void *b)
{
    return *(int *) a - *(int *) b;
}


#define MALLOC_UNIT 5000
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume
 * caller calls free().
 */
int **threeSum(int *nums,
               int numsSize,
               int *returnSize,
               int **returnColumnSizes)
{
    *returnSize = 0;
    if (numsSize < 3) {
        return NULL;
    }

    qsort(nums, numsSize, sizeof(int), compare);

    int count = MALLOC_UNIT, ret_sz = 0;
    int **ret = (int **) malloc(sizeof(int *) * count);
    *returnColumnSizes = malloc(sizeof(int) * count);
    for (int i = 0; i < numsSize - 2; i++) {
        /* ignore the duplicate target */
        if (i > 0 && nums[i] == nums[i - 1])
            continue;

        int target = (-1) * (nums[i]), left = i + 1, right = numsSize - 1;
        while (left < right) {
            if (left > i + 1 && nums[left - 1] == nums[left]) {
                left++;
                continue;
            }

            if (nums[left] + nums[right] == target) {
                ret_sz++;
                if (ret_sz == count) {
                    count <<= 1;
                    ret = realloc(ret, sizeof(int *) * count);
                    *returnColumnSizes =
                        realloc(*returnColumnSizes, sizeof(int) * count);
                }
                ret[ret_sz - 1] = malloc(sizeof(int) * 3);
                ret[ret_sz - 1][0] = nums[i];
                ret[ret_sz - 1][1] = nums[left];
                ret[ret_sz - 1][2] = nums[right];
                (*returnColumnSizes)[ret_sz - 1] = 3;
                left++;
            } else if (nums[left] + nums[right] < target) {
                left++;
            } else {
                /* nums[left] + nums[right] > target */
                right--;
            }
        }
    }
    *returnSize = ret_sz;
    return ret;
}
