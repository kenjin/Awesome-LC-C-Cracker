/**

69. Sqrt(x) [Easy]

Ref: https://leetcode.com/problems/sqrtx/

*/

int mySqrt(int x)
{
	/* x is guaranteed to be a non-negative integer. */
	if (x == 0)
	{
		return 0;
	}

	int head = 0;
	int tail = x;
	int mid = 0;
	while (1)
	{
		mid = (head+tail)/2;
		if (mid == 0)
		{
			/* Avoid devide by 0 */
			return 1;
		}

		if (x/mid < mid)
		{
			tail = mid-1;
		} else
		{
			if (mid+1 > x/(mid+1))
			{
				return mid;
			}
			head = mid+1;
		}
	}
}
