/**

277. Find the Celebrity [M]
Ref: https://leetcode.com/problems/find-the-celebrity/

 */
// Forward declaration of the knows API.
bool knows(int a, int b);

int findCelebrity(int n) 
{
	int ret = 0;
	for (int i = 0; i < n; i++)
	{
		/* Find the only candidate */
		ret = knows(i, ret) ? ret : i;
	}
	/* Verify candidate */
	for (int i = 0; i < n; i++)
	{
		if (ret != i &&
				(knows(ret, i) || !knows(i, ret))
		   )
		{
			return -1;
		}
	}
	return ret;
}
