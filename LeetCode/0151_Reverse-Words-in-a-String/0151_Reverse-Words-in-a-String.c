/**

151. Reverse Words in a String [M]
Ref: https://leetcode.com/problems/reverse-words-in-a-string/

Given an input string, reverse the string word by word.

Example 1:
Input: "the sky is blue"
Output: "blue is sky the"

Example 2:
Input: "  hello world!  "
Output: "world! hello"
Explanation: Your reversed string should not contain leading or trailing spaces.

Example 3:
Input: "a good   example"
Output: "example good a"
Explanation: You need to reduce multiple spaces between two words to a single space in the reversed string.


Note:
A word is defined as a sequence of non-space characters.
Input string may contain leading or trailing spaces. However, your reversed string should not contain leading or trailing spaces.
You need to reduce multiple spaces between two words to a single space in the reversed string.


Follow up:
For C programmers, try to solve it in-place in O(1) extra space.

 */


void my_memcpy(void *dest, void *src, size_t n)
{
	char *csrc = (char *)src;
	char *cdest = (char *)dest;

	for (int i = 0; i < n; i++)
	{
		cdest[i] = csrc[i];
	}
}

void reverseStr(char *s, int head, int tail)
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

char * reverseWords(char * s)
{
	int len = strlen(s);
	/* Reverse entire string */
	reverseStr(s, 0, len-1);

	/* Reverse each sub-string */
	int idx = 0;
	int findStr = -1; /* -1 means currently we dont find any char of sub-string*/
	int curLen = 0;
	while (s[idx] != '\0')
	{
		/* find the first char of sub-string, record the index */
		if (s[idx] != ' ' && (findStr == -1))
		{
			findStr = idx;
		}
		/* find the space after sub-string */
		if (s[idx] == ' ' && (findStr != -1))
		{
			s[idx] = '\0';
			int tmpLen = strlen(&(s[findStr]));
			s[idx] = ' ';
			reverseStr(s, findStr, idx-1);
			/* Use my_memcpy to avoid memcpy(): "memcpy-param-overlap" */
			my_memcpy(&(s[curLen]), &(s[findStr]), sizeof(char)*(tmpLen+1));
			curLen += (tmpLen+1);
			/* reverse the sub-string and reset findIdx of sub-string */
			findStr = -1;
		}
		idx++;
	}
	/* Means that we found the last string have not completed the reverse */
	if (findStr != -1)
	{
		reverseStr(s, findStr, idx-1);
		int tmpLen = strlen(&(s[findStr]));
		my_memcpy(&(s[curLen]), &(s[findStr]), sizeof(char)*(tmpLen+1));
		curLen += (tmpLen+1);
	}

	/* Edge case ("", "[space]...[space]") */
	if (curLen == 0)
	{
		return "";
	} else
	{
		s[curLen-1] = '\0';
	}
	return s;
}
