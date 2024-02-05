
int firstUniqChar(char* s)
{
    int set[26] = {0};
    for (int i = 0; s[i] != 0; i++) {
        set[s[i] - 'a'] += 1;
    }

    for (int i = 0; s[i] != 0; i++) {
        if (set[s[i] - 'a'] == 1)
            return i;
    }

    return -1;
}
