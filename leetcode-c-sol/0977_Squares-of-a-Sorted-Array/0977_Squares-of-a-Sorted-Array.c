
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *sortedSquares(int *A, int ASize, int *returnSize)
{
    *returnSize = ASize;
    int *ret = malloc(sizeof(int) * ASize);
    int neg_idx = -1;
    for (int i = 0; i < ASize; i++) {
        if (A[i] < 0)
            neg_idx++;
        A[i] = A[i] * A[i];
    }

    int pos_idx = neg_idx + 1, ctr = 0;
    while (neg_idx >= 0 && pos_idx < ASize) {
        if (A[neg_idx] > A[pos_idx])
            ret[ctr++] = A[pos_idx++];
        else
            ret[ctr++] = A[neg_idx--];
    }

    while (neg_idx >= 0)
        ret[ctr++] = A[neg_idx--];

    while (pos_idx < ASize)
        ret[ctr++] = A[pos_idx++];

    return ret;
}
