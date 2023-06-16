
int maxArea(int* height, int heightSize)
{
	int head = 0;
	int tail = heightSize-1;
	int max = 0;
	while (head < tail)
	{
		if (height[head] < height[tail])
		{
			max = height[head]*(tail-head) > max ? height[head]*(tail-head) : max;
			head++;
		} else
		{
			max = height[tail]*(tail-head) > max ? height[tail]*(tail-head) : max;
			tail--;   
		}
	}
	return max;
}
