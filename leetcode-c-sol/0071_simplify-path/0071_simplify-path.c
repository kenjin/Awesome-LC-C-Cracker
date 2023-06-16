typedef struct
{
	int size;
	int cur;
	char **arr;
} STACK;

STACK* stackCreate(int size) 
{
	STACK *obj = malloc(sizeof(STACK));
	obj->size = size;
	obj->cur = -1;
	obj->arr = malloc(sizeof(char *)*size);
	return obj;
}

int getStackSize(STACK *obj)
{
	return obj->cur;    
}

bool stackIsEmpty(STACK *obj)
{
	return (obj->cur == -1 ? true : false);
}

void stackPush(STACK* obj, char *ptr)
{
	obj->cur += 1;
	obj->arr[obj->cur] = ptr;
}

char* stackPop(STACK* obj)
{
	if (stackIsEmpty(obj))
	{
		printf("WARNING: empty stack!\n");
		return NULL;
	}

	obj->cur -= 1;
	return obj->arr[obj->cur+1];
}

char* stackTop(STACK* obj)
{
	if (stackIsEmpty(obj))
	{
		return -1;
	}
	return obj->arr[obj->cur];
}

void stackFree(STACK* obj) 
{
	free(obj->arr);
	free(obj);
}

void stackUpdatePathBottomUp(STACK* s, char *path)
{
	for (int i = 0; i <= s->cur; i++)    
	{
		strcat(path, "/");
		strcat(path, s->arr[i]);
	}
}

char * simplifyPath(char * path)
{
	int len = strlen(path);
	if (len == 0)
	{
		return path;
	}

	// copy "tmp" string to do string parser
	STACK *s = stackCreate(len+1);
	char *tmp = calloc(len+1, sizeof(char)); 
	strcpy(tmp, path);

	char *delim = "/";
	char *pch = NULL;
	pch = strtok(tmp, delim);
	while (pch != NULL)
	{
		if (strlen(pch) == 2 && !strcmp(pch, ".."))
		{
			stackPop(s);
		} else if (strlen(pch) != 1 || strcmp(pch, "."))
		{
			stackPush(s, pch);
		}
		pch = strtok(NULL, delim);
	}      

	memset(path, 0, sizeof(char)*len);
	if (stackIsEmpty(s))
	{
		strcat(path, "/");
	} else
	{
		stackUpdatePathBottomUp(s, path);
	}

	free(tmp);
	stackFree(s);
	return path;
}


