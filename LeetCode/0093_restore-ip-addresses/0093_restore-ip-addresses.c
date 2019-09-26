
void restoreIpAddressesHelper(char *s, int slen, int sIdx, int lv, int *ip, char ***ret, int *retSize)
{
	if (lv == 4)
	{
		if (sIdx == slen)
		{
			*ret = realloc(*ret, sizeof(char *)*(*retSize + 1));
			(*ret)[*retSize] = calloc(16, sizeof(char));
			sprintf((*ret)[*retSize], "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
			*retSize += 1;            
		}
		return;
	}

	int sum = 0;
	int baseCtr = 0; /* Max count to 3(0 ~ 255)*/
	while (s[sIdx] && baseCtr < 3)
	{
		sum *= 10;
		sum += s[sIdx] - '0';        
		sIdx++;
		if (0 <= sum && sum <= 255 && 
				slen-sIdx <= (3-lv)*3)
		{
			ip[lv] = sum;
			restoreIpAddressesHelper(s, slen, sIdx, lv+1, ip, ret, retSize);
		}

		// Check that number cannot be 0 prefixed
		if (baseCtr == 0 && sum == 0)
		{
			break;
		}
		baseCtr++;
	}
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** restoreIpAddresses(char * s, int* returnSize)
{
	char **ret = malloc(sizeof(char *));
	*returnSize = 0;

	int len = strlen(s);       
	int ip[4] = {0};
	restoreIpAddressesHelper(s, len, 0, 0, ip, &ret, returnSize);

	return ret;
}


