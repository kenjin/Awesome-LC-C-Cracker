
bool isStrobogrammatic(char * num)
{
	int convert[] = {0, 1, -1, -1, -1, -1, 9, -1, 8, 6};
	int len = strlen(num);
	int l = 0, r = len - 1;
	/* Validate the case within odd string len, check the mid element at first */
	if (len & 0x1) {
		int mid = len >> 1;
		if (num[mid] != '0' && num[mid] != '1' && num[mid] != '8')
			return false;
	}
	while (l < r) {
		if (convert[num[l] - '0'] != num[r] - '0')            
			return false;
		l++;
		r--;
	}

	return true;
}
