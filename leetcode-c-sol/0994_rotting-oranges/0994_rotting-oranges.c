enum {
    EMPTY = 0,
    FRESH,
    ROTTEN,
};

typedef struct __pos {
    int row;
    int col;
} POS;

typedef struct __queue {
    int size;
    int cur;
    int head;
    int tail;
    POS *arr;
} QUEUE;

static inline QUEUE *create_q(int size)
{
    QUEUE *q = malloc(sizeof(QUEUE));
    q->head = 0;
    q->tail = -1;
    q->size = size;
    q->cur = 0;
    q->arr = malloc(sizeof(POS) * size);
    return q;
}

static inline void release_q(QUEUE *q)
{
    free(q->arr);
    free(q);
}

static inline int get_size_q(QUEUE *q)
{
    return q->cur;
}

static inline bool is_full_q(QUEUE *q)
{
    return (q->cur == q->size);
}

static inline bool is_empty_q(QUEUE *q)
{
    return (q->cur == 0);
}

static inline void push_q(QUEUE *q, int x, int y)
{
    if (is_full_q(q))
        return;

    q->tail = (q->tail + 1) % q->size;
    q->arr[q->tail].row = x;
    q->arr[q->tail].col = y;
    q->cur += 1;
}

static inline void pop_q(QUEUE *q)
{
    if (is_empty_q(q))
        return;

    q->head = (q->head + 1) % q->size;
    q->cur -= 1;
}

static inline POS peak_q(QUEUE *q)
{
    return q->arr[q->head];
}

static void bfs(int **grid, int row_sz, int col_sz, QUEUE *q, int *fresh_cnt)
{
    int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int cur_sz = get_size_q(q);
    for (int i = 0; i < cur_sz; i++) {
        POS tmp = peak_q(q);
        pop_q(q);
        for (int x = 0; x < 4; x++) {
            int cur_row = tmp.row + dir[x][0];
            int cur_col = tmp.col + dir[x][1];
            if (cur_row >= 0 && cur_row < row_sz && cur_col >= 0 &&
                cur_col < col_sz && grid[cur_row][cur_col] == FRESH) {
                *fresh_cnt -= 1;
                push_q(q, cur_row, cur_col);
                grid[cur_row][cur_col] = ROTTEN;
            }
        }
    }
}

int orangesRotting(int **grid, int gridSize, int *gridColSize)
{
    int col_sz = gridColSize[0];
    QUEUE *q = create_q(gridSize * col_sz);

    /* init */
    int fresh_cnt = 0;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < col_sz; j++) {
            if (grid[i][j] == ROTTEN)
                push_q(q, i, j);
            else if (grid[i][j] == FRESH)
                fresh_cnt++;
        }
    }
    /* rotten oranges */
    int min = 0;
    while (1) {
        bfs(grid, gridSize, col_sz, q, &fresh_cnt);
        if (is_empty_q(q))
            break;
        min++;
    }

    release_q(q);
    return (fresh_cnt == 0 ? min : -1);
}