#define MOD (1000000007)
#define SLEN_MAX (100001)

static int fast_pow(int base, int power)
{
    long long answer = 1;
    long long buffer = base;
    while (power) {
        if (power & 1)
            answer = (answer * buffer) % MOD;
        buffer = buffer * buffer % MOD;
        power >>= 1;
    }
    return (int)answer;
}

int countAnagrams(char* s)
{
    int ret = 1;
    const char *delim= " ";
    char *token = NULL;

    // prepare factorials
    int factorials[SLEN_MAX] = {0};
    int factorials_inverse[SLEN_MAX] = {0};
    factorials[0] = 1;
    factorials[1] = 1;
    factorials_inverse[0] = 1;
    factorials_inverse[1] = 1;
    for (int i = 2; i < SLEN_MAX; i++) {
        factorials[i] = (long long)factorials[i - 1] * i % MOD;
        factorials_inverse[i] = fast_pow(factorials[i], MOD - 2);
    }

    token = strtok(s, delim);
    while (token) {
        int slen = strlen(token);
        int h[26] = {0};
        for (int i = 0; i < slen; i++) {
            h[token[i]-'a']++;
        }
        int tmp = factorials[slen];
        for (int i = 0; i < 26; i++) {
            tmp = (long long)tmp * factorials_inverse[h[i]] % MOD;
        }

        ret = (long long)ret * tmp % MOD;
        token = strtok(NULL, delim);
    }
    return ret;
}
