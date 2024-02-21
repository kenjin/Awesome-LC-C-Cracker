/***

A longest nice subarray means the related bit ONLY occurs once.

Therefore, we use a mask to record which bits have appeared only once in the
previous longest nice subarray. Utilizing a sliding window (head/tail), we start
scanning each element in the array to determine the longest nice subarray ending
at the current element (tail):

- If there is no intersection with the mask (indicating we found a subarray
  where we can include the current tail element to extend it),
- Otherwise, we need to move the head index forward and update the mask to
  exclude bits that have appeared in nums[head], until we find the longest nice
  subarray ending at the current element. (The worst-case scenario is when the
  head moves to the tail, at which point the mask will also be zero)
- Update the mask in each round to include the tail element and record the
  current maximum length.

***/

#define MAX(a, b) (a > b ? a : b)

int longestNiceSubarray(int* nums, int numsSize) {
    int mask = 0, ret = 0, len = 0;
    for (int head = 0, tail = 0; tail < numsSize; tail++) {
        while (0 != (nums[tail] & mask)) {
            mask &= ~(nums[head]);
            head++;
        }
        mask |= nums[tail];
        ret = MAX(ret, tail - head + 1);
    }

    return ret;
}
