// The rand7() API is already defined for you.
// int rand7();
// @return a random integer in the range 1 to 7

int rand10()
{
    int ret = -1;
    while (1) {
        ret = (rand7() - 1) * 7 + rand7();
        if (ret <= 40)
            return ret % 10 + 1;
    }
    return ret;
}
