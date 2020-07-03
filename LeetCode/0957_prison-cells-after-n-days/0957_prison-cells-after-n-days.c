
enum {
    VACANT = 0,
    OCCUPIED,
};

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *prisonAfterNDays(int *cells, int cells_sz, int N, int *return_sz)
{
    int *tmp = malloc(sizeof(int) * cells_sz);
    N %= 14;
    N = (N == 0 ? 14 : N);
    for (int round = 0; round < N; round++) {
        for (int i = 0; i < cells_sz; i++)
            tmp[i] =
                ((i != 0 && i != cells_sz - 1 && cells[i - 1] == cells[i + 1])
                     ? OCCUPIED
                     : VACANT);
        memcpy(cells, tmp, sizeof(int) * cells_sz);
    }

    free(tmp);
    *return_sz = cells_sz;
    return cells;
}