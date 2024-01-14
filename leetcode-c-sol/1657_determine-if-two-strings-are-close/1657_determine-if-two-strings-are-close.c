typedef struct __bucket {
    int val;
    int freq;
} bucket_t;

typedef struct __hash {
    int size;
    bucket_t *bucket;
} hash_t;

static inline int do_hash(hash_t h, int val)
{
    int ret = val % h.size;
    return (ret < 0 ? ret + h.size : ret);
}

static bool find_update_hash(hash_t h, int val)
{
    int hidx = do_hash(h, val);
    while (h.bucket[hidx].val != 0){
        if (h.bucket[hidx].val == val) {
            h.bucket[hidx].freq--;
            return true;
        }
        hidx = (hidx + 1) % h.size;
    }
    return false;
}

static void add_update_hash(hash_t h, int val)
{
    int hidx = do_hash(h, val);
    if (h.bucket[hidx].val != 0){
        if (h.bucket[hidx].val == val) {
            h.bucket[hidx].freq++;
            return ;
        }
        hidx = (hidx + 1) % h.size;
    }
    h.bucket[hidx].val = val;
    h.bucket[hidx].freq = 1;
}

bool closeStrings(char* word1, char* word2)
{
    int len1 = strlen(word1);
    int len2 = strlen(word2);
    if (len1 != len2)
        return false;

    bool ret = false;
    int set1[26] = {0}, set2[26] = {0};
    for (int i = 0; i < len1; i++) {
        set1[word1[i] - 'a']++;
        set2[word2[i] - 'a']++;
    }

    hash_t h = {.size = len1, .bucket = calloc(len1, sizeof(bucket_t))};
    for (int i = 0; i < 26; i++) {
        if (set1[i])
            add_update_hash(h, set1[i]);
    }

    for (int i = 0; i < 26; i++) {
        if (set2[i]) {
            // 1) Ensure that two strings consist of the same character(s).
            // 2) Esure the freq set should be the same
            if (!set1[i] || !find_update_hash(h, set2[i]))
                goto out;
        }
    }

    for (int i = 0; i < h.size; i++) {
        if (h.bucket[i].freq != 0)
            goto out;
    }

    ret = true;
out:
    free(h.bucket);
    return ret;
}
