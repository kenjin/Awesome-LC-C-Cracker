
int maxProfit(int *prices, int prices_sz)
{
    /* sanity check */
    if (!prices_sz)
        return 0;

    int profit = 0;
    /**
     * tran_head[i]: max profix from day 0 to day i
     * tran_tail[i]: max profix from day i to last day
     */
    int *tran_head = malloc(sizeof(int) * prices_sz);
    int *tran_tail = malloc(sizeof(int) * prices_sz);
    tran_head[0] = 0, tran_tail[prices_sz - 1] = 0;

    int min_idx = 0;
    for (int i = 1; i < prices_sz; i++) {
        int diff = prices[i] - prices[min_idx];
        tran_head[i] = (tran_head[i - 1] > diff ? tran_head[i - 1] : diff);
        min_idx = (prices[i] < prices[min_idx] ? i : min_idx);
    }

    int max_idx = prices_sz - 1;
    for (int i = prices_sz - 2; i >= 0; i--) {
        int diff = prices[max_idx] - prices[i];
        tran_tail[i] = (tran_tail[i + 1] > diff ? tran_tail[i + 1] : diff);
        max_idx = (prices[i] > prices[max_idx] ? i : max_idx);
    }
    /* calculate the possible max value of twice tranaction */
    for (int i = 1; i < prices_sz - 2; i++) {
        int cur = tran_head[i] + tran_tail[i + 1];
        profit = (profit > cur ? profit : cur);
    }
    /* consider one transaction case */
    profit =
        (profit > tran_head[prices_sz - 1] ? profit : tran_head[prices_sz - 1]);
    /* release memory */
    free(tran_head);
    free(tran_tail);
    return profit;
}
