/**

494. Target Sum [Medium]

You are given a list of non-negative integers, a1, a2, ..., an, and a 
target, S. Now you have 2 symbols + and -. For each integer, you 
should choose one from + and - as its new symbol.

Find out how many ways to assign symbols to make sum of integers equal
to target S.

Example 1:

Input: nums is [1, 1, 1, 1, 1], S is 3.
Output: 5
Explanation:

-1+1+1+1+1 = 3
+1-1+1+1+1 = 3
+1+1-1+1+1 = 3
+1+1+1-1+1 = 3
+1+1+1+1-1 = 3

There are 5 ways to assign symbols to make the sum of nums be target 3.

Note:
The length of the given array is positive and will not exceed 20.
The sum of elements in the given array will not exceed 1000.
Your output answer is guaranteed to be fitted in a 32-bit integer.

 */

void calSum(int *nums, int head, int tail, long target, int *ret)
{
    if (head > tail)
    {
        if (target == 0)
        {
            *ret += 1;
        }
        return;
    }

    long curNum = (long)nums[head];
    /* "+" symbol case */
    calSum(nums, head+1, tail, target-curNum, ret);
    /* "-" symbol case */
    curNum = curNum*(-1);
    calSum(nums, head+1, tail, target-curNum, ret);

}

int findTargetSumWays(int* nums, int numsSize, int S)
{
    if (numsSize == 0)
    {
        return 0;
    }

    int ret = 0;
    calSum(nums, 0, numsSize-1, (long)S, &ret);

    return ret;
}
