
bool hasAlternatingBits(int n)
{
	int base = 0, res = -1;
	while (base < 31 && (0x1 << base) <= n)
	{
		int tmpRes = (n & (0x1 << base)) == 0 ? 0 : 1;
		if (res == tmpRes)
		{
			return false;
		}
		base ++;
		res = tmpRes;        
	}

	return true;
}


