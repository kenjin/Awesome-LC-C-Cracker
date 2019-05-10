/**

14. Longest Common Prefix [E]
Ref: https://leetcode.com/problems/longest-common-prefix/

Write a function to find the longest common prefix string amongst an array of strings.

If there is no common prefix, return an empty string "".

Example 1:
Input: ["flower","flow","flight"]
Output: "fl"

Example 2:
Input: ["dog","racecar","car"]
Output: ""
Explanation: There is no common prefix among the input strings.

Note:

All given inputs are in lowercase letters a-z.

 */
char * longestCommonPrefix(char ** strs, int strsSize)
{
	if (strsSize == 0)
	{
		return "";
	}

	/* Calculate min len of **strs */
	int min = INT_MAX;
	for (int i = 0; i < strsSize; i++)
	{
		if (strlen(strs[i]) < min)
		{
			min = strlen(strs[i]);
		}
	}

	int common = 0;
	for (int i = 0; i < min; i++)
	{
		char cur = strs[0][i];        
		for (int j = 1; j < strsSize; j++)
		{
			if (strs[j][i] != cur)
			{                
				strs[0][common] = '\0';
				return strs[0];
			}
		}
		common++;
	}       
	strs[0][common] = '\0';  
	return strs[0];
}
