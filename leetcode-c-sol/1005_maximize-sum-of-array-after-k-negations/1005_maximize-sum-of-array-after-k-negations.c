
static int compare(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int largestSumAfterKNegations(int* nums, int numsSize, int k)
{
    qsort(nums, numsSize, sizeof(int), compare);

    // Calculate total sum and find the count of negative
    int neg_ctr = 0, sum = 0;
    for (int i = 0; i < numsSize; i++) {
        sum += nums[i];
        if (nums[i] < 0) {
            neg_ctr++;
        }
    }

    // Process all the negative
    int i = 0;
    while (neg_ctr > 0 && k > 0) {
        nums[i] *= -1;
        sum = sum + nums[i]*2;
        neg_ctr--;
        k--;
        i++;
    }

    // Process the rest of positive, if k is a single value, choose the smallest positive element.
    if (k % 2) {
        int min = INT_MAX;
        for (int x = neg_ctr; x < numsSize; x++) {
            min = (min < nums[x] ? min : nums[x]);
        }
        sum = sum - min*2;    
    }
    return sum;
}
