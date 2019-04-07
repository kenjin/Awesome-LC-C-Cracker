/**
Given a 2d grid map of '1's (land) and '0's (water), count the number of
islands. An island is surrounded by water and is formed by connecting 
adjacent lands horizontally or vertically. You may assume all four 
edges of the grid are all surrounded by water.

Example 1:

Input:
11110
11010
11000
00000

Output: 1
Example 2:

Input:
11000
11000
00100
00011

Output: 3

*/

void findNeighborDfs(char **grid, int i /* row */, int j /* col */, int maxRow, int maxCol)
{
    if (i < 0 || j < 0 || i > (maxRow-1) || j > (maxCol-1) || grid[i][j] != '1')
    {
        return ;
    } else
    {
        grid[i][j] = '0';
        findNeighborDfs(grid, i+1, j, maxRow, maxCol);
        findNeighborDfs(grid, i-1, j, maxRow, maxCol);
        findNeighborDfs(grid, i, j+1, maxRow, maxCol);
        findNeighborDfs(grid, i, j-1, maxRow, maxCol);
    }
}

int numIslands(char** grid, int gridRowSize, int gridColSize) {
    int ret = 0;
    
    for (int i = 0; i < gridRowSize; i++)
    {
        for (int j = 0; j < gridColSize; j++)
        {
            ret += grid[i][j] - '0';
            findNeighborDfs(grid, i, j, gridRowSize, gridColSize);                        
        }
    }

    return ret;
}

