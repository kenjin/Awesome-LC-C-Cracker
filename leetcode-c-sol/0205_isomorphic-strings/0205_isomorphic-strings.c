
/*
 * Approach: Compare each character of the two strings one by one, use a Char
 * Hash (ascii[256]). If the current characters of the two strings appear for
 * the first time, then directly replace them with each other's characters. If
 * the current characters of the two strings have appeared before, then directly
 * use the Char Hash to check whether they match each other's characters. If
 * not, return false. If all characters have been successfully traversed, return
 * true."
 */
bool isIsomorphic(char* s, char* t) {
    char char_s_hash[256] = {0};
    char char_t_hash[256] = {0};

    for (int i = 0; s[i] != 0; i++) {
        if (char_s_hash[s[i]] == 0 && char_t_hash[t[i]] == 0) {
            char_s_hash[s[i]] = t[i];
            char_t_hash[t[i]] = s[i];
        } else {
            if (char_s_hash[s[i]] != t[i] || char_t_hash[t[i]] != s[i])
                return false;
        }
    }

    return true;
}

