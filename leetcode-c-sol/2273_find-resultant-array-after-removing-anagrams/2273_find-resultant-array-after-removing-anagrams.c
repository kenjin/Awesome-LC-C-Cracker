char** removeAnagrams(char** words, int wordsSize, int* returnSize)
{
    char **ret = malloc(sizeof(char *)*wordsSize);
    int ret_sz = 0;

    int set[26] = {0};
    for (int i = 0; i < wordsSize; i++) {
        char *tmp = words[i];
        int set_tmp[26] = {0};
        while (*tmp) {
            set_tmp[*tmp - 'a']++;
            tmp++;
        }
        if (memcmp(set, set_tmp, sizeof(int)*26)) {
            ret[ret_sz] = words[i];
            ret_sz++;
            memcpy(set, set_tmp, sizeof(int)*26);
        }
    }

    ret = realloc(ret, sizeof(char*)*ret_sz);
    *returnSize = ret_sz;
    return ret;
}
