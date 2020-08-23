#define MIN(a, b) (a < b ? a : b)

static inline bool is_valid_position(int cur_x,
                                     int cur_y,
                                     int row_sz,
                                     int col_sz,
                                     int **maze)
{
    return (cur_x >= 0 && cur_x < row_sz && cur_y >= 0 && cur_y < col_sz &&
            0 == maze[cur_x][cur_y]);
}

static void maze_dfs(int **maze,
                     int row_sz,
                     int col_sz,
                     int **cost,
                     int cur_x,
                     int cur_y)
{
    int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    for (int x = 0; x < 4; x++) {
        int next_x = cur_x, next_y = cur_y, cur_step = 0;
        while (1) {
            next_x += dir[x][0];
            next_y += dir[x][1];
            cur_step++;
            if (!is_valid_position(next_x, next_y, row_sz, col_sz, maze)) {
                next_x -= dir[x][0];
                next_y -= dir[x][1];
                cur_step--;
                break;
            }
        }
        if (cost[cur_x][cur_y] + cur_step < cost[next_x][next_y]) {
            cost[next_x][next_y] = cost[cur_x][cur_y] + cur_step;
            maze_dfs(maze, row_sz, col_sz, cost, next_x, next_y);
        }
    }
}

int shortestDistance(int **maze,
                     int maze_sz,
                     int *maze_col_sz,
                     int *start,
                     int start_sz,
                     int *destination,
                     int destination_sz)
{
    int col_sz = maze_col_sz[0];
    int **cost = malloc(sizeof(int *) * maze_sz);
    for (int i = 0; i < maze_sz; i++) {
        cost[i] = malloc(sizeof(int) * col_sz);
        for (int j = 0; j < col_sz; j++)
            cost[i][j] = INT_MAX;
    }

    cost[start[0]][start[1]] = 0;
    maze_dfs(maze, maze_sz, col_sz, cost, start[0], start[1]);
    int ret = (cost[destination[0]][destination[1]] == INT_MAX
                   ? -1
                   : cost[destination[0]][destination[1]]);

    for (int i = 0; i < maze_sz; i++)
        free(cost[i]);
    free(cost);
    return ret;
}
