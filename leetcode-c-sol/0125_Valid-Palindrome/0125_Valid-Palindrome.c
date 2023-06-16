/**

125. Valid Palindrome [E]
Ref: https://leetcode.com/problems/valid-palindrome/

 */


static inline bool is_alphanumeric(char c)
{
	if ((c >= 'a' && c <= 'z' ) || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
		return true;
	return false;
}

bool isPalindrome(char * s)
{
	int head = 0;
	int tail = strlen(s) - 1;
	while (head < tail) {
		/* check char */
		if (!is_alphanumeric(s[head])) {
			head++;
			continue;
		}
		if (!is_alphanumeric(s[tail])) {
			tail--;
			continue;
		}
		if ((s[head] | ' ') != (s[tail] | ' '))
			return false;

		head++;
		tail--;
	}


	return true;
}

