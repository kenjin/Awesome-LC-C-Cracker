/***

Approach: O(n) string traversing

Initialize indices s_idx for traversing s and t_idx for traversing t. Use a
while loop to iterate through both strings as long as neither has reached its
end. If characters at current indices of both strings match, increment t_idx
(indicating a match for t has been found). Always increment s_idx to continue
checking the next character in s. After the loop, the value t_idx represents how
many characters of t were found in s. Subtract t_idx from the length of t to get
the number of characters that need to be appended to s.

***/

int appendCharacters(char* s, char* t) {
    int s_idx = 0, t_idx = 0;
    while (s[s_idx] && t[t_idx]) {
        if (s[s_idx] == t[t_idx])
            t_idx++;
        s_idx++;
    }

    return (strlen(t) - t_idx);
}
