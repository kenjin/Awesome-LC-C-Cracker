/***

Solution Approach:

#Data Structure Setup
Use a structure str_arr_t to store the result sentences. This struct includes
an array of strings (data), the current size of the array (size), and its
capacity (capacity). Initialize the str_arr_t with a specific capacity and
provide functions to add strings to this array. Helper Functions:

#Recursive Backtracking
The main recursive function wb is designed to explore all possible ways to
break the string word into valid words found in the dictionary. The function 
operates by iterating over all possible prefixes of the current string. For 
each prefix that is found in the dictionary, it calls itself recursively with 
the remaining part of the string. During each recursive call, it constructs a 
new sentence by appending the valid prefix to the current result.

#Base Case
When the length of the current string(word) is zero, it means a valid sentence
has been formed using words from the dictionary. This sentence is added to the
result array.

***/
#define MAX_STR_LEN (10)

// Define a string array to store results
typedef struct {
    char** data;
    int size;
    int capacity;
} str_arr_t;

static inline void init_str_arr(str_arr_t* array, int capacity) {
    array->data = (char**)malloc(sizeof(char*) * capacity);
    array->size = 0;
    array->capacity = capacity;
}

static inline void add_str_arr(str_arr_t* array, char* str) {
    if (array->size == array->capacity) {
        array->capacity <<= 1;
        array->data =
            (char**)realloc(array->data, sizeof(char*) * array->capacity);
    }
    array->data[array->size++] = strdup(str);
}

// is_in_dict():
// - A helper function to check if a given word exists in the word dictionary.
static inline bool is_in_dict(char* word, char** word_dict,
                              int word_dict_size) {
    for (int i = 0; i < word_dict_size; ++i) {
        if (!strcmp(word, word_dict[i]))
            return true;
    }
    return false;
}


void wb(char* word, char* res, char** word_dict, int word_dict_size,
        str_arr_t* ans) {
    int word_len = strlen(word);
    if (word_len == 0) {
        add_str_arr(ans, res);
        return;
    }

    for (int i = 1; i <= word_len; ++i) {
        char left[i + 1];
        strncpy(left, word, i);
        left[i] = '\0';
        if (is_in_dict(left, word_dict, word_dict_size)) {
            char right[word_len - i + 1];
            strcpy(right, word + i);

            int new_len =
                strlen(res) + i + 2; // Including space and null terminator
            char new_res[new_len];
            if (!strlen(res))
                strcpy(new_res, left);
            else
                snprintf(new_res, new_len, "%s %s", res, left);

            wb(right, new_res, word_dict, word_dict_size, ans);
        }
    }
}

char** wordBreak(char* s, char** word_dict, int word_dict_size,
                 int* return_size) {
    str_arr_t ans;
    init_str_arr(&ans, MAX_STR_LEN);

    char initial_res[1] = "";
    wb(s, initial_res, word_dict, word_dict_size, &ans);

    *return_size = ans.size;
    return ans.data;
}

