
bool validateIndex(int idx, int size)
{
    return (idx < 0 || idx >= size) ? false : true;  
}

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size)
{
    int *arr1 = (nums1Size <= nums2Size) ? nums1 : nums2;
    int *arr2 = (nums1 == arr1) ? nums2 : nums1;
    int arr1Size = (nums1Size < nums2Size) ? nums1Size : nums2Size;
    int arr2Size = (nums1Size == arr1Size) ? nums2Size : nums1Size;

    // if one of the array is empty
    if (arr1Size == 0)
    {
        if (arr2Size & 0x01)
        {
            return arr2[arr2Size/2];
        } else
        {
            // remember to return double type result
            return (double)(arr2[arr2Size/2-1]+arr2[arr2Size/2])/2;
        }
    }

    int totalArrSize = arr1Size + arr2Size;
    int a1 = arr1Size/2 - 1;
    int a2 = a1 + 1;
    int b1 = totalArrSize/2 - arr1Size/2 - 1;
    int b2 = b1 + 1;
    while (1)
    {
        // Find the answer
        if ((!validateIndex(b2, arr2Size) || !validateIndex(a1, arr1Size) || arr1[a1] < arr2[b2]) && 
            (!validateIndex(b1, arr2Size) || !validateIndex(a2, arr1Size) || arr2[b1] <= arr1[a2]))
        {
            break;
        }
        if (validateIndex(b2, arr2Size) && validateIndex(a1, arr1Size) && arr1[a1] >= arr2[b2])
        {
            a1--;
            a2--;
            b1++;
            b2++;
        } else if (validateIndex(b1, arr2Size) && validateIndex(a2, arr1Size) && arr2[b1] > arr1[a2])
        {
            a1++;
            a2++;
            b1--;
            b2--;
        } else
        {
            // one of [a1, b2] and one of [a2, b1] are invalid, no need to check anymore.
            //
            // test case: arr1=[100], arr2=[101]
            //
            break;
        }
    }

    double minHalf = 0, maxHalf = 0;
    if (!validateIndex(a1, arr1Size))
    {
        maxHalf = arr2[b1];
    } else if (!validateIndex(b1, arr2Size))
    {
        maxHalf = arr1[a1];
    } else
    {
        maxHalf = arr1[a1] > arr2[b1] ? arr1[a1] : arr2[b1];
    }

    if (!validateIndex(a2, arr1Size))
    {
        minHalf = arr2[b2];
    } else if (!validateIndex(b2, arr2Size))
    {
        minHalf = arr1[a2];
    } else
    {
        minHalf = arr1[a2] < arr2[b2] ? arr1[a2] : arr2[b2];
    }
    
    if (totalArrSize & 0x1)
    {
        return minHalf;
    } else
    {
        return (minHalf+maxHalf)/2;
    }
}

