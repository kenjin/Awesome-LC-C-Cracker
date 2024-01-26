#define MAX(a, b) (a > b ? a : b)
int maxProfit(int* prices, int pricesSize, int fee)
{
    int *sold = malloc(sizeof(int)*pricesSize);    
    int *hold = malloc(sizeof(int)*pricesSize);
    sold[0] = 0;
    hold[0] = -prices[0];
    for (int i = 1; i < pricesSize; i++) {
        sold[i] = MAX(sold[i-1], hold[i-1] + prices[i] - fee);
        hold[i] = MAX(hold[i-1], sold[i-1] - prices[i]); 
    }
    int ret = sold[pricesSize - 1];
    free(sold);
    free(hold);
    return ret;
}
