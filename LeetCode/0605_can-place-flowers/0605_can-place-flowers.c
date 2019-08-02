
bool canPlaceFlowers(int* flowerbed, int flowerbedSize, int n)
{
	int flowerCtr = 0;
	// trick init, consider [0, 0, 1,...] case
	// => we can put flower at first even though two '0' in the beginning
	int start = -2; 
	for (int i = 0; i < flowerbedSize; i++)
	{
		if (flowerbed[i])
		{
			//printf("start=%d, cur=%d.  total=%d\n", start, i, (i-start-2)/2);
			flowerCtr += (i-start-2)/2;
			start = i;   
		}

		if (n <= flowerCtr)
		{
			return true;
		}
	}

	// "flowerbedSize+1" is also a trick, consider [...1, 0, 0] case
	// => We can put flower even though two '0' in the end
	flowerCtr += (flowerbedSize+1-start-2)/2;

	return (flowerCtr >= n ? true: false);
}


