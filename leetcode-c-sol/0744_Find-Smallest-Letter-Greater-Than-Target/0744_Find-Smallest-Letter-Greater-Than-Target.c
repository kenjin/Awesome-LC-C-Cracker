/**
744. Find Smallest Letter Greater Than Target [E]
Ref: https://leetcode.com/problems/find-smallest-letter-greater-than-target/

Given a list of sorted characters letters containing only lowercase 
letters, and given a target letter target, find the smallest element in
the list that is larger than the given target.

Letters also wrap around. For example, if the target is target = 'z' and
letters = ['a', 'b'], the answer is 'a'.

 */

char nextGreatestLetter(char* letters, int lettersSize, char target)
{
    int head = 0;
    int tail = lettersSize-1;
    while (head < (lettersSize-1) && tail >= 0)
    {   
        int mid = head + (tail-head)/2;
        if (letters[mid] <= target && target < letters[(mid+1)%lettersSize])
        {
            // [0, 2, 3, "3", 4]
            //                ^(ret)
            return letters[(mid+1)%lettersSize];
        } else if (letters[mid] <= target) 
        {
            // target >= letters[(mid+1)%lettersSize]
            head = mid+1;
        } else 
        {
            // target < letters[mid]
            tail = mid-1;
        }
    }
    
    return letters[0];
}

