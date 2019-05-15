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

int getSum(int a, int b)
{
	unsigned int base = 0x1;
	unsigned int carry = 0;
	unsigned int sum = 0;
	for (int i = 0; i < 32; i++)
	{
		unsigned int tmpA = (base << i) & (unsigned int)a;
		unsigned int tmpB = (base << i) & (unsigned int)b;
		sum  += (tmpA ^ tmpB) ^ (carry << i);
		if ((tmpA != 0 && (tmpA ^ tmpB) == 0) /* tmpA and tmpB are > 0 */ || 
				((tmpA ^ tmpB) > 0 && carry == 1))
		{
			carry = 1;
		} else
		{
			carry = 0;
		}
	}
	return sum;
}
