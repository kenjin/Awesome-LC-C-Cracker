
#define STR_IS_DUPLICATED   (0x80000000)

static void dfs(unsigned int *alpha_low, char **arr, int arrSize, int cur_arr_idx, int *max, int concat_len, unsigned int cur_alpha)
{
    int len = strlen(arr[cur_arr_idx]);
    if (alpha_low[cur_arr_idx] == STR_IS_DUPLICATED ||
            (alpha_low[cur_arr_idx] & cur_alpha)) {
        return;
    }

    cur_alpha |= alpha_low[cur_arr_idx];
    concat_len += len;
    *max = (*max > concat_len ? *max : concat_len);

    for (int i = cur_arr_idx + 1; i < arrSize; i++)
        dfs(alpha_low, arr, arrSize, i, max, concat_len, cur_alpha);
}


int maxLength(char** arr, int arrSize)
{
    unsigned int *alpha_low = calloc(arrSize, sizeof(unsigned int));
    // Use undigned int (first 26 bit) and transfer from char to bit point of view
    for (int i = 0; i < arrSize; i++){
        for (int x = 0; x < strlen(arr[i]); x++) {
            if (alpha_low[i] & (0x1 << (arr[i][x]-'a'))) {
                alpha_low[i] = STR_IS_DUPLICATED;
                break;
            }
            alpha_low[i] |= (0x1 << (arr[i][x]-'a'));
        }
    }

    int max = 0;
    for (int i = 0; i < arrSize; i++)
        dfs(alpha_low, arr, arrSize, i, &max, 0, 0);

    return max;
}
