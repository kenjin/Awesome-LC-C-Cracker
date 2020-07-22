
static int compare(const void *a, const void *b)
{
    return *(int *) a - *(int *) b;
}

int threeSumClosest(int *nums, int numsSize, int target)
{
    int min = INT_MAX;
    int ret = target;
    qsort(nums, numsSize, sizeof(int), compare);
    for (int i = 0; i + 2 < numsSize; i++) {
        int head = i + 1, tail = numsSize - 1;
        while (tail - head >= 1) {
            int sum = nums[i] + nums[head] + nums[tail];
            int com = abs(sum - target);
            if (com < min) {
                min = com;
                ret = sum;
            }

            if (sum < target)
                head++;
            else if (sum > target)
                tail--;
            else
                return target;
        }
    }

    return ret;
}
