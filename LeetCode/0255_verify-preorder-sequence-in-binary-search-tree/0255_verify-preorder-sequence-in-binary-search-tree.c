bool verifyPreorderHelper(int *arr, int head, int tail)
{
	if (head >= tail)
	{
		return true;
	}

	int curRoot = arr[head];    
	// lt
	int chkIdx = head+1;
	while (chkIdx <= tail)
	{
		if (arr[chkIdx] > curRoot)
		{
			break;
		}
		chkIdx++;
	}    
	bool lRet = verifyPreorderHelper(arr, head+1, chkIdx-1);
	if (!lRet)
	{
		return false;
	}    
	// gt
	int maxIdx = chkIdx;
	while (maxIdx <= tail)
	{
		if (arr[maxIdx] < curRoot)
		{
			return false;
		}
		maxIdx++;
	}

	return verifyPreorderHelper(arr, chkIdx, tail);    
}

bool verifyPreorder(int* preorder, int preorderSize)
{
	if (!preorderSize)
	{
		return true;
	}
	return verifyPreorderHelper(preorder, 0, preorderSize-1);    
}

