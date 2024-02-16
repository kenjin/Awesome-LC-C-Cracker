/*
 * Approach: DP
 * - dp[i][j] represents the len of the longest subarray with matching digits
 *   at the end of first i digits of arr nums1 and first j digits of arr nums2.
 * - Wherever the dp value is non-zero, it corresponds to the situation when
 *   nums1[i] == nums2[j], and we need to add the dp value from the top-left
 *   corner, which is dp[i-1][j-1]. So current dp[i][j] = dp[i-1][j-1] + 1.
 * - Once nums1[i] != nums2[j], we directly assign the value to 0 because we 
 *   don't need to consider further.
 */
int findLength(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int** dp = malloc(sizeof(int*) * (nums1Size + 1));
    for (int i = 0; i <= nums1Size; i++)
        dp[i] = calloc(nums2Size + 1, sizeof(int));

    int max = 0;
    for (int i = 1; i <= nums1Size; i++) {
        for (int j = 1; j <= nums2Size; j++) {
            if (nums1[i - 1] == nums2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                max = (max > dp[i][j] ? max : dp[i][j]);
            }
        }
    }

    for (int i = 0; i <= nums1Size; i++)
        free(dp[i]);
    free(dp);
    return max;
}
