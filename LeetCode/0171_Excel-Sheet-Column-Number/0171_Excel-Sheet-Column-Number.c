/**
171. Excel Sheet Column Number [E]
Ref: https://leetcode.com/problems/excel-sheet-column-number/

Given a column title as appear in an Excel sheet, return its corresponding
column number.

For example:
A -> 1
B -> 2
C -> 3
...
Z -> 26
AA -> 27
AB -> 28
...

Example 1:
Input: "A"
Output: 1

Example 2:
Input: "AB"
Output: 28

Example 3:
Input: "ZY"
Output: 701

 */

int titleToNumber(char *s)
{
    int sum = 0;
    while (*s) {
        sum *= 26;
        sum += *s - 'A' + 1;
        s++;
    }
    return sum;
}