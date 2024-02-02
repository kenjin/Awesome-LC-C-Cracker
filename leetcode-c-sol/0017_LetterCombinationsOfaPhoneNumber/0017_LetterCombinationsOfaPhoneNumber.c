/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

char letters[8][5] = {{"abc"}, {"def"}, {"ghi"}, {"jkl"}, {"mno"}, {"pqrs"}, {"tuv"}, {"wxyz"}};

static void dfs(char **ret, int *ret_sz, char *digits, int dctr, int dlen, char *tmp)
{
    if (dctr == dlen) {
        ret[*ret_sz] = calloc(dlen+1, sizeof(char));
        memcpy(ret[*ret_sz], tmp, sizeof(char)*dlen);
        *ret_sz += 1;
        return;
    }

    int idx = digits[dctr] - '0' - 2;
    int letter_len = strlen(letters[idx]);
    for (int i = 0; i < letter_len; i++) {
        tmp[dctr] = letters[idx][i];
        dfs(ret, ret_sz, digits, dctr + 1, dlen, tmp);
    }
}

char** letterCombinations(char* digits, int* returnSize)
{
    int dlen = strlen(digits);
    *returnSize = 0;
    if (dlen == 0)
        return NULL;

    // Constraints: 0 <= digits.length <= 4
    char **ret = malloc(sizeof(char *)*256);
    char *tmp = malloc(sizeof(char)*5);
    dfs(ret, returnSize, digits, 0, dlen, tmp);
    ret = realloc(ret, sizeof(char *)*(*returnSize));
    free(tmp);
    return ret;
}
