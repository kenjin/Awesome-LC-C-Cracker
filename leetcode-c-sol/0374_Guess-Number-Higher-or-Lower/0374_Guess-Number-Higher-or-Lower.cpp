/**

374. Guess Number Higher or Lower [E]
Ref: https://leetcode.com/problems/guess-number-higher-or-lower/

*/

// Forward declaration of guess API.
// @param num, your guess
// @return -1 if my number is lower, 1 if my number is higher, otherwise return 0
int guess(int num);

class Solution {
	public:
		int guessNumber(int n) 
		{
			int head = 1;
			int tail = n;

			while (1)
			{
				int mid = tail+(head-tail)/2;

				if (guess(mid) == -1)
				{
					tail = mid-1;
				} else if (guess(mid) == 1)
				{
					head = mid+1;
				} else
				{
					return mid;
				}
			}      
		}
};
