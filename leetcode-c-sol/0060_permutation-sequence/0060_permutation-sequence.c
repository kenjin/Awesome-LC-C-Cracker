
char * getPermutation(int n, int k)
{
    if (n == 1)
        return "1";

    char *num = malloc(sizeof(char)*10);
    char *ret = calloc(n+1, sizeof(char));
    char *tmp = ret;
    int remain_comb = 1;
    for (int i = 1; i <= n; i++) {
        remain_comb *= i;
        num[i-1] = '0' + i;
    }    

    k--; /* let k starts from "0"(th) permutation sequence */
    for (int i = n; i > 2; i--, tmp++) {
        remain_comb /= i;        
        int set_idx = k / remain_comb;
        int new_k = k - set_idx*remain_comb;
        *tmp = num[set_idx];    
        memmove(&num[set_idx], &num[set_idx+1], i-set_idx);
        k = new_k;
    }

    /* Handle the last two char(s) */
    if (k == 0) {
        tmp[0] = num[0];        
        tmp[1] = num[1];
    } else {
        tmp[0] = num[1];
        tmp[1] = num[0];
    }

    free(num);
    return ret;
}
