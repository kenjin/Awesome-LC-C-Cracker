#define MAX(a, b) (a > b ? a : b)

int equalSubstring(char *s, char *t, int maxCost)
{
    int res = 0, n = strlen(s), cur = 0, start = 0;
    for (int i = 0; i < n; ++i) {
        cur += abs(s[i] - t[i]);
        while (cur > maxCost && start <= i) {
            cur -= abs(s[start] - t[start]);
            start++;
        }
        res = MAX(res, i - start + 1);
    }
    return res;
}
