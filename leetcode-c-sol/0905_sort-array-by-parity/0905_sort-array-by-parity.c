
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *sortArrayByParity(int *A, int ASize, int *returnSize)
{
    int oidx = ASize - 1;
    for (int i = 0; i < oidx; i++) {
        if (A[i] & 0x1) {
            int tmp = A[i];
            A[i] = A[oidx];
            A[oidx] = tmp;
            oidx--;
            i--;
        }
    }

    *returnSize = ASize;
    return A;
}
