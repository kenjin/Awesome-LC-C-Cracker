/*

557. Reverse Words in a String III [E]

Given a string, you need to reverse the order of characters in each word within a sentence while still preserving whitespace and initial word order.

Example 1:
Input: "Let's take LeetCode contest"
Output: "s'teL ekat edoCteeL tsetnoc"

Note: In the string, each word is separated by single space and there will not be any extra space in the string.
 */

char * reverseWords(char * s)
{
    int len = strlen(s);
    if (len <= 1)
    {
        return s;
    }
    int bufferIdx = len;
    int bufferCtr = 0;
    char *buffer = calloc(len, sizeof(char));
    int retLen = 0;
    for (int i = 0; i < len; i++)
    {
        if (s[i] != ' ')
        {
            bufferIdx--;
            buffer[bufferIdx] = s[i];
            bufferCtr++;
        } else
        {
            if (!bufferCtr)
            {
                continue;
            }
            memcpy(&s[retLen], &buffer[bufferIdx], bufferCtr);
            // reserve 1 byte for space char
            retLen += bufferCtr+1;
            s[retLen-1] = ' ';
            // reset buffer ctr
            bufferCtr = 0;
            bufferIdx = len;
        }
    }
    memcpy(&s[retLen], &buffer[bufferIdx], bufferCtr);
    retLen += bufferCtr+1;
    s[retLen-1] = '\0';

    return s;
}

