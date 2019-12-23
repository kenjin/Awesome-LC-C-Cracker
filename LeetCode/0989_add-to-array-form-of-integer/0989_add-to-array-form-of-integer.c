
void reverse(int *n, int head, int tail)
{
	while (head < tail)
	{
		int tmp = n[head];
		n[head] = n[tail];
		n[tail] = tmp;        
		head++;
		tail--;
	}
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* addToArrayForm(int* A, int ASize, int K, int* returnSize)
{
	int *ret = malloc(sizeof(int)*10001);
	int retCtr = 0;
	int addIdx = ASize-1;
	int carry = 0;
	while (K > 0)
	{
		int tmp = 0;
		if (addIdx >= 0)
		{
			tmp = A[addIdx];
			addIdx--;                        
		}
		ret[retCtr] = tmp + (K % 10) + carry;        
		carry = ret[retCtr]/10;        
		ret[retCtr] = ret[retCtr] % 10;
		K /= 10;
		retCtr++;        
	}

	while (addIdx >= 0)
	{
		ret[retCtr] = A[addIdx] + carry;
		carry = ret[retCtr]/10;
		ret[retCtr] = ret[retCtr] % 10;
		addIdx--;
		retCtr++;        
	}

	if (carry)
	{
		ret[retCtr] = 1;
		retCtr++;
	}

	ret = realloc(ret, sizeof(int)*retCtr);
	*returnSize = retCtr;    
	reverse(ret, 0, retCtr-1);
	return ret;
}

