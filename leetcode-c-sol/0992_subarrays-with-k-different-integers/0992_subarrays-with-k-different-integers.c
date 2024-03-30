static int subarr_at_most_distinct_k(int* nums, int numsSize, int k) {
    int l = 0, ret = 0;
    int set[20001] = {0};
    for (int r = 0; r < numsSize; r++) {
        set[nums[r]] += 1;
        // Update distinct ctr
        if (set[nums[r]] == 1)
            k--;
        // Move left idx of window until distinct ctr is at most k
        while (k < 0) {
            set[nums[l]] -= 1;
            if (set[nums[l]] == 0)
                k++;
            l++;
        }
        ret += (r - l + 1);
    }
    return ret;
}

int subarraysWithKDistinct(int* nums, int numsSize, int k) {
    // Calculate separately the number of subarrays with at most K different
    // numbers, and the number of subarrays with at most K-1 different numbers.
    // Subtract the latter from the former to obtain the count of subarrays with
    // exactly K different numbers.
    return subarr_at_most_distinct_k(nums, numsSize, k) -
           subarr_at_most_distinct_k(nums, numsSize, k - 1);
}
