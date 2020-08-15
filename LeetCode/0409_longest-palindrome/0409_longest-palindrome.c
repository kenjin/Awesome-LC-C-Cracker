int longestPalindrome(char *s)
{
    int ctr[52] = {0}; /* a~z, A~Z */
    while (*s) {
        if ('A' <= *s && *s <= 'Z')
            ctr[*s - 'A' + 26] += 1;
        else if ('a' <= *s && *s <= 'z')
            ctr[*s - 'a'] += 1;
        s++;
    }

    int ret = 0, odd_found = 0;
    for (int x = 0; x < 52; x++) {
        if (!odd_found && (ctr[x] & 0x1))
            odd_found = 1;
        ret += (ctr[x] >> 1);
    }

    ret = (ret << 1) + odd_found;
    return ret;
}
