static bool is_palindrome(char* str, int left, int right)
{
    while (left <= right) {
        if (str[left] != str[right])
            return false;
        left++;
        right--;
    }
    return true;
}

static void dfs(char* str, int cur_idx, int slen, char*** res, int* returnSize,
                int** returnColSize, char** tmp_strs, int tmp_sz)
{
    // If we successfully find all the palindrome substrings that combine to
    // form the string, add tmp_strs group to the result.
    if (cur_idx == slen) {
        res[*returnSize] = malloc(sizeof(char*) * tmp_sz);
        (*returnColSize)[*returnSize] = tmp_sz;
        for (int i = 0; i < tmp_sz; i++) {
            res[*returnSize][i] = malloc(strlen(tmp_strs[i]) + 1);
            strcpy(res[*returnSize][i], tmp_strs[i]);
        }
        (*returnSize)++;
        return;
    }

    for (int x = cur_idx; x < slen; x++) {
        // If the current substring is a palindrome, save it to tmp_strs group
        // then find substring from the next index.
        if (is_palindrome(str, cur_idx, x)) {
            char* sub_str = calloc(x - cur_idx + 2, sizeof(char));
            strncpy(sub_str, &str[cur_idx], x - cur_idx + 1);
            tmp_strs[tmp_sz] = sub_str;
            dfs(str, x + 1, slen, res, returnSize, returnColSize, tmp_strs,
                tmp_sz + 1);
            free(sub_str);
        }
    }
}

char*** partition(char* str, int* returnSize, int** returnColSize)
{
    int slen = strlen(str);
    char*** res = malloc(sizeof(char**) * (1 << slen));
    *returnSize = 0;
    *returnColSize = malloc(sizeof(int) * (1 << slen));

    char** tmp = malloc(sizeof(char*) * slen);
    dfs(str, 0, slen, res, returnSize, returnColSize, tmp, 0);
    free(tmp);
    return res;
}

