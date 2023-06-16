/**
 *
 * Given an array of 4 digits, return the largest 24 hour time that can
 * be made. The smallest 24 hour time is 00:00, and the largest is 23:59.
 * Starting from 00:00, a time is larger if more time has elapsed since
 * midnight. Return the answer as a string of length 5. If no valid time
 * can be made, return an empty string.
 *
 * Example 1:
 * Input: [1,2,3,4]
 * Output: "23:41"
 *
 * Example 2:
 * Input: [5,5,5,5]
 * Output: ""
 *
 * Note:
 * - A.length == 4
 * - 0 <= A[i] <= 9
 *
 */

static bool check_set(char *ret, int *num_set, int ret_idx)
{
    int limit = 9;
    switch (ret_idx) {
    case 0:
        limit = 2;
        break;
    case 1:
        if (ret[0] == '2')
            limit = 3;
        break;
    case 2:
        return check_set(ret, num_set, ret_idx + 1);
    case 3:
        limit = 5;
        break;
    case 5:
        return true;
    default:
        break;
    }

    bool found = false;
    for (int i = limit; i >= 0; i--) {
        if (num_set[i]) {
            num_set[i] -= 1;
            ret[ret_idx] = i + '0';
            if (check_set(ret, num_set, ret_idx + 1)) {
                found = true;
                break;
            }
            num_set[i] += 1;
        }
    }
    if (!found)
        return false;

    return true;
}

char *largestTimeFromDigits(int *A, int ASize)
{
    char *ret = calloc(6, sizeof(char));
    int num_set[10] = {0};
    for (int i = 0; i < 4; i++)
        num_set[A[i]] += 1;

    if (!check_set(ret, num_set, 0))
        return "";

    ret[2] = ':';
    return ret;
}