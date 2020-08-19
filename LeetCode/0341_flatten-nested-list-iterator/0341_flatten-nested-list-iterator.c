/**
 * *********************************************************************
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * *********************************************************************
 *
 * // Return true if this NestedInteger holds a single integer, rather than a
 * nested list.
 * bool NestedIntegerIsInteger(struct NestedInteger *);
 *
 * // Return the single integer that this NestedInteger holds, if it holds a
 * single integer
 * // The result is undefined if this NestedInteger holds a nested list
 * int NestedIntegerGetInteger(struct NestedInteger *);
 *
 * // Return the nested list that this NestedInteger holds, if it holds a nested
 * list
 * // The result is undefined if this NestedInteger holds a single integer
 * struct NestedInteger **NestedIntegerGetList(struct NestedInteger *);
 *
 * // Return the nested list's size that this NestedInteger holds, if it holds a
 * nested list
 * // The result is undefined if this NestedInteger holds a single integer
 * int NestedIntegerGetListSize(struct NestedInteger *);
 * };
 */

#define ALLOC_UNIT_SIZE (10000)
struct NestedIterator {
    int *arr;
    int cur;
    int size;
    int allocate_unit;
};

static void nested_get_num(struct NestedInteger *cur,
                           struct NestedIterator *iter)
{
    if (NestedIntegerIsInteger(cur)) {
        if (0 == iter->size % iter->allocate_unit) {
            iter->arr = realloc(
                iter->arr, sizeof(int) * (iter->size + iter->allocate_unit));
        }
        iter->arr[(iter->size)++] = NestedIntegerGetInteger(cur);
        return;
    }

    int list_sz = NestedIntegerGetListSize(cur);
    struct NestedInteger **tmp = NestedIntegerGetList(cur);
    for (int i = 0; i < list_sz; i++)
        nested_get_num(tmp[i], iter);
}

struct NestedIterator *nestedIterCreate(struct NestedInteger **nestedList,
                                        int nestedListSize)
{
    struct NestedIterator *iter = malloc(sizeof(struct NestedIterator));
    iter->arr = malloc(sizeof(int));
    iter->allocate_unit = ALLOC_UNIT_SIZE;
    iter->size = iter->cur = 0;
    for (int i = 0; i < nestedListSize; i++) {
        struct NestedInteger *tmp = nestedList[i];
        nested_get_num(tmp, iter);
    }
    return iter;
}

bool nestedIterHasNext(struct NestedIterator *iter)
{
    return (iter->cur < iter->size);
}

int nestedIterNext(struct NestedIterator *iter)
{
    return iter->arr[(iter->cur)++];
}

/** Deallocates memory previously allocated for the iterator */
void nestedIterFree(struct NestedIterator *iter)
{
    free(iter->arr);
    free(iter);
}

/**
 * Your NestedIterator will be called like this:
 * struct NestedIterator *i = nestedIterCreate(nestedList, nestedListSize);
 * while (nestedIterHasNext(i)) printf("%d\n", nestedIterNext(i));
 * nestedIterFree(i);
 */