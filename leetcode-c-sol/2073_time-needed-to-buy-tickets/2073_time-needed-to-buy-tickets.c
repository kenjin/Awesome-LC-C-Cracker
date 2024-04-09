/***

Assuming the target is equal to tickets[k], iterate through all elements of
tickets[]:
1. Accumulate directly those smaller than the target.
2. For those larger than the target and with an index greater than k
   (indicating they will be undersubtracted in the final round), accumulate
   target - 1.
3. For those larger than the target and with an index less than or equal to k,
   accumulate the target directly.

***/

int timeRequiredToBuy(int* tickets, int ticketsSize, int k)
{
    int ret = 0;
    for (int i = 0; i < ticketsSize; i++) {
        if (tickets[i] >= tickets[k]) {
            if (i > k)
                ret += (tickets[k] - 1);
            else
                ret += tickets[k];
        } else {
            ret += tickets[i];
        }
    }
    return ret;
}
