/**
#79. Word Search

Given a 2D board and a word, find if the word exists in the grid.
The word can be constructed from letters of sequentially adjacent cell, where
"adjacent" cells are those horizontally or vertically neighboring. The same
letter cell may not be used more than once.

Example:
    board =
    [
        ['A','B','C','E'],
        ['S','F','C','S'],
        ['A','D','E','E']
    ]

    Given word = "ABCCED", return true.
    Given word = "SEE", return true.
    Given word = "ABCB", return false.
*/


static inline void reverse(char* str, int len) {
    for (int x = 0; x < (len >> 1); x++) {
        char tmp = str[x];
        str[x] = str[len - 1 - x];
        str[len - 1 - x] = tmp;
    }
}

static bool dfs(char** board, char* word, int widx, int cur_row, int cur_col,
                int row_sz, int col_sz, int wlen) {
    if (cur_row == row_sz || cur_col == col_sz || cur_row < 0 || cur_col < 0 ||
        word[widx] != board[cur_row][cur_col])
        return false;
    /* End of the search */
    if ((wlen - 1) == widx)
        return true;

    int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    char cur = board[cur_row][cur_col];
    board[cur_row][cur_col] = -1;
    for (int i = 0; i < 4; i++) {
        if (dfs(board, word, widx + 1, cur_row + dir[i][0], cur_col + dir[i][1],
                row_sz, col_sz, wlen))
            return true;
    }
    board[cur_row][cur_col] = cur;
    return false;
}

bool exist(char** board, int board_sz, int* board_colsz, char* word) {
    int len = strlen(word);
    if (!len)
        return true;
    if (!board)
        return false;

    // Take O(n) time to consider `aaaaaaaaaab` case, reversing to `baaaaaaaaaa`
    // could speed-up DFS
    int same_head_ctr = 0, same_tail_ctr = 0;
    for (int i = 1; i < len; i++) {
        if (word[0] == word[i])
            same_head_ctr++;
        else
            break;
    }

    for (int i = len - 2; i >= 0; i--) {
        if (word[len - 1] == word[i])
            same_tail_ctr++;
        else
            break;
    }

    if (same_tail_ctr < same_head_ctr)
        reverse(word, len);

    for (int i = 0; i < board_sz; i++) {
        for (int j = 0; j < board_colsz[i]; j++) {
            if (dfs(board, word, 0, i, j, board_sz, board_colsz[i], len))
                return true;
        }
    }

    return false;
}
