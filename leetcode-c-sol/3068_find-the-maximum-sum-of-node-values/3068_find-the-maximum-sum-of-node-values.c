long long maximumValueSum(int *nums, int nums_size, int k, int **edges, int edges_size, int *edges_col_size)
{
    long long max_sum = 0;
    int changed_count = 0, min_change_diff = INT_MAX;

    for (int i = 0; i < nums_size; ++i) {
        int num = nums[i];
        int xor_num = num ^ k;
        max_sum += (num > xor_num) ? num : xor_num;
        if (xor_num > num)
            changed_count++;

        int change_diff = abs(num - xor_num);
        if (change_diff < min_change_diff)
            min_change_diff = change_diff;
    }

    if (!(changed_count & 0x1))
        return max_sum;

    return max_sum - min_change_diff;
}
