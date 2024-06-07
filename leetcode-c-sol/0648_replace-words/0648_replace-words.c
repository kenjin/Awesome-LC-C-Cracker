/***

Approach: Trie

The solution uses a trie (prefix tree) to store root words from the dictionary,
allowing for efficient prefix searches. Each node in the trie represents a
character and has an array of children pointers and a flag is_root. This flag is
used to store the index of the root word from the dictionary, but it is stored
as a 1-indexed value (i.e., the actual index plus one). This allows the code to
distinguish between an unset flag (value 0) and a set flag (positive value).

The add_trie function inserts words into the trie, navigating through the
characters of each word and creating new nodes as needed. When it reaches the
end of a word, it sets the is_root flag to the 1-indexed value of the dictionary
index.

The find_trie function searches for the shortest root word that matches a prefix
in the trie. It navigates through the trie according to the characters of the
word. If it finds a node where is_root is set, it returns the 0-indexed
dictionary index by subtracting one from the is_root value. If no root word
matches the prefix, it returns -1.

The replaceWords function processes the input sentence by tokenizing it into
words, then replaces each word with its corresponding root word found in the
trie, if available. If no root word is found, the original word is retained.
After processing, the function returns the modified sentence and frees all
memory used for the trie. This approach ensures efficient word replacement in
the sentence by leveraging the trie's prefix search capabilities and the
1-indexed is_root flag to store dictionary indices.

***/

typedef struct __trie {
    struct __trie* alpha[26];
    char is_root;
} trie_t;

static int find_trie(trie_t* t, char* str) {
    while (*str) {
        int idx = *str - 'a';
        if (!t->alpha[idx])
            return -1;
        t = t->alpha[idx];
        if (t->is_root >= 1) {
            return t->is_root - 1;
        }
        str++;
    }
    return t->is_root - 1;
}

static void add_trie(trie_t* t, char* str, int idx) {
    while (*str) {
        int idx = *str - 'a';
        if (!t->alpha[idx])
            t->alpha[idx] = calloc(1, sizeof(trie_t));
        t = t->alpha[idx];
        str++;
    }
    t->is_root = idx + 1;
}

static inline void free_trie(trie_t* root) {
    if (!root)
        return;

    for (int i = 0; i < 26; i++)
        free_trie(root->alpha[i]);

    free(root);
}

char* replaceWords(char** dictionary, int dictionarySize, char* sentence) {
    trie_t* t = calloc(1, sizeof(trie_t));
    for (int i = 0; i < dictionarySize; i++)
        add_trie(t, dictionary[i], i);

    char* tmp = calloc(strlen(sentence) + 1, sizeof(char));
    char *delim = " ", *token = strtok(sentence, delim);

    // Process first token
    int find_idx = find_trie(t, token);
    if (find_idx >= 0)
        strcat(tmp, dictionary[find_idx]);
    else
        strcat(tmp, token);

    // Process the rest of token
    token = strtok(NULL, delim);
    while (token) {
        strcat(tmp, " ");
        find_idx = find_trie(t, token);
        if (find_idx >= 0)
            strcat(tmp, dictionary[find_idx]);
        else
            strcat(tmp, token);

        token = strtok(NULL, delim);
    }

    memcpy(sentence, tmp, sizeof(char) * (strlen(tmp) + 1));
    // release memory
    free(tmp);
    free_trie(t);
    return sentence;
}
