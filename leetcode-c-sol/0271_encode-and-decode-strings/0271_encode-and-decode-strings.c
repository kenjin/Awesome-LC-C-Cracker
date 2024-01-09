/** Encodes a list of strings to a single string */
char* encode(char** strs, int strsSize) {
    int sum = 0;
    for (int i = 0; i < strsSize; i++) {
        int len = strlen(strs[i]);
        // Add first 1 byte to record length for each string
        sum += (len+1);
    }
    // Add first 1 byte to record the total length
    char *ret = calloc((sum + 2), sizeof(int));
    int cur = 0;
    ret[cur++] = strsSize;
    for (int i = 0; i < strsSize; i++) {
        int len = strlen(strs[i]);
        ret[cur++] = len;
        memcpy(&(ret[cur]), strs[i], sizeof(char)*len);
        cur += len;
    }
    return ret;
}

/**
 * Decodes a single string to a list of strings.
 *
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** decode(char* s, int* returnSize) {
    // Note that to cast to unisgned to get correct len
    *returnSize = (unsigned char)*s;
    char **ret = malloc(sizeof(char *)*(*returnSize));
    int len = 0, str_ctr = -1, cur = 0;
    s++;
    while (*s || (str_ctr + 1) < *returnSize) {
        if (!len) {
            len = (unsigned char)*s;
            ret[++str_ctr] = calloc(len + 1, sizeof(char));
            cur = 0;
        } else {
            ret[str_ctr][cur++] = *s;
            len--;
        }
        s++;
    }
    return ret;
}

// Your functions will be called as such:
// char* s = encode(strs, strsSize);
// decode(s, &returnSize);
