
typedef struct trustInfo
{
	int inDegree;
	int outDegree;
} INFO;

int findJudge(int N, int** trust, int trustSize, int* trustColSize)
{
	if (trustSize == 0 && N == 1)
	{
		return 1;
	}

	INFO *d = calloc(N+1, sizeof(INFO));
	for (int i = 0; i < trustSize; i++)
	{
		d[trust[i][1]].inDegree += 1;
		d[trust[i][0]].outDegree -= 1;
	}

	int ret = -1;
	for (int i = 0; i < N+1; i++)
	{
		if (d[i].inDegree == N-1 && d[i].outDegree == 0)
		{
			ret = i;
			break;
		}
	}

	free(d);
	return ret;
}

