/**

67. Add Binary [E]

Ref: https://leetcode.com/problems/add-binary/

 */


int calSum(char *ret, int retCtr, char *a, int idxA, char *b, int idxB, int carry)
{
	int tmp;
	if (b != NULL)
	{
		tmp = (a[idxA]-'0') + (b[idxB]-'0')  + carry;
	} else
	{
		tmp = (a[idxA]-'0') + carry;
	}
	carry = ((tmp & 0x2) != 0) ? 1 : 0;
	ret[retCtr] = (tmp & 0x1 != 0) ? '1' : '0';
	return carry;
}

void reverseStr(char *ret, int head, int tail)
{
	while (head < tail)
	{
		char tmp = ret[head];
		ret[head] = ret[tail];
		ret[tail] = tmp;
		head++;
		tail--;
	}
}

char * addBinary(char * a, char * b)
{   
	int idxA = strlen(a)-1;
	int idxB = strlen(b)-1;
	int maxLen = idxA > idxB ? idxA : idxB;
	char *ret = calloc(maxLen+3 /* '\0' and 'carry' and 'index2len' */, sizeof(char));
	int ctr = 0;
	int carry = 0;
	while (idxA >= 0 && idxB >= 0)
	{
		carry = calSum(ret, ctr, a, idxA, b, idxB, carry);
		ctr++;
		idxA--;
		idxB--;
	}
	/* Check the ramining */
	while (idxA >= 0)
	{
		carry = calSum(ret, ctr, a, idxA, NULL, 0, carry);
		ctr++;
		idxA--;
	}
	while (idxB >= 0)
	{
		carry = calSum(ret, ctr, b, idxB, NULL, 0, carry);
		ctr++;
		idxB--;
	}
	/* Check the carry bit */
	if (carry)
	{
		ret[ctr] = '1';
		ctr++;
	}
	/* reverse string */
	reverseStr(ret, 0, ctr-1);

	return ret;
}
