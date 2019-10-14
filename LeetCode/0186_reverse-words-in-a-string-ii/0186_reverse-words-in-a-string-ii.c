
void reverse(char *s, int head, int tail)
{
	while (head < tail)
	{
		char tmp = s[head];
		s[head] = s[tail];
		s[tail] = tmp;
		head++;
		tail--;
	}
}

void reverseWords(char* s, int sSize)
{     
	reverse(s, 0, sSize-1);
	int start = 0;
	for (int i = 0; i < sSize; i++)
	{
		if (i == sSize-1)
		{
			reverse(s, start, i);
			break;
		}
		if (s[i] == ' ')
		{
			reverse(s, start, i-1);
			start = i+1;
		}
	}
}

