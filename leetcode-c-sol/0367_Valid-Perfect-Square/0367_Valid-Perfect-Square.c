/**

367. Valid Perfect Square [E]

Ref: https://leetcode.com/problems/valid-perfect-square/

 */

bool isPerfectSquare(int num)
{
	/* Given a positive integer num */
	if (num <= 0)
	{
		return false;
	} else if (num == 1)
	{
		return true;
	}

	int head = 0;
	int tail = num;
	while (head < tail)
	{
		int mid = head + (tail-head)/2;

		int cur = num/mid;
		if (cur < mid)
		{
			tail = mid-1;
		} else if (cur > mid)
		{
			head = mid+1;
		} else 
		{
			if (cur*mid != num)
			{
				return false;
			} else
			{
				return mid;
			}
		}
	}

	if (head*head == num)
	{
		return true;
	} else
	{
		return false;
	}
}
