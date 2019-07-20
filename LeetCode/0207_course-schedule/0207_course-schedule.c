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

bool canFinish(int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize)
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

	int ctr = 0;
	for (int i = 0; i < numCourses; i++)
	{
		if (data[i].visited == 1)
		{
			continue;
		}
		// Get the vertex with 0 in-degree and remove the related edge
		if (data[i].inDegree == 0)
		{
			data[i].visited = 1;
			if (data[i].edgeHeadIdx != -1) // zero edge case
			{
				int size = data[i].edgeHeadIdx + data[i].edgeNum;
				for (int x = data[i].edgeHeadIdx; x < size; x++)
				{                    
					data[ prerequisites[x][0] ].inDegree -= 1;
				}      
			}                     
			ctr ++;
			// reset the scan index
			i = -1;
		}       
	}

	free(data);
	return (ctr == numCourses ? true : false);
}

