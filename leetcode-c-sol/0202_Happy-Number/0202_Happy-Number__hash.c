/**

202. Happy Number [E]

Write an algorithm to determine if a number is "happy".

A happy number is a number defined by the following process: Starting 
with any positive integer, replace the number by the sum of the squares
of its digits, and repeat the process until the number equals 1 (where 
it will stay), or it loops endlessly in a cycle which does not include 
1. Those numbers for which this process ends in 1 are happy numbers.

Example: 

Input: 19
Output: true

Explanation: 
1^2 + 9^2 = 82
8^2 + 2^2 = 68
6^2 + 8^2 = 100
1^2 + 0^2 + 0^2 = 1

*/
#define HASH_SIZE (15000)
#define HASH_MOD  (15000)

typedef struct hashTable
{
	int bucket[HASH_SIZE]
}HASH;

HASH* createHash()
{
	HASH *h = malloc(sizeof(HASH));
	for (int x = 0; x < HASH_SIZE; x++)
	{
		h->bucket[x] = -1;
	}
	return h;
}

void addHash(HASH *h, int key)
{
	int hashIdx = key % HASH_MOD;

	while (h->bucket[hashIdx] != -1)
	{
		if (h->bucket[hashIdx] == key)
		{
			return;
		}
		hashIdx = (hashIdx+1) % HASH_SIZE;
	}

	h->bucket[hashIdx] = key;
}

bool findHash(HASH *h, int key)
{
	int hashIdx = key % HASH_MOD;

	while (h->bucket[hashIdx] != -1)
	{
		if (h->bucket[hashIdx] == key)
		{
			return true;
		}
		hashIdx = (hashIdx+1) % HASH_SIZE;
	}

	return false;
}

void destroyHash(HASH *h)
{
	free(h);
}

int checkHappy(int n)
{
	int target = n;

	int sum = (target%10)*(target%10);    
	// Chech digit
	while ( (target/10) > 0)
	{              
		target /= 10;
		sum += (target%10)*(target%10);
	}

	return sum;
}

bool isHappy(int n)
{
	HASH *h = createHash();
	bool result = false;
	int ret = n;
	while (1)
	{      
		if (ret == 1)
		{
			result = true;
			break;
		} else
		{
			/* Record and check the loops endlessly in a cycle */
			if (!findHash(h, ret))
			{
				addHash(h, ret);
				ret = checkHappy(ret);
			} else
			{
				result = false;
				break;
			}            
		}
	}
	destroyHash(h);
	return  result;
}

