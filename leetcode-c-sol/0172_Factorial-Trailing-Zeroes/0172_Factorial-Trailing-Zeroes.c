/**
172. Factorial Trailing Zeroes [E]
Ref: https://leetcode.com/problems/factorial-trailing-zeroes/

Given an integer n, return the number of trailing zeroes in n!.

Example 1:
Input: 3
Output: 0
Explanation: 3! = 6, no trailing zero.

Example 2:
Input: 5
Output: 1
Explanation: 5! = 120, one trailing zero.

Note: Your solution should be in logarithmic time complexity.

 */
int trailingZeroes(int n)
{
	double max5 = 1;
	int ctr = 0;
	while (max5*5 <= n)
	{
		max5 *= 5;        
		ctr++;
	}

	int sum = 0;
	for (int x = 0; x < ctr; x++)
	{
		sum += (n/max5);
		max5 /=5 ;
	}
	return sum;
}
