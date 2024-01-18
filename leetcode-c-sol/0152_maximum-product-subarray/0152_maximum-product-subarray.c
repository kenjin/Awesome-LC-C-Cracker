
#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)

int maxProduct(int* nums, int numsSize)
{
    int dp_pos = nums[0], dp_neg = nums[0], ret = nums[0];
    for (int i = 1; i < numsSize; i++) {
        int tmp1 = nums[i] * dp_pos;
        int tmp2 = nums[i] * dp_neg;
        if (tmp1 > tmp2){
            dp_pos = MAX(tmp1, nums[i]);
            dp_neg = MIN(tmp2, nums[i]);
        } else {
            dp_pos = MAX(tmp2, nums[i]);
            dp_neg = MIN(tmp1, nums[i]);
        }
        ret = MAX(ret, dp_pos);
    }
    return ret;
}
