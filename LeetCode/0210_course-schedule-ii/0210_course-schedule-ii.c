
struct nodeInfo
{
	int inDegree;
	int edgeHeadIdx;
	int edgeNum;
	int visited;
};

int compare(const void *a, const void *b)
{
	const int *n1 = *(int **)a;
	const int *n2 = *(int **)b;

	return n1[1] - n2[1];
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findOrder(int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize, int* returnSize)
{
	// sort the vertex order for edge calculation
	qsort(prerequisites, prerequisitesSize, sizeof(int *), compare);

	struct nodeInfo *data = calloc(numCourses, sizeof(struct nodeInfo));
	for (int i = 0; i < numCourses; i++)
	{
		// init to zero edge
		data[i].edgeHeadIdx = -1;
	}    
	for (int i = 0; i < prerequisitesSize; i++)
	{
		// Update in-degree
		data[ prerequisites[i][0] ].inDegree += 1;
		// Update edge path
		data[ prerequisites[i][1] ].edgeNum     = (data[ prerequisites[i][1] ].edgeHeadIdx == -1 ? 
				1 : data[ prerequisites[i][1] ].edgeNum + 1);
		data[ prerequisites[i][1] ].edgeHeadIdx = (data[ prerequisites[i][1] ].edgeHeadIdx == -1 ? 
				i : data[ prerequisites[i][1] ].edgeHeadIdx);
	}

	// Init result
	int *ret = malloc(sizeof(int)*numCourses);
	*returnSize = 0;
	// Topology Ordering
	char foundNode = 0;
	char *tmpChk = calloc(numCourses, sizeof(char));
	int ctr = 0;
	for (int i = 0; i <= numCourses; i++)
	{
		if (i == numCourses)
		{
			if (foundNode)
			{
				foundNode = 0;
				memset(tmpChk, 0, sizeof(char)*numCourses);
				i = -1;
				continue;
			} else
			{
				break;
			}
		}
		// Get the vertex with 0 in-degree and remove the related edge
		if (!data[i].visited && data[i].inDegree == 0 && !tmpChk[i])
		{
			foundNode = 1;
			data[i].visited = 1; 
			if (data[i].edgeHeadIdx != -1) // ignore zero edge case
			{
				int size = data[i].edgeHeadIdx + data[i].edgeNum;
				for (int x = data[i].edgeHeadIdx; x < size; x++)
				{                    
					data[ prerequisites[x][0] ].inDegree -= 1;
					tmpChk[ prerequisites[x][0] ] = 1;
				}      
			}
			ret[ctr] = i;
			ctr ++;
		}
	}

	*returnSize = (ctr == numCourses ? ctr : 0);

	free(tmpChk);
	free(data);
	return ret;
}

