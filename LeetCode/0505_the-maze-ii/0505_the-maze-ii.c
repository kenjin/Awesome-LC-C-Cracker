#define MIN(a, b) (a < b ? a : b)

bool isValid(int curX, int curY, int rowSize, int colSize, int **maze)
{
	return (curX >= 0 && curX < rowSize && curY >= 0 && curY < colSize && 0 == maze[curX][curY]);
}

void
mazeHelper(int **maze, int rowSize, int colSize, int **cost, int curX, int curY)
{
	int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
	for (int x = 0; x < 4; x++)
	{
		int nextX = curX, nextY = curY;
		int curStep = 0;
		while (1)
		{            
			nextX += dir[x][0];
			nextY += dir[x][1];
			curStep++;
			if (isValid(nextX, nextY, rowSize, colSize, maze))
			{
				continue;
			} else
			{
				nextX -= dir[x][0];
				nextY -= dir[x][1];
				curStep--;
				break;
			}
		}

		if (cost[curX][curY] + curStep < cost[nextX][nextY])
		{
			cost[nextX][nextY] = cost[curX][curY]+curStep;
			mazeHelper(maze, rowSize, colSize, cost, nextX, nextY);
		}
	}
}

int shortestDistance(int** maze, int mazeSize, int* mazeColSize, int* start, int startSize, int* destination, int destinationSize)
{
	int colSize = mazeColSize[0];
	int **cost = malloc(sizeof(int *)*mazeSize);
	for (int i = 0; i < mazeSize; i++)
	{
		cost[i] = calloc(colSize, sizeof(int));
		memset(cost[i], 1, sizeof(int)*colSize);
	}

	int min = INT_MAX;
	cost[start[0]][start[1]] = 0;
	cost[destination[0]][destination[1]] = INT_MAX;
	mazeHelper(maze, mazeSize, colSize, cost, start[0], start[1]);

	int ret = (cost[destination[0]][destination[1]] == INT_MAX ? -1 : cost[destination[0]][destination[1]]);
	for (int i = 0; i < mazeSize; i++)
	{
		free(cost[i]);
	}
	free(cost);

	return ret;
}

