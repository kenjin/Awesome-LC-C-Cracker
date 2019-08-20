/**
 * *********************************************************************
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * *********************************************************************
 *
 * // Initializes an empty nested list and return a reference to the nested integer.
 * struct NestedInteger *NestedIntegerInit();
 *
 * // Return true if this NestedInteger holds a single integer, rather than a nested list.
 * bool NestedIntegerIsInteger(struct NestedInteger *);
 *
 * // Return the single integer that this NestedInteger holds, if it holds a single integer
 * // The result is undefined if this NestedInteger holds a nested list
 * int NestedIntegerGetInteger(struct NestedInteger *);
 *
 * // Set this NestedInteger to hold a single integer.
 * void NestedIntegerSetInteger(struct NestedInteger *ni, int value);
 *
 * // Set this NestedInteger to hold a nested list and adds a nested integer elem to it.
 * void NestedIntegerAdd(struct NestedInteger *ni, struct NestedInteger *elem);
 *
 * // Return the nested list that this NestedInteger holds, if it holds a nested list
 * // The result is undefined if this NestedInteger holds a single integer
 * struct NestedInteger **NestedIntegerGetList(struct NestedInteger *);
 *
 * // Return the nested list's size that this NestedInteger holds, if it holds a nested list
 * // The result is undefined if this NestedInteger holds a single integer
 * int NestedIntegerGetListSize(struct NestedInteger *);
 * };
 */


int depthSumHelper(struct NestedInteger *n, int lv)
{
	if (NestedIntegerIsInteger(n))
	{
		return lv * NestedIntegerGetInteger(n);
	}

	int nListSize = NestedIntegerGetListSize(n);
	struct NestedInteger **nList = NestedIntegerGetList(n);

	int sum = 0;
	for (int i = 0; i < nListSize; i++)
	{
		sum += depthSumHelper(nList[i], lv+1);        
	}
	return sum;
}

int depthSum(struct NestedInteger** nestedList, int nestedListSize)
{
	int sum = 0;

	for (int i = 0; i < nestedListSize; i++)
	{
		sum += depthSumHelper(nestedList[i], 1);
	}    
	return sum;
}


