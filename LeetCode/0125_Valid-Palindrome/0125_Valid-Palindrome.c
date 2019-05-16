/**

125. Valid Palindrome [E]
Ref: https://leetcode.com/problems/valid-palindrome/

 */

bool isAlpha(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
	{
		return true;
	}
	return false;
}

bool isNumeric(char c)
{
	if (c >= '0' && c <= '9')
	{
		return true;
	}
	return false;
}

char adjustLowerCase(char c)
{
	if (c >= 'A' && c <= 'Z')
	{
		c = c - 'A' + 'a';
	}
	return c;
}

bool isPalindrome(char * s)
{
	int len = strlen(s);
	int head = 0;
	int tail = len-1;
	while (head < tail)
	{
		while (head < len && !isAlpha(s[head]) && !isNumeric(s[head]))
		{
			head++;
		}
		if (head >= len)
		{
			break;
		}
		s[head] = adjustLowerCase(s[head]);

		while (tail >= 0 && !isAlpha(s[tail]) && !isNumeric(s[tail]))
		{
			tail--;
		}
		if (tail < 0)
		{
			break;
		}
		s[tail] = adjustLowerCase(s[tail]);

		if (s[head] == s[tail])
		{
			head++;
			tail--;
		} else
		{
			return false;
		}
	}
	return true;
}


