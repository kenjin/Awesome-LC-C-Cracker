// Recursive function to count beautiful subsets
static int count_beautiful_subsets_handler(int* nums, int numsSize, int difference,
                                    int index, int mask)
{
    // Base case: Return 1 if mask is greater than 0 (non-empty subset)
    if (index == numsSize)
        return (mask > 0 ? 1 : 0);

    // Flag to check if the current subset is beautiful
    bool is_beautiful = true;

    // Check if the current number forms a beautiful pair with any previous
    // number in the subset
    for (int j = 0; j < index && is_beautiful; ++j)
        is_beautiful =
            ((1 << j) & mask) == 0 || abs(nums[j] - nums[index]) != difference;

    // Recursively calculate beautiful subsets including and excluding the
    // current number
    int skip = count_beautiful_subsets_handler(nums, numsSize, difference,
                                               index + 1, mask);
    if (is_beautiful)
        return skip + count_beautiful_subsets_handler(nums, numsSize, difference,
                                               index + 1, mask + (1 << index));
    else
        return skip;
}

int beautifulSubsets(int* nums, int numsSize, int k)
{
    return count_beautiful_subsets_handler(nums, numsSize, k, 0, 0);
}
