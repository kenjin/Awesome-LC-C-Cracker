/**

394. Decode String [Medium]

Given an encoded string, return it's decoded string.

The encoding rule is: k[encoded_string], where the encoded_string 
inside the square brackets is being repeated exactly k times. Note that
k is guaranteed to be a positive integer.

You may assume that the input string is always valid; No extra white 
spaces, square brackets are well-formed, etc.

Furthermore, you may assume that the original data does not contain any 
digits and that digits are only for those repeat numbers, k. For 
example, there won't be input like 3a or 2[4].

Examples:

s = "3[a]2[bc]", return "aaabcbc".
s = "3[a2[c]]", return "accaccacc".
s = "2[abc]3[cd]ef", return "abcabccdcdcdef".

*/

typedef struct singly_linked_List
{
	int data;
	struct singly_linked_List *next;
} LIST_NODE;

typedef struct stack
{
	LIST_NODE *head;
} STACK;

/* Stack Implementation */
bool emptyStack(STACK *s)
{
	return (s->head == NULL ? true : false);
}

int popStack(STACK *s)
{
	if (emptyStack(s))
	{
		return (-1);
	}

	LIST_NODE *tmp = s->head->next;
	int ret = s->head->data;
	if (tmp == NULL)
	{
		free(s->head);
	}
	s->head = tmp;
	return ret;
}

void pushStack(STACK *s, int val)
{
	LIST_NODE *node = malloc(sizeof(LIST_NODE));
	node->data = val;

	LIST_NODE *tmp = s->head;
	if (tmp == NULL)
	{
		node->next = NULL;
	} else
	{
		node->next = tmp;
	}
	s->head = node;
}

void destroyStack(STACK *s)
{
	while (s->head != NULL)
	{
		LIST_NODE *tmp = s->head->next;
		free(s->head);
		s->head = tmp;
	}
	free(s);
}

STACK* createStack()
{
	STACK *s = malloc(sizeof(STACK));
	s->head = NULL;

	return s;
}

/* Stack(string) Implementation */
typedef struct singly_linked_List_str
{
	char *str;
	struct singly_linked_List_str *next;
} LIST_NODE_STR;

typedef struct stack_str
{
	LIST_NODE_STR *head;
} STACK_STR;

/* Stack Implementation */
bool emptyStack_str(STACK_STR *s)
{
	return (s->head == NULL ? true : false);
}

char* popStack_str(STACK_STR *s)
{
	if (emptyStack(s))
	{
		return NULL;
	}

	LIST_NODE_STR *tmp = s->head->next;
	char *ret = s->head->str;
	if (tmp == NULL)
	{
		free(s->head);
	}
	s->head = tmp;
	return ret;
}

void pushStack_str(STACK_STR *s, char *val)
{
	LIST_NODE_STR *node = malloc(sizeof(LIST_NODE_STR));
	node->str = val;

	LIST_NODE_STR *tmp = s->head;
	if (tmp == NULL)
	{
		node->next = NULL;
	} else
	{
		node->next = tmp;
	}
	s->head = node;
}

void destroyStack_str(STACK_STR *s)
{
	while (s->head != NULL)
	{
		LIST_NODE_STR *tmp = s->head->next;
		free(s->head);
		s->head = tmp;
	}
	free(s);
}

STACK_STR* createStack_str()
{
	STACK_STR *s = malloc(sizeof(STACK_STR));
	s->head = NULL;

	return s;
}


char* addString(char *s, char c, int size)
{
	s = realloc(s, sizeof(char)*size+1); // Reserve '\0' for last element
	s[size-1] = c;
	s[size] = 0;

	return s;
}

char * decodeString(char * s)
{
	int len = strlen(s);
	if (len == 0)
	{
		return "";
	}

	STACK *s1 = createStack(); // Store the repeat counter
	STACK_STR *s2 = createStack_str(); // Store tmp result string

	char *resStr = NULL;
	int resLen = 0;    
	int repeat = 0;
	for (int i = 0; i < len; i++)
	{
		if (s[i] == '[')
		{
			/* Push and clear the repeat counter*/
			pushStack(s1, repeat);
			repeat = 0;
			/* Push current result and re-create a result string */   
			pushStack_str(s2, resStr);
			resLen = 0;
			resStr = calloc(1, sizeof(char));
		} else if (s[i] == ']')
		{
			/* Pop previous string */
			char *prevStr = popStack_str(s2);
			int prevStrStrLen = 0;
			if (prevStr != NULL)
			{
				prevStrStrLen = strlen(prevStr);
			}

			/* Create tmp string buffer for repeated copy */
			char *tmpStr = calloc(resLen+1, sizeof(char));
			memcpy(tmpStr, resStr, sizeof(char)*resLen);

			/* Pop repeat conter for repeat of current result string */
			int repeatCtr = popStack(s1);
			int repeatStrLen = strlen(resStr);     
			/* Re-allocate current result string for new concat */
			resLen = prevStrStrLen + (repeatStrLen*repeatCtr);
			resStr = realloc(resStr, sizeof(char)*resLen + 1);

			/* Conbime "previous string" + (repeat)*"current string"   */
			if (prevStr != NULL)
			{
				memcpy(resStr, prevStr, sizeof(char)*prevStrStrLen);
			}
			for (int x = 0; x < repeatCtr; x++)
			{
				int copyIdx = prevStrStrLen + x*repeatStrLen;
				memcpy(&(resStr[copyIdx]), tmpStr, sizeof(char)*repeatStrLen);
			}
			resStr[resLen] = 0;

			/* Free useless memeory */
			free(prevStr);
			free(tmpStr);
		} else if ('0' <= s[i] && s[i] <= '9')
		{
			/* Calculate the repeat */
			repeat = 10 * repeat + (s[i] - '0');
		} else if (('a' <= s[i] && s[i] <= 'z') || 
				('A' <= s[i] && s[i] <= 'Z'))
		{
			resLen++;
			resStr = addString(resStr, s[i], resLen);
		}
	}

	destroyStack(s1);
	destroyStack_str(s2);
	return resStr;
}


