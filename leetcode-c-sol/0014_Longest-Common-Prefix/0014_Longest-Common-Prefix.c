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


char* longestCommonPrefix(char** strs, int strsSize)
{
    // Edge case: return the string directly if we only have one.
    if (strsSize == 1)
        return strs[0];

    int prefix_idx = 0;
    while (1) {
        int cur_char = strs[0][prefix_idx];
        bool need2break = false;
        for (int i = 1; i < strsSize; i++) {
            // Break the loop if reaching the end of the string or if the
            // character of the prefix is not equal to that of the others.
            if (strs[i][prefix_idx] == 0 || strs[i][prefix_idx] != cur_char) {
                need2break = true;
                break;
            }
        }
        if (need2break)
            break;

        // Get the common prefix index, continue to try the next one.
        prefix_idx++;
    }

    strs[0][prefix_idx] = 0;
    return strs[0];
}
