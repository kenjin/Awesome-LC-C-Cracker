
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *pourWater(int *heights, int heights_sz, int v, int k, int *return_sz)
{
    for (int i = 0; i < v; i++) {
        int pos = k;
        bool found = false;
        /* moving left */
        for (int x = pos - 1; x >= 0; x--) {
            if (heights[x] > heights[pos])
                break;
            if (heights[x] < heights[pos]) {
                pos = x;
                found = true;
            }
        }
        if (!found) {
            /* moving right */
            for (int x = pos + 1; x < heights_sz; x++) {
                if (heights[x] > heights[pos])
                    break;
                if (heights[x] < heights[pos])
                    pos = x;
            }
        }

        /* Update the final position after moving left/right or still at
         * position 'k'. */
        heights[pos]++;
    }

    *return_sz = heights_sz;
    return heights;
}
