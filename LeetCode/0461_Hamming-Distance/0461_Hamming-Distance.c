/**

461. Hamming Distance [E]
Ref: https://leetcode.com/problems/hamming-distance/

 */

int hammingDistance(int x, int y)
{
	int diff = x ^ y;
	int ret = 0;
	for (int i = 0; i < 32; i++)
	{
		if (diff & ((unsigned int)0x1 << i))
		{
			ret++;
		}
	}
	return ret;
}
