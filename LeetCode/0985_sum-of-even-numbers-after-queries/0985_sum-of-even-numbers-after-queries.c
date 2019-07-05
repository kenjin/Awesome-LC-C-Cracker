
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sumEvenAfterQueries(int* A, int ASize, int** queries, int queriesSize, int* queriesColSize, int* returnSize)
{
    int *ret = malloc(sizeof(int)*queriesSize);
    *returnSize = queriesSize;
    
    int sum = 0;
    for (int i = 0; i < ASize; i++)
    {
        if ((A[i] & 0x1) != 0x1)
        {
            sum += A[i];
        }
    }
    
    for (int i = 0; i < queriesSize; i++)
    {
        int val = queries[i][0];
        int idx = queries[i][1];
        if ((A[idx] & 0x1) != 0x1)
        {
            sum -= A[idx];
        }        
        
        A[idx] = A[idx] + val;
        if ((A[idx] & 0x1) != 0x1)
        {
            sum += A[idx];
        }
        
        
        ret[i] = sum;
    }
    
    return ret;
}
