/**
153. Find Minimum in Rotated Sorted Array [M]
Ref: https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/

Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e.,  [0,1,2,4,5,6,7] might become  [4,5,6,7,0,1,2]).

Find the minimum element.

You may assume no duplicate exists in the array.

Example 1:
Input: [3,4,5,1,2]
Output: 1

Example 2:
Input: [4,5,6,7,0,1,2]
Output: 0

 */

int findMin(int* nums, int numsSize)
{
    int head = 0, tail = numsSize - 1;
    while (head < tail) {
        int pivot = head + ((tail - head) >> 1);
        if (head == pivot || tail == pivot) {
            return (nums[head] < nums[tail] ? nums[head] : nums[tail]);
        }

        if (nums[pivot] > nums[head] && nums[pivot] > nums[tail]) {
            // pivot is at right side
            // ex: [3, 4, 5, 1, 2]
            //      ^     ^     ^
            //      H     P     T
            head = pivot;
        } else {
            // pivot is at left side
            // ex: [1, 2, 3, 4, 5] or [5, 1, 2, 3, 4]
            //      ^     ^     ^      ^     ^     ^
            //      H     P     T      H     P     T
            tail = pivot;
        }
    }

    return nums[tail];
}
