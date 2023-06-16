typedef struct __pos {
    int row;
    int col;
} POS;

typedef struct __queue {
    int size;
    int cur;
    int front;
    int rear;
    POS *p;
} QUEUE;

QUEUE *createq(int size)
{
    QUEUE *obj = malloc(sizeof(QUEUE));
    obj->size = size;
    obj->cur = 0;
    obj->front = 0;
    obj->rear = -1;
    obj->p = malloc(sizeof(POS) * size);
    return obj;
}

void destroyq(QUEUE *obj)
{
    free(obj->p);
    free(obj);
}

bool is_emptyq(QUEUE *obj)
{
    return (obj->cur == 0);
}

void addq(QUEUE *obj, int row, int col)
{
    obj->rear = (obj->rear + 1) % obj->size;
    obj->p[obj->rear].row = row;
    obj->p[obj->rear].col = col;
    obj->cur++;
}

POS delq(QUEUE *obj)
{
    POS ret = obj->p[obj->front];
    obj->front = (obj->front + 1) % obj->size;
    obj->cur--;
    return ret;
}

static inline void check_neighbor(char **board,
                                  char **chk,
                                  QUEUE *q,
                                  int row_sz,
                                  int col_sz,
                                  int r,
                                  int c)
{
    int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    for (int x = 0; x < 4; x++) {
        int row_cur = r + dir[x][0];
        int col_cur = c + dir[x][1];
        if (row_cur >= 1 && col_cur >= 1 && row_cur < row_sz - 1 &&
            col_cur < col_sz - 1 && !chk[row_cur][col_cur] &&
            board[row_cur][col_cur] == 'O') {
            addq(q, row_cur, col_cur);
            chk[row_cur][col_cur] = 1;
        }
    }
}

void solve(char **board, int boardSize, int *boardColSize)
{
    if (!boardSize)
        return board;

    int col_sz = boardColSize[0];
    char **chk = malloc(sizeof(char *) * boardSize);
    for (int i = 0; i < boardSize; i++) {
        chk[i] = calloc(col_sz, sizeof(char));
    }

    QUEUE *q = createq((boardSize + col_sz) * 4);
    for (int i = 0; i < boardSize; i++) {
        if (board[i][0] == 'O')
            check_neighbor(board, chk, q, boardSize, col_sz, i, 0);
        if (board[i][col_sz - 1] == 'O')
            check_neighbor(board, chk, q, boardSize, col_sz, i, col_sz - 1);
    }

    for (int i = 0; i < col_sz; i++) {
        if (board[0][i] == 'O')
            check_neighbor(board, chk, q, boardSize, col_sz, 0, i);
        if (board[boardSize - 1][i] == 'O')
            check_neighbor(board, chk, q, boardSize, col_sz, boardSize - 1, i);
    }

    while (!is_emptyq(q)) {
        POS cur = delq(q);
        board[cur.row][cur.col] = '!';
        check_neighbor(board, chk, q, boardSize, col_sz, cur.row, cur.col);
    }

    for (int i = 1; i < boardSize - 1; i++) {
        for (int j = 1; j < col_sz - 1; j++)
            board[i][j] = (board[i][j] == '!' ? 'O' : 'X');
    }

    destroyq(q);
    for (int i = 0; i < boardSize; i++)
        free(chk[i]);
    free(chk);
}
