#define MAX(a, b) (a > b ? a : b)
#define VISITED_BIT (0x0100000)
#define ROOT_BIT (0x1000000)
#define BITMASK (0x00FFFFF)

#define IS_VISITED(a) (a & VISITED_BIT)
#define GET_VAL(a) (a & BITMASK)

static void dfs(int** grid, int cur_x, int cur_y, int row_sz, int col_sz,
                int* ctr, int root_x, int root_y) {
    if (cur_x < 0 || cur_y < 0 || cur_x == row_sz || cur_y == col_sz ||
        !grid[cur_x][cur_y] || IS_VISITED(grid[cur_x][cur_y]))
        return;

    *ctr += 1;
    grid[cur_x][cur_y] = ((root_x * 500 + root_y) | VISITED_BIT);

    int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    for (int i = 0; i < 4; i++)
        dfs(grid, cur_x + dir[i][0], cur_y + dir[i][1], row_sz, col_sz, ctr,
            root_x, root_y);
}

static int check_neighbor(int** grid, int cur_x, int cur_y, int row_sz,
                          int col_sz) {
    int ctr = 1;
    int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    // root_set is used to avoid duplicated root
    int root_set[4][2] = {0};
    int set_ctr = 0;
    for (int i = 0; i < 4; i++) {
        int tmp_x = cur_x + dir[i][0];
        int tmp_y = cur_y + dir[i][1];
        if (tmp_x < 0 || tmp_y < 0 || tmp_x == row_sz || tmp_y == col_sz ||
            !grid[tmp_x][tmp_y]) {
            continue;
        }

        int val = grid[tmp_x][tmp_y];

        // Transfer to root coordinate
        if (!(val & ROOT_BIT)) {
            tmp_x = (val & BITMASK) / 500;
            tmp_y = (val & BITMASK) % 500;
        }

        bool found = false;
        for (int x = 0; x < set_ctr; x++) {
            if (tmp_x == root_set[x][0] && tmp_y == root_set[x][1]) {
                found = true;
                break;
            }
        }
        if (!found) {
            root_set[set_ctr][0] = tmp_x;
            root_set[set_ctr][1] = tmp_y;
            set_ctr++;
            ctr += GET_VAL(grid[tmp_x][tmp_y]);
        }
    }
    return ctr;
}

int largestIsland(int** grid, int gridSize, int* gridColSize) {
    int max = 0;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridColSize[0]; j++) {
            if (!(grid[i][j] & VISITED_BIT) && grid[i][j]) {
                int ctr = 0;
                dfs(grid, i, j, gridSize, gridColSize[0], &ctr, i, j);
                grid[i][j] = (ctr | ROOT_BIT | VISITED_BIT);
                max = MAX(max, GET_VAL(grid[i][j]));
            }
        }
    }

    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridColSize[0]; j++) {
            if (grid[i][j] == 0) {
                int ctr = check_neighbor(grid, i, j, gridSize, gridColSize[0]);
                max = MAX(max, ctr);
            }
        }
    }

    return max;
}
