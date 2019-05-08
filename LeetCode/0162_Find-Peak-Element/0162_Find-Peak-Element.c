/**
162. Find Peak Element

Ref: https://leetcode.com/problems/find-peak-element/

 */

int findPeakElement(int* nums, int numsSize)
{
	int head = 0;
	int tail = numsSize-1;

	while (head < tail)
	{
		int mid = head + (tail-head)/2;
		/*
		 *                 O
		 *     ? ? ? ? ? O   ? ? ... 
		 *    O                      O
		 *    ^(n[-1])   ^(n[mid])   ^(n[size])
		 */
		if (nums[mid] <= nums[mid+1])
		{
			/* Peak must be in the right side, so update the head */
			head = mid+1;
		} 
		/*
		 *               O
		 *     ? ? ? ? ?   O ? ? ... 
		 *    O                      O
		 *    ^(n[-1])   ^(n[mid])   ^(n[size])
		 */
		else /* (nums[mid] > nums[mid+1]) */
		{
			/* Peak must be in the left side, so update the tail */
			tail = mid;
		}
	}
	return head;
}
