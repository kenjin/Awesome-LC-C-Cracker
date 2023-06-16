
#define ARR_SIZE_UNIT 5000
typedef struct __data {
    int price;
    int span;
} DATA;

typedef struct {
    DATA *arr;
    int cur;
} StockSpanner;


StockSpanner *stockSpannerCreate()
{
    StockSpanner *obj = malloc(sizeof(StockSpanner));
    obj->arr = malloc(sizeof(DATA));
    obj->cur = 0;
    return obj;
}

int stockSpannerNext(StockSpanner *obj, int price)
{
    int cur = obj->cur;
    if (cur % ARR_SIZE_UNIT == 0)
        obj->arr = realloc(obj->arr, sizeof(DATA) * (cur + ARR_SIZE_UNIT));
    int ret = 1, cmp_idx = cur;
    while (cmp_idx > 0 && obj->arr[cmp_idx - 1].price <= price) {
        ret += obj->arr[cmp_idx - 1].span;
        cmp_idx = cmp_idx - obj->arr[cmp_idx - 1].span;
    }
    obj->arr[cur].price = price;
    obj->arr[cur].span = ret;
    obj->cur = cur + 1;
    return ret;
}

void stockSpannerFree(StockSpanner *obj)
{
    free(obj->arr);
    free(obj);
}

/**
 * Your StockSpanner struct will be instantiated and called as such:
 * StockSpanner* obj = stockSpannerCreate();
 * int param_1 = stockSpannerNext(obj, price);

 * stockSpannerFree(obj);
 */
