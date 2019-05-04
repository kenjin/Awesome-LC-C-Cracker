/**

221. Maximal Square [Medium]

Given a 2D binary matrix filled with 0's and 1's, find the largest square containing only 1's and return its area.

Example:

Input:
1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0

Output: 4

 */



bool checkLargerSquare(char **matrix, int row, int col, int edge)
{
    for (int i = row; i < (row+edge); i++)
    {
        for (int j = col; j < (col+edge); j++)
        {
            if (matrix[i][j] != '1')
            {
                return false;
            }            
        }        
    }
    return true;    
}

int maximalSquare(char** matrix, int matrixSize, int* matrixColSize){

    int maxEdge = 0;
    int colSize = matrixColSize[0];
    
    if (matrix == NULL)
    {
        return 0;
    }

    for (int i = 0; i < matrixSize; i++)
    {
        for (int j = 0; j < colSize; j++)
        {
            if (matrix[i][j] == '1')
            {
                int calEdge = 0;
                for (int x = (maxEdge+1); ((i+x) <= matrixSize && (j+x) <= colSize); x++)
                {
                    if (checkLargerSquare(matrix, i, j, x))
                    {
                        calEdge = x;
                    } else
                    {
                        calEdge = x-1;                        
                        break;
                    }
                }
                if (calEdge > maxEdge)
                {
                    maxEdge = calEdge;
                }
            }
        }
    }
    return maxEdge*maxEdge;
}
