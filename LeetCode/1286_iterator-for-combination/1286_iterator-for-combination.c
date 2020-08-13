
typedef struct {
    int *idx;
    char *ret;
    char *str;
    int cur;
    int total;
    int slen;
    int comb_len;
} CombinationIterator;

static inline cal(int a, int b)
{
    int sum = 1, div = 1;
    for (int i = 1; i <= b; i++) {
        sum *= a;
        a--;
        div *= i;
    }
    return (sum / div);
}

CombinationIterator *combinationIteratorCreate(char *characters,
                                               int combinationLength)
{
    CombinationIterator *obj = malloc(sizeof(CombinationIterator));
    obj->ret = calloc(combinationLength + 1, sizeof(char));
    obj->idx = malloc(sizeof(int) * combinationLength);
    obj->comb_len = combinationLength;
    obj->slen = strlen(characters);
    obj->str = calloc(obj->slen + 1, sizeof(char));
    strcpy(obj->str, characters);

    for (int i = 0; i < combinationLength; i++) {
        obj->idx[i] = i;
    }
    obj->cur = 0;
    obj->total = cal(obj->slen, combinationLength);
    return obj;
}

static void check_overidx(int *idx, int cur, int limit, int accumulation)
{
    if (idx[cur] == limit) {
        check_overidx(idx, cur - 1, limit - 1, accumulation + 1);
    } else {
        int cnt = idx[cur] + 1;
        for (int i = 0; i <= accumulation; i++) {
            idx[cur + i] = cnt;
            cnt++;
        }
    }
}

char *combinationIteratorNext(CombinationIterator *obj)
{
    for (int i = 0; i < obj->comb_len; i++) {
        obj->ret[i] = obj->str[obj->idx[i]];
    }
    obj->cur += 1;

    if (obj->cur != obj->total)
        check_overidx(obj->idx, obj->comb_len - 1, obj->slen - 1, 0);

    return obj->ret;
}

bool combinationIteratorHasNext(CombinationIterator *obj)
{
    return (obj->cur < obj->total);
}

void combinationIteratorFree(CombinationIterator *obj)
{
    free(obj->idx);
    free(obj->str);
    free(obj->ret);
    free(obj);
}

/**
 * Your CombinationIterator struct will be instantiated and called as such:
 * CombinationIterator* obj = combinationIteratorCreate(characters,
 combinationLength);
 * char * param_1 = combinationIteratorNext(obj);

 * bool param_2 = combinationIteratorHasNext(obj);

 * combinationIteratorFree(obj);
*/