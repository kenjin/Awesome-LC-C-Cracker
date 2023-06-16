/**

  289. Game of Life [Medium]

  According to the Wikipedia's article: "The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970."

  Given a board with m by n cells, each cell has an initial state live (1) or dead (0). Each cell interacts with its eight neighbors (horizontal, vertical, diagonal) using the following four rules (taken from the above Wikipedia article):

  Any live cell with fewer than two live neighbors dies, as if caused by under-population.
  Any live cell with two or three live neighbors lives on to the next generation.
  Any live cell with more than three live neighbors dies, as if by over-population..
  Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
  Write a function to compute the next state (after one update) of the board given its current state. The next state is created by applying the above rules simultaneously to every cell in the current state, where births and deaths occur simultaneously.

Example:
Input: 
[
	[0,1,0],
	[0,0,1],
	[1,1,1],
	[0,0,0]
]

Output: 
[
	[0,0,0],
	[1,0,1],
	[0,1,1],
	[0,1,0]
]

Follow up:
Could you solve it in-place? Remember that the board needs to be updated at the same time: You cannot update some cells first and then use their updated values to update other cells.
In this question, we represent the board using a 2D array. In principle, the board is infinite, which would cause problems when the active area encroaches the border of the array. How would you address these problems?

 */

void checkNeighbor(int** board, int row, int col, int rowSize, int colSize, int *live, int *dead)
{
	for (int x = -1; x < 2; x++)
	{
		for (int y = -1; y < 2; y ++)
		{
			int curRow = row + x;
			int curCol = col + y;

			if (curRow < 0 || curRow >= rowSize ||
					curCol < 0 || curCol >= colSize ||
					(curRow == row && curCol == col))
			{
				continue;
			}
			if ((board[curRow][curCol] & 0x01) == 0x01)
			{
				*live += 1;
			} else
			{
				*dead += 1;
			}
		}
	}    
}

void gameOfLife(int** board, int boardSize, int* boardColSize){

	if (boardSize == 0)
	{
		return board;        
	}

	int colSize = boardColSize[0];
	for (int x = 0; x < boardSize; x++)
	{
		for (int y = 0; y < colSize; y++)
		{            
			int live = 0, dead = 0;
			checkNeighbor(board, x, y, boardSize, colSize, &live, &dead);                        
			if ((board[x][y] & 0x01) == 0x01) /* live */
			{
				if (live == 2 || live == 3)
				{
					board[x][y] |= 0x10;
				}
			} else /* dead */
			{
				if (live == 3)
				{
					board[x][y] |= 0x10;
				}
			}
		}
	}

	for (int x = 0; x < boardSize; x++)
	{
		for (int y = 0; y < colSize; y++)
		{        
			if ((board[x][y] & 0x10) == 0x10)
			{
				board[x][y] = 1;
			} else
			{
				board[x][y] = 0;
			}
		}
	}
}

