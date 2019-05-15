/**
371. Sum of Two Integers [E]
Ref: https://leetcode.com/problems/sum-of-two-integers/

Calculate the sum of two integers a and b, but you are not allowed to use the operator + and -.

Example 1:
Input: a = 1, b = 2
Output: 3

Example 2:
Input: a = -2, b = 3
Output: 1

 */

/*
 * 011     110     0100     01000    "1000"
 * 101 => 0010 => 00100 => 000000 =>     0
 *
 * getSum(3,5) => getSum(6,2) => getSum(4,4) => getSum(8,0) => Ans=8
 */
int getSum(int a, int b)
{
	if (b == 0)
	{
		return a;
	}
	unsigned int sum = a ^ b;
	/* &0x7ffffffff: Clear most significant bit to avoid INT_MIN left shift case */
	unsigned int carry = (a & b & 0x7ffffffff) << 1;
	return getSum(sum, carry);
}
