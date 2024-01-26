#define MAX(a, b) (a > b ? a : b)
int maxProfit(int* prices, int pricesSize, int fee)
{
    int sold = 0, hold = -prices[0];
    for (int i = 1; i < pricesSize; i++) {
        int tmp = sold;
        sold = MAX(tmp, hold + prices[i] - fee);
        hold = MAX(hold, tmp - prices[i]); 
    }
    return sold;
}
