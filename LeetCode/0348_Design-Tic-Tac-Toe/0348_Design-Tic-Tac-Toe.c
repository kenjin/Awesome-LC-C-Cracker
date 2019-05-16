/**

348. Design Tic-Tac-Toe [M]
Ref: https://leetcode.com/problems/design-tic-tac-toe/

Design a Tic-tac-toe game that is played between two players on a n x n grid.

You may assume the following rules:

A move is guaranteed to be valid and is placed on an empty block.
Once a winning condition is reached, no more moves is allowed.
A player who succeeds in placing n of their marks in a horizontal, vertical, or diagonal row wins the game.
Example:
Given n = 3, assume that player 1 is "X" and player 2 is "O" in the board.

TicTacToe toe = new TicTacToe(3);

toe.move(0, 0, 1); -> Returns 0 (no one wins)
|X| | |
| | | |    // Player 1 makes a move at (0, 0).
| | | |

toe.move(0, 2, 2); -> Returns 0 (no one wins)
|X| |O|
| | | |    // Player 2 makes a move at (0, 2).
| | | |

toe.move(2, 2, 1); -> Returns 0 (no one wins)
|X| |O|
| | | |    // Player 1 makes a move at (2, 2).
| | |X|

toe.move(1, 1, 2); -> Returns 0 (no one wins)
|X| |O|
| |O| |    // Player 2 makes a move at (1, 1).
| | |X|

toe.move(2, 0, 1); -> Returns 0 (no one wins)
|X| |O|
| |O| |    // Player 1 makes a move at (2, 0).
|X| |X|

toe.move(1, 0, 2); -> Returns 0 (no one wins)
|X| |O|
|O|O| |    // Player 2 makes a move at (1, 0).
|X| |X|

toe.move(2, 1, 1); -> Returns 1 (player 1 wins)
|X| |O|
|O|O| |    // Player 1 makes a move at (2, 1).
|X|X|X|


Follow up:
Could you do better than O(n^2) per move() operation?

 */


typedef struct 
{
	int size;
	int **board;
} TicTacToe;

/** Initialize your data structure here. */

TicTacToe* ticTacToeCreate(int n) 
{
	TicTacToe* obj = malloc(sizeof(TicTacToe));
	obj->size = n;
	obj->board = malloc(sizeof(int *)*n);
	for (int x = 0; x < n; x++)
	{
		obj->board[x] = malloc(sizeof(int)*n);
	}
	return obj;
}

/** Player {player} makes a move at ({row}, {col}).
  @param row The row of the board.
  @param col The column of the board.
  @param player The player, can be either 1 or 2.
  @return The current winning condition, can be either:
0: No one wins.
1: Player 1 wins.
2: Player 2 wins. */
int ticTacToeMove(TicTacToe* obj, int row, int col, int player) 
{
	obj->board[row][col] = player;

	int i;
	int n = obj->size;
	/* Check row => O(n) */ 
	for (i = 1; i < n; i++)
	{
		if (obj->board[row][i] != obj->board[row][i-1])
		{
			break;
		}
	}
	if (i == n)
	{
		return player;
	}
	/* Check col => O(n) */
	for (i = 1; i < n; i++)
	{
		if (obj->board[i][col] != obj->board[i-1][col])
		{
			break;
		}
	}
	if (i == n)
	{
		return player;
	}
	/* Check Slash => O(n) */
	if (col == row)
	{
		for (i = 1; i < n; i++)
		{
			if (obj->board[i][i] != obj->board[i-1][i-1])
			{
				break;
			}
		}
		if (i == n)
		{
			return player;
		}
	}
	/* Check backslash => O(n) */
	if (col+row == n-1)
	{
		for (i = 1; i < n; i++)
		{
			if (obj->board[i][n-i-1] != obj->board[i-1][n-i])
			{
				break;
			}
		}
		if (i == n)
		{
			return player;
		}
	}
	return 0;
}

void ticTacToeFree(TicTacToe* obj) 
{
	for (int x = 0; x < obj->size; x++)
	{
		free(obj->board[x]);
	}
	free(obj);
}

/**
 * Your TicTacToe struct will be instantiated and called as such:
 * TicTacToe* obj = ticTacToeCreate(n);
 * int param_1 = ticTacToeMove(obj, row, col, player);

 * ticTacToeFree(obj);
 */
