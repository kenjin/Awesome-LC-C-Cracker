int addDigits(int num)
{
	int ret = 0;        
	while (num/10)
	{
		ret += num%10;
		num /= 10;
	}
	ret += num%10;
	return ret;
}

int sumOfDigits(int* A, int ASize)
{
	int min = A[0];
	for (int i = 1; i < ASize; i++)
	{
		min = (min < A[i] ? min : A[i]);
	}

	return ((addDigits(min) & 0x1) != 0x1);
}


