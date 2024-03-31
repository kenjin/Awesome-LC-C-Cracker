#define MIN(a, b) (a < b ? a : b)

// Approach: Sliding window
//
// Use the sliding window approach to check subarrays where all the elements are
// between minK and maxK. Track 'head' as the starting index of subarray,
// 'cur_min_idx' for the latest minK position, and 'cur_max_idx' for the latest
// maxK position. The formula calculates the possible combinations of the
// current subarray as: MIN(cur_min_idx, cur_max_idx) - head + 1.
//
// e.g.
// nums = [ x x x 1 . . . 5], minK = 1, maxK = 5
//          ^     #       #        (^: head idx, #: min/max idx of subarray)
// plus 4 combinations: [1 . . . 5]
//                      [x 1 . . . 5]
//                      [x x 1 . . . 5]
//                      [x x x 1 . . . 5]
// As long as the current element is within bounds, i.e., <
// maxK and > minK, new combinations can be added using the above formula.
//
// e.g.
// nums = [ x x x 1 . . . 5 2 3]
//          ^     #       #
// nums[] = 2, plus 4 combinations ([1 . . . 5 2], ..., [x x x 1 . . . 5 2])
// nums[] = 3  plus 4 combinations ([1 . . . 5 2 3], ..., [x x x 1 . . . 5 2 3])
//
// We may see the duplicate minK or maxK in a subarray, we need to update latest
// index so that to get new combinations and treat the previous one as an
// arbitrary element.
//
// e.g.
// nums = [ x x x 1 . . . 5 2 1]
//          ^             #   *    (*: New minK)
// plus new combinations: [5 2 1]
//                        [. 5 2 1]
//                        ...
//                        [1' . . . 5 2 1]
//                        [x 1' . . . 5 2 1]
//                        [x x 1' . . . 5 2 1]
//                        [x x x 1' . . . 5 2 1]
//
// If exceeding maxK or below minK, no need to examine the entire subarray and
// do reset. Reset intentionally sets 'cur_min_idx' and 'cur_max_idx' to -1, so
// that when the current subarray does not find minK or maxK, new combinations
// will not be added.
//
long long countSubarrays(int* nums, int numsSize, int minK, int maxK) {
    int cur_min_idx = -1, cur_max_idx = -1, head = 0;
    long long ret = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > maxK || nums[i] < minK) {
            // reset
            head = i + 1;
            cur_min_idx = -1;
            cur_max_idx = -1;
        }

        if (nums[i] == maxK)
            cur_max_idx = i;
        if (nums[i] == minK)
            cur_min_idx = i;

        int tmp = MIN(cur_min_idx, cur_max_idx) - head + 1;
        if (tmp > 0)
            ret += tmp;
    }
    return ret;
}

