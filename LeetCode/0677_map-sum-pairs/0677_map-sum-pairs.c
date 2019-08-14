
typedef struct MapSumNode
{
	int val;
	struct MapSumNode *charNode[26];
} MapSum;

/** Initialize your data structure here. */

MapSum* mapSumCreate() 
{
	MapSum *obj = calloc(1, sizeof(MapSum));
	return obj;
}

void mapSumInsert(MapSum* obj, char * key, int val) 
{
	while (*key)
	{
		if (NULL == obj->charNode[*key - 'a'])
		{
			obj->charNode[*key - 'a'] = mapSumCreate();
		}
		obj = obj->charNode[*key - 'a'];
		key++;
	}
	obj->val = val;
}

int calChildSum(MapSum *head)
{    
	int tmp = head->val;
	for (int i = 0; i < 26; i++)
	{
		if (head->charNode[i])
		{
			tmp += calChildSum(head->charNode[i]);
		}
	}

	return tmp;
}

int mapSumSum(MapSum* obj, char * prefix) 
{
	while (*prefix)
	{
		if (obj == NULL)
		{
			break;
		}
		obj = obj->charNode[*prefix - 'a'];
		prefix++;
	}    
	return (obj == NULL ? 0 : calChildSum(obj));
}

void mapSumFree(MapSum* obj) 
{
	if (obj == NULL)
	{
		return;
	}

	for (int i = 0; i < 26; i++)
	{
		mapSumFree(obj->charNode[i]);
	}    
	free(obj);
}

/**
 * Your MapSum struct will be instantiated and called as such:
 * MapSum* obj = mapSumCreate();
 * mapSumInsert(obj, key, val);

 * int param_2 = mapSumSum(obj, prefix);

 * mapSumFree(obj);
 */
