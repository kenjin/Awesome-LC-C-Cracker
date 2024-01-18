int lengthOfLongestSubstring(char* s)
{
    // Use 0 to check is used or not, so index start from 1.
    int set[128] = {0}, len = strlen(s), cur = 0, prev_dup_idx = 0, max = 0;
    for (int i = 0; i < len; i++) {
        int dup_idx = set[s[i]] - 1;
        // If no duplicate or the dup idx is an older index.
        if (dup_idx == -1 || dup_idx < prev_dup_idx) {
            cur++;
        } else {
            cur = (i - dup_idx);
            prev_dup_idx = dup_idx;
        }
        max = (max > cur ? max : cur);
        set[s[i]] = i + 1;
    }
    int tmp = len - prev_dup_idx - 1;
    max = (max > tmp ? max : tmp);
    return max;
}
