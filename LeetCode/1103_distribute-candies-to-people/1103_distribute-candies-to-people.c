
static inline void assign_rest(int *ret, int ctr, int candies, int num_people)
{
    int idx = 0;
    while (candies > 0 && ctr < candies) {
        ret[idx] += ctr;
        candies -= ctr;
        idx = (idx + 1) % num_people;
        ctr++;
    }
    ret[idx] += candies;
}

/**
   * Note: The returned array must be malloced, assume caller calls free().
    */
int *distributeCandies(int candies, int num_people, int *return_sz)
{
    int *ret = calloc(num_people, sizeof(int));
    *return_sz = num_people;

    int sum = (((1 + num_people) * num_people) >> 1);
    int round = 0;
    if (sum > candies)
        goto out;

    while (1) {
        round++;
        int cur = (((((1 + round * num_people) << 1) + num_people - 1) *
                    num_people) >>
                   1);
        if ((sum + cur) > candies) {
            candies -= sum;
            break;
        }
        sum += cur;
    }

    for (int i = 0; i < num_people; i++)
        ret[i] = ((((i << 1) + num_people * (round - 1) + 2) * round) >> 1);

out:
    assign_rest(ret, 1 + round * num_people, candies, num_people);
    return ret;
}
