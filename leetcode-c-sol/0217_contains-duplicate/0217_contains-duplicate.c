
typedef struct __hash_table {
	int size;
	int *list;
} HASHER;

int hash(HASHER obj, int key)
{
	int r = key % obj.size;
	return r < 0 ? r + obj.size : r;
}

bool hash_find(HASHER ht, int *nums, int idx)
{
	int index = hash(ht, nums[idx]);
	while (ht.list[index] != -1) {
		if (nums[ht.list[index]] == nums[idx])
			return true;
		index++;
		index %= ht.size;
	}
	return false;
}

void hash_add(HASHER ht, int *nums, int idx)
{
	int index = hash(ht, nums[idx]);
	while (ht.list[index] != -1) {
		index++;
		index %= ht.size;
	}
	ht.list[index] = idx;
}


bool containsDuplicate(int* nums, int numsSize)
{
	HASHER obj;
	obj.list = calloc(numsSize, sizeof(int));
	for (int i = 0; i < numsSize; i++)
		obj.list[i] = -1;
	obj.size = numsSize;

	bool ret = false;
	for (int i = 0; i < numsSize; i++) {
		if (hash_find(obj, nums, i)) {
			ret = true;
			break;
		}
		hash_add(obj, nums, i);
	}

	free(obj.list);
	return ret;
}
