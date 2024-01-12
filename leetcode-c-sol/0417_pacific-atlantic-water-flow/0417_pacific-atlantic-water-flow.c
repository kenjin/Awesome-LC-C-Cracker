
// heights[][] is from 0x0 to 0x0186A0
// 0x1 00000 => pacific bit
// 0x2 00000 => pacific ocean is visited
// 0x4 00000 => atlantic bit
// 0x8 00000 => atlantic ocean is visited
#define PACIFIC_TAG           (0x100000)
#define ATLANTIC_TAG          (PACIFIC_TAG << 2)
#define FLOW_BOTH_TAG         (PACIFIC_TAG | ATLANTIC_TAG)
#define OCEAN_MASK            (0xFFFFF)
#define IS_VISITED(OCEAN)       (OCEAN << 1)

static void dfs(int** heights, int row_sz, int col_sz, int cur_x, int cur_y, int *ret_sz, int ocean)
{
    if (heights[cur_x][cur_y] & IS_VISITED(ocean))
        return;

    heights[cur_x][cur_y] |= (ocean | IS_VISITED(ocean));
    if ((heights[cur_x][cur_y] & FLOW_BOTH_TAG) == FLOW_BOTH_TAG) {
        *ret_sz += 1;
    }

    int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    for (int i = 0; i < 4; i++) {
        int next_x = cur_x + dirs[i][0];
        int next_y = cur_y + dirs[i][1];
        if (next_x >= 0 && next_y >= 0 && next_x < row_sz && next_y < col_sz &&
                (heights[cur_x][cur_y] & OCEAN_MASK) <= (heights[next_x][next_y] & OCEAN_MASK)) {
            dfs(heights, row_sz, col_sz, next_x, next_y, ret_sz, ocean);
        }  
    }
}

int** pacificAtlantic(int** heights, int heightsSize, int* heightsColSize, int* returnSize, int** returnColumnSizes)
{
    int col_sz = heightsColSize[0];
    *returnSize = 0;

    for (int i = 0; i < heightsSize; i++) {
        dfs(heights, heightsSize, col_sz, i, 0, returnSize, PACIFIC_TAG);
        dfs(heights, heightsSize, col_sz, i, col_sz-1, returnSize, ATLANTIC_TAG);
    }

    for (int i = 0; i < col_sz; i++) {
        dfs(heights, heightsSize, col_sz, 0, i, returnSize, PACIFIC_TAG);
        dfs(heights, heightsSize, col_sz, heightsSize-1, i, returnSize, ATLANTIC_TAG);
    }

    int **ret = malloc(sizeof(int *)*(*returnSize)), ctr = 0;
    *returnColumnSizes = malloc(sizeof(int)*(*returnSize));
    for (int i = 0; i < heightsSize; i++) {
        for (int j = 0; j < col_sz; j++) {
            if ((heights[i][j] & FLOW_BOTH_TAG) == FLOW_BOTH_TAG) {
                ret[ctr] = malloc(sizeof(int)*2);
                ret[ctr][0] = i;
                ret[ctr][1] = j;
                (*returnColumnSizes)[ctr] = 2;
                ctr++;
            }
        }
    }
    return ret;
}
