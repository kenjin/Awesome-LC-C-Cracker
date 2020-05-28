
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* countBits(int num, int* returnSize)
{
    int *cb = malloc(sizeof(int)*(num+1));
    *returnSize = num + 1;
    cb[0] = 0;
    int cur_po2 = 1; /* Save current max num which is power of 2 */
    for (int i = 1; i <= num; i++) {
        /* Check whether it is power of 2 */
        if ((i & (i-1)) != 0)
            cb[i] = cb[cur_po2] + cb[i-cur_po2];
        else {
            cb[i] = 1;
            cur_po2 = i;            
        }        
    }

    return cb;
}
