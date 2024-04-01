/***

Scan through the string word and keep track of the last occurrence position of
each vowel and the most recent occurrence position C of a consonant (initially
set to -1 for all vowels and consonants, indicating that they haven't occurred
yet).

When word[i] is a consonant, we update the index i (let's denote this idx as C).
If it's a vowel, we update the corresponding occurrence position for that vowel
type. Then, we iterate over all vowel types to find the earliest occurrence
position among them (let's denote it as V). If V < C, it means that the
substring word[V] to word[i] contains some consonants mixed in with the five
vowels, so it's not a vowel substring. Conversely, if V > C, then the
substrings:

- word[C + 1] to word[i]
- word[C + 2] to word[i]
- ...
- word[V] to word[i]

are all vowel substrings. (Total `V - C` substrings)


Time: O(n)
***/

static inline bool is_vowel(char letter) {
    if (letter == 'a' || letter == 'e' || letter == 'i' || letter == 'o' ||
        letter == 'u')
        return true;
    return false;
}

static inline int get_min(int* pos) {
    char vowels[5] = {'a', 'e', 'i', 'o', 'u'};
    int min = INT_MAX;
    for (int i = 0; i < 5; i++)
        min = (min < pos[vowels[i]] ? min : pos[vowels[i]]);

    return min;
}

int countVowelSubstrings(char* word) {
    int pos[128];
    int consonant_idx = -1, ret = 0;

    pos['a'] = pos['e'] = pos['i'] = pos['o'] = pos['u'] = -1;
    for (int i = 0; word[i]; i++) {
        if (is_vowel(word[i])) {
            pos[word[i]] = i;
            int cur_vowel_min = get_min(pos);
            if (cur_vowel_min > consonant_idx)
                ret += (cur_vowel_min - consonant_idx);
        } else {
            consonant_idx = i;
        }
    }
    return ret;
}
