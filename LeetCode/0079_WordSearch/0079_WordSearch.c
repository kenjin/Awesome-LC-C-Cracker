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

static bool dfs(char **board,
                char *word,
                int widx,
                int cur_row,
                int cur_col,
                int row_sz,
                int col_sz,
                int wlen)
{
    if (cur_row == row_sz || cur_col == col_sz || cur_row < 0 || cur_col < 0 ||
        word[widx] != board[cur_row][cur_col])
        return false;
    /* End of the search */
    if ((wlen - 1) == widx)
        return true;

    char cur = board[cur_row][cur_col];
    board[cur_row][cur_col] = -1;
    if (dfs(board, word, widx + 1, cur_row + 1, cur_col, row_sz, col_sz, wlen))
        return true;
    if (dfs(board, word, widx + 1, cur_row - 1, cur_col, row_sz, col_sz, wlen))
        return true;
    if (dfs(board, word, widx + 1, cur_row, cur_col + 1, row_sz, col_sz, wlen))
        return true;
    if (dfs(board, word, widx + 1, cur_row, cur_col - 1, row_sz, col_sz, wlen))
        return true;
    board[cur_row][cur_col] = cur;

    return false;
}

bool exist(char **board, int board_sz, int *board_colsz, char *word)
{
    int wlen = strlen(word);
    if (!wlen)
        return true;
    if (!board)
        return false;

    int col_sz = board_colsz[0];
    for (int i = 0; i < board_sz; i++) {
        for (int j = 0; j < col_sz; j++) {
            if (dfs(board, word, 0, i, j, board_sz, col_sz, wlen))
                return true;
        }
    }

    return false;
}
