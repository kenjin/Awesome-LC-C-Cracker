#define MAX_OPERATIONS    (300)
#define TIME_STR_SIZE       (20)

typedef struct
{
	int idx;
	char str[TIME_STR_SIZE];
} DATA;

typedef struct 
{
	int curSize;
	DATA arr[MAX_OPERATIONS];    
} LogSystem;


LogSystem* logSystemCreate() 
{
	LogSystem *obj = calloc(1, sizeof(LogSystem));
	return obj;
}

void logSystemPut(LogSystem* obj, int id, char * timestamp) 
{
	obj->arr[obj->curSize].idx = id;
	strcpy(obj->arr[obj->curSize].str, timestamp);
	obj->curSize ++;
}

int getEndLengthFromUnit(char *gra)
{
	if (!strcmp(gra, "Year"))
	{
		return 4;
	} else if (!strcmp(gra, "Month"))
	{
		return 7;
	} else if (!strcmp(gra, "Day"))
	{
		return 10;
	} else if (!strcmp(gra, "Hour"))
	{
		return 13;
	} else if (!strcmp(gra, "Minute"))
	{
		return 16;
	} else 
	{
		return 19;
	}
}

int* logSystemRetrieve(LogSystem* obj, char * s, char * e, char * gra, int* retSize) 
{
	int *ret = malloc(sizeof(int)*MAX_OPERATIONS);
	*retSize = 0;

	int endUnit = getEndLengthFromUnit(gra);
	for (int i = 0; i < obj->curSize; i++)
	{
		if (strncmp(obj->arr[i].str, s, endUnit) >= 0 &&
				strncmp(obj->arr[i].str, e, endUnit) <= 0)
		{
			ret[*retSize] = obj->arr[i].idx;
			*retSize += 1;
		}
	}

	return ret;
}

void logSystemFree(LogSystem* obj) 
{
	free(obj);
}

/**
 * Your LogSystem struct will be instantiated and called as such:
 * LogSystem* obj = logSystemCreate();
 * logSystemPut(obj, id, timestamp);

 * int* param_2 = logSystemRetrieve(obj, s, e, gra, retSize);

 * logSystemFree(obj);
 */
