void rotate(int* nums, int numsSize, int k)
{
    // edge cases: no need for movement
    if (numsSize == 1 || (k % numsSize) == 0)
        return;

    int cur_val = nums[0], cur_idx = 0, start_idx = 0;
    for (int swap_ctr = 0; swap_ctr < numsSize; swap_ctr++) {
        int tmp_idx = (cur_idx + k) % numsSize;
        int tmp_val = nums[tmp_idx];
        nums[tmp_idx] = cur_val;
        cur_val = tmp_val;
        cur_idx = tmp_idx;
        // Once cur_idx reaches the position of start_idx, increment the 
        // start_idx by 1, and then assign it back to cur_idx. This way, the 
        // position of cur_idx is also changed, allowing the swapping process 
        // to continue.
        if (cur_idx == start_idx) {
            start_idx++;
            cur_idx = start_idx;
            cur_val = nums[start_idx];
        }
    }
}
