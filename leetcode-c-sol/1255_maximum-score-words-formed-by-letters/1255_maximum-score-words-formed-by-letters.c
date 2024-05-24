
static int dfs(char** words, int words_size, int* cnt, int* score, int idx)
{
    int res = 0;
    for (int i = idx; i < words_size; ++i) {
        int sum = 0;
        bool is_valid = true;
        int word_len = strlen(words[i]);
        for (int j = 0; j < word_len; ++j) {
            char c = words[i][j];
            if (--cnt[c - 'a'] < 0)
                is_valid = false;
            sum += score[c - 'a'];
        }
        if (is_valid) {
            sum += dfs(words, words_size, cnt, score, i + 1);
            if (sum > res)
                res = sum;
        }
        for (int j = 0; j < word_len; ++j) {
            char c = words[i][j];
            ++cnt[c - 'a'];
        }
    }
    return res;
}

int maxScoreWords(char** words, int wordsSize, char* letters, int lettersSize,
                  int* score, int scoreSize)
{
    int cnt[26] = {0};
    for (int i = 0; i < lettersSize; ++i)
        ++cnt[letters[i] - 'a'];

    return dfs(words, wordsSize, cnt, score, 0);
}
