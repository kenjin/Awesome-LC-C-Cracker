static inline bool is_valid_position(int cur_x,
                                     int cur_y,
                                     int row_sz,
                                     int col_sz,
                                     int **maze)
{
    return (cur_x >= 0 && cur_x < row_sz && cur_y >= 0 && cur_y < col_sz &&
            0 == maze[cur_x][cur_y]);
}

static bool maze_dfs(int **maze,
                     int row_sz,
                     int col_sz,
                     int **visited,
                     int cur_x,
                     int cur_y,
                     int *end)
{
    int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    if (!is_valid_position(cur_x, cur_y, row_sz, col_sz, maze) ||
        visited[cur_x][cur_y])
        return false;

    if (cur_x == end[0] && cur_y == end[1])
        return true;

    visited[cur_x][cur_y] = 1;
    for (int x = 0; x < 4; x++) {
        int next_x = cur_x, next_y = cur_y;
        while (1) {
            next_x += dir[x][0];
            next_y += dir[x][1];
            if (!is_valid_position(next_x, next_y, row_sz, col_sz, maze)) {
                next_x -= dir[x][0];
                next_y -= dir[x][1];
                break;
            }
        }
        if (maze_dfs(maze, row_sz, col_sz, visited, next_x, next_y, end))
            return true;
    }

    return false;
}

bool hasPath(int **maze,
             int maze_sz,
             int *maze_col_sz,
             int *start,
             int start_sz,
             int *destination,
             int destination_sz)
{
    int col_sz = maze_col_sz[0];
    int **visited = malloc(sizeof(int *) * maze_sz);
    for (int i = 0; i < maze_sz; i++)
        visited[i] = calloc(col_sz, sizeof(int));

    bool ret = maze_dfs(maze, maze_sz, col_sz, visited, start[0], start[1],
                        destination);

    for (int i = 0; i < maze_sz; i++)
        free(visited[i]);
    free(visited);
    return ret;
}
