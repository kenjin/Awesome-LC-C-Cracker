/**
286. Walls and Gates [Medium]

You are given a m x n 2D grid initialized with these three possible values.

-1 - A wall or an obstacle.
0 - A gate.
INF - Infinity means an empty room. We use the value 231 - 1 = 2147483647 to represent INF as you may assume that the distance to a gate is less than 2147483647.
Fill each empty room with the distance to its nearest gate. If it is impossible to reach a gate, it should be filled with INF.

Example:

Given the 2D grid:

INF  -1  0  INF
INF INF INF  -1
INF  -1 INF  -1
  0  -1 INF INF

After running your function, the 2D grid should be:

  3  -1   0   1
  2   2   1  -1
  1  -1   2  -1
  0  -1   3   4

  */

void DFS(int** rooms, int rSize, int cSize, int i, int j, int len)
{
    if (i < 0 || i >= rSize || j < 0 || j >= cSize || rooms[i][j] < len)
    {
        return;
    }
    rooms[i][j] = len;
    DFS(rooms, rSize, cSize, i + 1, j, len + 1);
    DFS(rooms, rSize, cSize, i - 1, j, len + 1);
    DFS(rooms, rSize, cSize, i, j + 1, len + 1);
    DFS(rooms, rSize, cSize, i, j - 1, len + 1);
}

void wallsAndGates(int** rooms, int roomsSize, int* roomsColSize){
    if (!roomsSize)
    {
        return;
    }

    int colSize = roomsColSize[0];
    for (int i = 0; i < roomsSize; i++)
    {
        for (int j = 0; j < colSize; j++)
        {
            if (rooms[i][j] == 0)
            {
                DFS(rooms, roomsSize, colSize, i, j, 0);
            }
        }
    }
}


