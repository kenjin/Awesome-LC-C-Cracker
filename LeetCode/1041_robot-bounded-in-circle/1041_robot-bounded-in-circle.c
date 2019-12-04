

bool isRobotBounded(char * instructions)
{
	int len = strlen(instructions);
	int pos[2] = {0, 0};
	int dir[4][2] = {{0, 1},  /* North */
		{1, 0},  /* East */
		{0, -1}, /* South */ 
		{-1, 0}  /* West */};
	int curDir = 0;
	for (int i = 0; i < len; i++)
	{
		if (instructions[i] == 'L')
		{
			curDir = (curDir + 1) % 4;            
		} else if (instructions[i] == 'R')
		{
			curDir = (curDir + 3) % 4;
		} else
		{
			pos[0] += dir[curDir][0];
			pos[1] += dir[curDir][1];
		}
	}


	return (pos[0] == 0 && pos[1] == 0) || curDir > 0;
}


