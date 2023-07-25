
static inline bool do_valiate(char c, unsigned short *v_set)
{
    if (*v_set & (0x1 << (c - '0')))
         return false;
    
    *v_set |= (0x1 << (c - '0'));
    return true;
}

bool isValidSudoku(char** board, int boardSize, int* boardColSize)
{    
    
    for (int i = 0; i < 9; i++) {
        unsigned short valid_set_r = 0x0000, valid_set_c = 0x0000;
        for (int j = 0; j < 9; j++) {
            if (board[i][j] != '.' && !do_valiate(board[i][j], &valid_set_r))
                return false;

            if (board[j][i] != '.' && !do_valiate(board[j][i], &valid_set_c))
                return false;
        }
    }

    for (int i = 0; i < 9; i++) {
        int row = (i / 3)*3, col = (i % 3)*3;
        unsigned short valid_set = 0x0000;
        for (int j = 0; j < 9; j++) {
            int add_r = (j / 3);
            int add_c = (j % 3);
            if (board[row + add_r][col + add_c] != '.' &&
                !do_valiate(board[row + add_r][col + add_c], &valid_set))
                return false;
        }
    }

    return true;
}
