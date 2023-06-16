
typedef struct __trie {
    char *str;
    struct __trie *child[26];
} TRIE;

static inline TRIE *create_node()
{
    return calloc(1, sizeof(TRIE));
}

static void free_trie(TRIE *t)
{
    if (!t)
        return;

    for (int i = 0; i < 26; i++)
        free_trie(t->child[i]);

    free(t);
}

static void add_trie(TRIE *head, char *str)
{
    char *s = str;
    while (*s) {
        int idx = *s - 'a';
        if (!head->child[idx])
            head->child[idx] = create_node();
        head = head->child[idx];
        s++;
    }

    head->str = str;
}

void dfs(TRIE *t,
         char **board,
         int r_sz,
         int c_sz,
         int cur_row,
         int cur_col,
         char **ret,
         int *ret_sz)
{
    if (cur_row == r_sz || cur_col == c_sz || cur_row < 0 ||
        cur_col < 0 ||                   /* Exceed boundary */
        board[cur_row][cur_col] == -1 || /* Current board has been visited */
        !(t->child[board[cur_row][cur_col] -
                   'a'])) /* This string path is not in the trie */
        return;

    t = t->child[board[cur_row][cur_col] - 'a'];
    if (t->str) {
        ret[*ret_sz] = t->str;
        *ret_sz += 1;
        t->str = NULL;
    }

    char dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    char tmp = board[cur_row][cur_col];
    board[cur_row][cur_col] =
        -1; /* tag to -1 to indicate this coordinate was visited */
    for (int x = 0; x < 4; x++)
        dfs(t, board, r_sz, c_sz, cur_row + dir[x][0], cur_col + dir[x][1], ret,
            ret_sz);

    board[cur_row][cur_col] = tmp;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **findWords(char **board,
                 int boardSize,
                 int *boardColSize,
                 char **words,
                 int wordsSize,
                 int *returnSize)
{
    TRIE *t = create_node();
    for (int i = 0; i < wordsSize; i++)
        add_trie(t, words[i]);

    char **ret = malloc(sizeof(char *) * wordsSize);
    *returnSize = 0;
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardColSize[0]; j++)
            dfs(t, board, boardSize, boardColSize[0], i, j, ret, returnSize);
    }

    free_trie(t);
    return ret;
}
