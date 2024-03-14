/**
 * Approach: Sliding Window
 *
 * Utilizes the concept of prefix sum. However, this sum isn't the sum from
 * the beginning to the current position, but rather the sum within the
 * sliding window. Whenever the sum within this sliding window equals the
 * goal, it constitutes a valid subarray according to the problem.
 * 
 * Traverse the nums array, adding the current digit to the sum. If the sum
 * exceeds the goal at any point, it requires shrinking the window by moving
 * the left to the right and subtracting the digit removed from the window until
 * the sum is less than or equal to goal, if the sum is less than the goal,
 * it implies that there is no subarray whose sum equals the goal. If the
 * sum equals the goal, increment the result (ret) by 1. Another scenario
 * to consider is when there are consecutive zeros on the left side of the
 * window. Zeros don't affect the sum, but each zero contributes to a
 * distinct subarray. Hence, it's necessary to count the number of consecutive
 * zeros from the left.
 */

int numSubarraysWithSum(int* nums, int numsSize, int goal)
{
    int ret = 0, sum = 0, left = 0;
    for (int right = 0; right < numsSize; right++) {
        sum += nums[right];
        if (sum < goal)
            continue;

        while (left < right && sum > goal)
            sum -= nums[left++];

        if (sum == goal)
            ret++;
        for (int j = left; j < right && nums[j] == 0; j++)
            ret++;
    }
    return ret;
}
