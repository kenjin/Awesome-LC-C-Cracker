int minimizedStringLength(char* s) {
    int set[26] = {0}, ret = 0;
    for (int i = 0; i < strlen(s); i++) {
        if (set[s[i] - 'a'] == 0)
            ret++;
        set[s[i] - 'a'] += 1;
    }

    return ret;
}
