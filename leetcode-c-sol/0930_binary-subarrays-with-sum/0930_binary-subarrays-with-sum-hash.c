/***

Approach: Hash

Using a hash map to map the occurrence of each cumulative sum, initialize 
subarr_sum_set[0] = 1 in this mapping pair. While traversing the nums 
array, for each encountered number num, add it to the cumulative sum 
tmp_sum. Then, check if there is a mapping value for tmp_sum - goal. If 
so, it implies that there are subarr_sum_set[tmp_sum-goal] subarrays that 
meet the requirements, which should be added to the result ret. If tmp_sum 
equals goal, i.e., tmp_sum - goal = 0, it indicates that from the beginning 
to the current position is exactly the required subarray.

***/

int numSubarraysWithSum(int* nums, int numsSize, int goal)
{
    int subarr_sum_set[30001] = {0}, tmp_sum = 0, ret = 0;
    subarr_sum_set[0] = 1;

    for (int i = 0; i < numsSize; i++) {
        tmp_sum += nums[i];
        if (tmp_sum - goal >= 0)
            ret += subarr_sum_set[tmp_sum - goal];
        subarr_sum_set[tmp_sum] += 1;
    }

    return ret;
}
