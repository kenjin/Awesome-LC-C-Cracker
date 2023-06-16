
int totalFruit(int* tree, int treeSize)
{
	int type[2];
	int max = 1;
	// Init first element
	type[0] = tree[0];
	type[1] = -1;
	int repeat = 0;
	int tmpLen = 1;
	for (int i = 1; i < treeSize; i++)
	{
		if ((tree[i] == tree[i-1]) ||   /* last element and current element are equal */
				(type[0] == tree[i] || type[1] == tree[i]) || /* the fruit is matched in one of buckets */
				(type[1] == -1)) /* second bucket is empty */
		{
			if (tree[i] == tree[i-1])
			{
				repeat++;
			}
			if (tree[i] != tree[i-1])
			{
				repeat = 0;
				if (type[1] == -1)
				{
					type[1] = tree[i];
				}
			}
			tmpLen++;
		} else
		{
			if (tmpLen >= max)                
			{
				max = tmpLen;    
			}
			// reset temp length and fruit type
			tmpLen = 2 + repeat;
			repeat = 0;
			type[0] = tree[i-1];
			type[1] = tree[i];
		}
	}
	if (tmpLen >= max)                
	{
		max = tmpLen;    
	} 

	return max;
}

