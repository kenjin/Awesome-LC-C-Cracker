bool isValid(int curX, int curY, int rowSize, int colSize, int **maze)
{
	return (curX >= 0 && curX < rowSize && curY >= 0 && curY < colSize && 0 == maze[curX][curY]);
}

bool mazeHelper(int **maze, int rowSize, int colSize, int **visit, int curX, int curY, int *end)
{
	int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

	if (!isValid(curX, curY, rowSize, colSize, maze) || visit[curX][curY])
	{
		return false;
	}

	if (curX == end[0] && curY == end[1])
	{
		return true;
	}

	visit[curX][curY] = 1;
	for (int x = 0; x < 4; x++)
	{
		int nextX = curX, nextY = curY;
		while (1)
		{
			nextX += dir[x][0];
			nextY += dir[x][1];
			if (isValid(nextX, nextY, rowSize, colSize, maze))
			{
				continue;
			} else
			{
				nextX -= dir[x][0];
				nextY -= dir[x][1];
				break;
			}
		}
		if (mazeHelper(maze, rowSize, colSize, visit, nextX, nextY, end))
		{
			return true;
		}
	}

	return false;
}

bool hasPath(int** maze, int mazeSize, int* mazeColSize, int* start, int startSize, int* destination, int destinationSize)
{
	int colSize = mazeColSize[0];
	int **visit = malloc(sizeof(int *)*mazeSize);
	for (int i = 0; i < mazeSize; i++)
	{
		visit[i] = calloc(colSize, sizeof(int));
	}

	bool ret = mazeHelper(maze, mazeSize, colSize, visit, start[0], start[1], destination);


	for (int i = 0; i < mazeSize; i++)
	{
		free(visit[i]);
	}
	free(visit);

	return ret;
}


