#define MIN(a, b) (a < b ? a : b)
#define MAX(a, b) (a > b ? a : b)

int maxProduct(int* nums, int numsSize)
{
    int max = nums[0], min = nums[0], ret = nums[0];
    for (int i = 1; i < numsSize; i++) {
        int tmp_max = nums[i] * (nums[i] > 0 ? max : min);
        int tmp_min = nums[i] * (nums[i] > 0 ? min : max);
        max = MAX(tmp_max, nums[i]);
        min = MIN(tmp_min, nums[i]);
        ret = MAX(ret, max);
    }
    return ret;
}
