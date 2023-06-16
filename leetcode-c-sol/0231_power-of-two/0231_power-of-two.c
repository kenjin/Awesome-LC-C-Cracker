
bool isPowerOfTwo(int n)
{
	if (n <= 0)
	{
		return 0;
	}
	return !(n & (n-1));
}

