/**
#79. Word Search

Given a 2D board and a word, find if the word exists in the grid.
The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once.

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
bool search(char** board, char *word, int word_idx, int cur_row, int cur_col, int max_row, int max_col, int word_len)
{
	bool ret = false;
	if (cur_row == max_row || cur_col == max_col || cur_row < 0 || cur_col < 0
			|| word[word_idx] != board[cur_row][cur_col])
	{
		return false;
	}

	if ((word_len-1) == word_idx)
	{
		return true;
	} else
	{
		char cur = board[cur_row][cur_col];
		board[cur_row][cur_col] = -1;
		if (search(board, word, word_idx+1, cur_row+1, cur_col, max_row, max_col, word_len))
			return true;
		if (search(board, word, word_idx+1, cur_row-1, cur_col, max_row, max_col, word_len))
			return true;
		if (search(board, word, word_idx+1, cur_row, cur_col+1, max_row, max_col, word_len))
			return true;
		if (search(board, word, word_idx+1, cur_row, cur_col-1, max_row, max_col, word_len))
			return true;
		board[cur_row][cur_col] = cur;
	}    
	return ret;
}

bool exist(char** board, int boardRowSize, int boardColSize, char* word) {

	int len = strlen(word);

	if (len == 0)
		return true;
	if (board == NULL)
		return false;

	for (int i = 0; i < boardRowSize; i++)
	{
		for (int j = 0; j < boardColSize; j++)
		{
			if (search(board, word, 0, i, j, boardRowSize, boardColSize, len) == true)
				return true;
		}
	}

	return false;
}
