/***

Approach: Prefix Sum + Hash

Hash Table Initialization: The program initializes a hash table called sum_hash
to store the cumulative sums encountered during the iteration through the nums
array. The size of the hash table is determined by ((numsSize << 1) + 1), where
numsSize is the size of the nums array.

Hashing the Cumulative Sums: It then iterates through the nums array,
maintaining a cumulative sum (cur_sum). For each element in nums, it decrements
cur_sum by 1 if the current element is 0, otherwise increments it by 1. This
step is crucial as it allows us to treat zeros as -1 when calculating the
cumulative sum.

Mapping Cumulative Sums to Indices: The program then maps each unique cumulative
sum encountered during the iteration to its corresponding index in the sum_hash
table. This mapping is stored in the tmp array, which is essentially an offset
from the midpoint of the sum_hash table.

Finding Maximum Length of Contiguous Array: During the iteration, if the current
cumulative sum (cur_sum) is encountered for the first time (indicated by
tmp[cur_sum] == -1), and cur_sum is not zero, its index is stored in the tmp
array. If the same cumulative sum is encountered again, it calculates the length
of the contiguous array by subtracting the current index from the index stored
in tmp. The maximum length encountered so far is updated accordingly.


Time: O(n)
Space:: O(n)

***/

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int findMaxLength(int* nums, int numsSize) {
    int* sum_hash = malloc(sizeof(int) * ((numsSize << 1) + 1));
    memset(sum_hash, 0xFF, ((numsSize << 1) + 1) * sizeof(int));
    // trick: move to the middle to cover negative current sum
    int* tmp = &sum_hash[numsSize];
    int ret = 0, cur_sum = 0;
    for (int i = 0; i < numsSize; i++) {
        cur_sum = (nums[i] == 0 ? cur_sum - 1 : cur_sum + 1);
        if (tmp[cur_sum] == -1 && cur_sum != 0)
            tmp[cur_sum] = i;
        else
            ret = MAX(ret, i - tmp[cur_sum]);
    }

    free(sum_hash);
    return ret;
}

