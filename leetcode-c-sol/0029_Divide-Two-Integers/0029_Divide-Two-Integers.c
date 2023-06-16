/**
29. Divide Two Integers [M]
Ref: https://leetcode.com/problems/divide-two-integers/

Given two integers dividend and divisor, divide two integers without using multiplication, division and mod operator.

Return the quotient after dividing dividend by divisor.

The integer division should truncate toward zero.

Example 1:
Input: dividend = 10, divisor = 3
Output: 3

Example 2:
Input: dividend = 7, divisor = -3
Output: -2

Note:
Both dividend and divisor will be 32-bit signed integers.
The divisor will never be 0.
Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range: [−231,  231 − 1]. For the purpose of this problem, assume that your function returns 231 − 1 when the division result overflows.

 */

/**
 *     32/3  
 *      3 (3 << 0)
 *      6 (3 << 1)
 *     12
 *     24
 *     48  => "48 > 32" => 32-24=8
 *----------------------------------
 *      8/3
 *      3
 *      6
 *     12  => "12 > 8" => 8-6=2
 *----------------------------------
 *      2/3  => "2 < 3" => return 
 *         
 *   32/3 = (24+6+2)/3 = (8+2+0)/3 => 2^3 + 2^1 = 10
 */
int divide(int dividend, int divisor)
{
	/* edge case */
	if (divisor == 0)
	{
		return INT_MIN;
	}
	if (dividend == INT_MIN)
	{
		if (divisor == 1)
		{
			return INT_MIN;
		} else if (divisor == -1)
		{
			return INT_MAX;
		}
	}
	/* use long type to avoid int overflow */
	long divd = (long)dividend;
	long divs = (long)divisor;

	/* negative case */
	int sign = 0;
	if (divd < 0)
	{
		sign ^= 1;
		divd *= -1;
	}
	if (divs < 0)
	{
		sign ^= 1;
		divs *= -1;
	}

	int shift = 0;
	int ret = 0;
	while (divd >= divs)
	{        
		shift++;
		long tmp = divs << shift;
		if (tmp > divd)
		{
			divd = divd - (divs << (shift-1));
			ret += (1 << (shift-1));
			shift = 0;
		}
	}

	return (sign == 0 ? ret : ret*(-1));
}


