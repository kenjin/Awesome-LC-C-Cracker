/***

Approach: Sliding Window

Define two functions: one to calculate the number of subarrays with at most K
odd numbers and another to calculate the number of subarrays with at most K-1
odd numbers. The difference between these two results will give us the number of
subarrays with exactly K odd numbers. This works because any subarray with
exactly K odd numbers is included in the count of subarrays with at most K odd
numbers but excluded from the count of subarrays with at most K-1 odd numbers.

This sliding window approach ensures that we do not have to iterate through all
possible subarrays, which would be computationally expensive. Instead, we
maintain a window that adjusts dynamically to include or exclude elements based
on the number of odd numbers it contains.

***/

// Function to calculate the number of subarrays with at most k odd numbers
static int at_most(int* nums, int nums_size, int k) {
    int res = 0, left = 0;
    for (int i = 0; i < nums_size; ++i) {
        k -= nums[i] & 0x1;
        while (k < 0)
            k += nums[left++] & 0x1;
        res += i - left + 1;
    }
    return res;
}

int numberOfSubarrays(int* nums, int nums_size, int k) {
    return at_most(nums, nums_size, k) - at_most(nums, nums_size, k - 1);
}
