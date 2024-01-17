#define MAX(a, b) (a > b ? a : b)
int jump(int* nums, int numsSize)
{
    int farthest = 0, last = 0, ctr = 0;
    for (int i = 0; i < numsSize - 1; i++) {
        farthest = MAX(farthest, i + nums[i]);
        if (i == last) {
            last = farthest;
            ctr++;
        }
    }

    return ctr;
}
