typedef struct
{
	int size;
	int cur;
	char *arr;
} STACK;

STACK* stackCreate(int size) 
{
	STACK *obj = malloc(sizeof(STACK));
	obj->size = size;
	obj->cur = -1;
	obj->arr = malloc(sizeof(char)*size);
	return obj;
}

bool stackIsEmpty(STACK *obj)
{
	return (obj->cur == -1 ? true : false);
}

void stackPush(STACK* obj, char c)
{
	obj->cur += 1;
	obj->arr[obj->cur] = c;
}

char stackPop(STACK* obj)
{
	if (stackIsEmpty(obj))
	{
		printf("WARNING: empty stack!\n");
		return;
	}

	obj->cur -= 1;
	return obj->arr[obj->cur+1];
}

void stackFree(STACK* obj) 
{
	free(obj->arr);
	free(obj);
}

char * parseTernary(char * expression)
{
	int len = strlen(expression);
	STACK *s = stackCreate(len);
	for (int i = len-1; i >= 0; i--)
	{
		if (expression[i] == ':')
		{
			continue;
		} else if (expression[i] == '?')
		{
			i--;
			char c1 = stackPop(s);
			char c2 = stackPop(s);
			if (expression[i] == 'T')
			{
				stackPush(s, c1);
			} else
			{
				stackPush(s, c2);
			}
		} else
		{
			stackPush(s, expression[i]);
		}                
	}

	expression[0] = stackPop(s);
	expression[1] = 0;
	stackFree(s);    
	return expression;
}

