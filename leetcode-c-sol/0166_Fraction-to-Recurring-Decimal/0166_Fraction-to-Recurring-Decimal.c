/**

166. Fraction to Recurring Decimal [M]
Ref: https://leetcode.com/problems/fraction-to-recurring-decimal/


Given two integers representing the numerator and denominator of a fraction, return the fraction in string format.
If the fractional part is repeating, enclose the repeating part in parentheses.

Example 1:
Input: numerator = 1, denominator = 2
Output: "0.5"

Example 2:
Input: numerator = 2, denominator = 1
Output: "2"

Example 3:
Input: numerator = 2, denominator = 3
Output: "0.(6)"

 */
typedef struct nodeInfo NODE;
struct nodeInfo
{
	int key;
	int idx;
	NODE *next;
};

typedef struct hashInfo
{
	int size;
	int mod;
	NODE **bucket;
} HASH;

NODE *createNode()
{
	NODE *newOne = malloc(sizeof(NODE));
	newOne->idx = -1;
	newOne->next = NULL;
	return newOne;
}

HASH *createHash(int size)
{
	HASH *obj = malloc(sizeof(HASH));
	obj->size = size;
	obj->mod = size;
	obj->bucket = malloc(sizeof(NODE *)*size);
	for (int i = 0; i < size; i++)
	{
		obj->bucket[i] = createNode();
	}    
	return obj;
}

void destroyHash(HASH *obj)
{
	for (int i = 0; i < obj->size; i++)
	{
		NODE *delTmp = obj->bucket[i];
		while(delTmp)
		{
			NODE *tmp = delTmp->next;
			free(delTmp);
			delTmp = tmp;
		}
	}
	free(obj->bucket);
	free(obj);
}

void addHash(HASH *obj, int key, int pos)
{
	int hashIdx = key % obj->mod;

	NODE *newOne = createNode();
	/* Fist empty bucket */
	if (obj->bucket[hashIdx]->idx == -1)
	{

		obj->bucket[hashIdx]->idx = pos;
		obj->bucket[hashIdx]->key = key;
		obj->bucket[hashIdx]->next = newOne;
	} else
	{
		NODE *tmp = obj->bucket[hashIdx];
		while (tmp->idx != -1)
		{
			tmp = tmp->next;
		}
		tmp->idx = pos;
		tmp->key = key;
		tmp->next = newOne;
	}
}

int findHash(HASH *obj, int key)
{
	int hashIdx = key % obj->mod;
	NODE *tmp = obj->bucket[hashIdx];

	while (tmp->idx != -1)
	{
		if (tmp->key == key)
		{
			return tmp->idx;
		}
		tmp = tmp->next;
	}

	return -1;
}

#define MALLOC_STR_UNIT (300)
char* addChar(char *s, int *sSize, char *str)
{
	int len = strlen(s);
	int addLen = strlen(str);
	if (len+addLen >= *sSize)
	{
		*sSize = len+addLen+MALLOC_STR_UNIT;
		s = realloc(s, sizeof(char)*(*sSize));
	}

	for (int x = 0; x < addLen; x++)
	{
		s[len+x] = str[x];
	}
	s[len+addLen] = '\0';

	return s;
}

char * fractionToDecimal(int numerator, int denominator)
{
	/* Return 0 directly, avoid zero divide by negative number cause "-0" case */
	if (numerator == 0)
	{
		return "0";
	}

	char str[12] = {0};
	char *ret = calloc(1, sizeof(char));
	int retSize = 0;

	HASH *hash = createHash(30000);

	long numer = (long)numerator;
	long denom = (long)denominator;
	int sign = 0;
	if (numer < 0)
	{
		sign ^= 1;
		numer *= -1;
	}
	if (denom < 0)
	{
		sign ^= 1;
		denom *= -1;
	}

	long quotient = numer/denom;
	long remain = numer%denom;
	/* 
	 * Calculate Integer Part
	 *
	 * Notice:
	 * 1. Negative case
	 * 2. Need to use long type
	 * 3. Use %ld
	 *    (have chance to convert INT_MIN(-2147483648) to 2147483648)
	 */
	if (sign)
	{
		sprintf(str, "-%ld", quotient);
	} else
	{
		sprintf(str, "%ld", quotient);
	}
	ret = addChar(ret, &retSize, str);

	/* Calculate Fractional Part */
	char *fraction = calloc(1, sizeof(char));
	int fractionSize = 0;
	char recurring = 0;
	int pos = 0;
	while (remain > 0)
	{
		/* Use hash to check rucurring case */
		if (findHash(hash, remain) >= 0)
		{
			recurring = 1;
			break;
		} else
		{
			addHash(hash, remain, pos);
		}

		long tmp = remain*10;
		memset(str, 0, sizeof(char)*12);    
		sprintf(str, "%d", tmp/denom);
		fraction = addChar(fraction, &fractionSize, str);
		pos++;

		remain = tmp % denom;
	}

	if (fractionSize != 0)
	{
		ret = addChar(ret, &retSize, ".");
		int concatLen = strlen(fraction);        
		if (recurring)
		{
			int replacePosition = findHash(hash, remain);
			char *parenthesesStr = calloc(concatLen+2+1, sizeof(char));
			/* concat non-recurring part */
			strncpy(parenthesesStr, fraction, replacePosition);
			/* concat recurring part */
			strcpy(&(parenthesesStr[replacePosition]), "(");
			strcpy(&(parenthesesStr[replacePosition+1]), &(fraction[replacePosition]));
			strcpy(&(parenthesesStr[concatLen+1]), ")");

			ret = addChar(ret, &retSize, parenthesesStr);
			free(parenthesesStr);
		} else
		{
			ret = addChar(ret, &retSize, fraction);
		}
	}

	free(fraction);
	destroyHash(hash);
	return ret;
}
