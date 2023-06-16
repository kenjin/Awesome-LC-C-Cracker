/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *diStringMatch(char *S, int *returnSize)
{
    int len = strlen(S);
    int *ret = malloc(sizeof(int) * (len + 1));
    int min = 0, max = len;
    for (int i = 0; i < len; i++) {
        if (S[i] == 'I') {
            ret[i] = min;
            min++;
        } else {
            ret[i] = max;
            max--;
        }
    }
    ret[len] = min;

    *returnSize = len + 1;
    return ret;
}
