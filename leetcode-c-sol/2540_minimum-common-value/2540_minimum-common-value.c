
int getCommon(int* nums1, int nums1Size, int* nums2, int nums2Size)
{
    int i = 0, j = 0;
    while (i < nums1Size && j < nums2Size) {
        if (nums1[i] == nums2[j])
            return nums1[i];
        if (nums1[i] < nums2[j])
            i += 1;
        else
            j += 1;
    }

    return -1;
}

