/***

Approach: Bitwise and Hash

Traverse the word from left to right, updating a bitmask: bitmask ^= (1 <<
(c-‘a’)). However, the bitmask only represents the state of the prefix
(word[0:i]). To count substrings, we use a hashtable. If the same bitmask occurs
'c' times before, indicating 'c' indices where word[0j1], word[0j2], …,
word[0jc] have the same state as word[0i], it implies that for word[j1+1i],
word[j2+1i], …, word[jc+1~i], all letters occurred even times. For the "at most
one odd" case, we toggle each bit of the bitmask and check its previous
occurrences.

Time complexity: O(n)
Space complexity: O(2^10)

***/

#define LETTER_SZ ('j' - 'a' + 1)

long long wonderfulSubstrings(char* word)
{
    long long ret = 0;
    int count[1 << LETTER_SZ] = {0}, mask = 0;
    count[0] = 1;
    for (char *cur_c = word; *cur_c != '\0'; cur_c++) {
        mask ^= 1 << (*cur_c - 'a');
        // one odd case:
        for (int i = 0; i < LETTER_SZ; ++i)
            ret += count[mask ^ (1 << i)]; 
        // all even case:
        ret += count[mask]++;
    }
    return ret;
}
