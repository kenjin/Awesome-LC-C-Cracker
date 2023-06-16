/**
	33. Search in Rotated Sorted Array [Medium]
	
	Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.
	
	(i.e., [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2]).
	
	You are given a target value to search. If found in the array return its index, otherwise return -1.
	
	You may assume no duplicate exists in the array.
	
	Your algorithm's runtime complexity must be in the order of O(log n).
	
	Example 1:
	
	Input: nums = [4,5,6,7,0,1,2], target = 0
	Output: 4
	Example 2:
	
	Input: nums = [4,5,6,7,0,1,2], target = 3
	Output: -1
 */

/* Standard Binary Search */
int binarySearch(int *nums, int left, int right, int target) 
{ 
    if (right < left)
    {
        return -1;
    } 
   
    int mid = left + (right-left)/2;
    if (target == nums[mid]) 
    {
        return mid;
    }
    if (target > nums[mid]) 
    {
        return binarySearch(nums, mid+1, right, target);
    } else
    {
        return binarySearch(nums, left, mid-1, target);
    }   
} 

/*
 *  [4,5,33,90,0,1,2]  Ex: 90 is pivot index
 *          ^
 *  - Find the pivot that is the index of the max num in array.
 *  - "return -1" means that we didn't find pivot index
 */
int findPivot(int *nums, int left, int right)
{
    if (right < left)
    {
        return -1;
    }
    if (right == left)
    {
        return right;
    }
    
    int mid = left + (right-left)/2;
    if (mid < right && nums[mid] > nums[mid+1])
    {
        return mid;
    }
    if (mid > left && nums[mid] < nums[mid-1])
    {
        return (mid-1);
    }
    
    /*
     *  [3, 4, 5, 0, 1, 2, 3]   => 0(mid) < 3(left)
     *                          => find "left half" [3, 4, 5]
     */
    if (nums[mid] <= nums[left])
    {
        return findPivot(nums, left, mid-1);
    } else
    /*
     *  [3, 4, 5, 6, 7, 1, 2]   => 6(mid) > 3(left)
     *                          => find "right half"  [7, 1, 2]
     */
    {
        return findPivot(nums, mid+1, right);
    }    
}

int search(int* nums, int numsSize, int target) {
    
    int rotatedPivot = findPivot(nums, 0, numsSize-1);
    

    // This case is that the array was not rotated at all 
    if (rotatedPivot == -1) 
    {
       return binarySearch(nums, 0, numsSize-1, target);
    }

    if (target == nums[rotatedPivot]) 
    {
        return rotatedPivot;
    }    
    if (nums[0] <= target)
    {
        return binarySearch(nums, 0, rotatedPivot-1, target);
    } else
    {
        return binarySearch(nums, rotatedPivot+1, numsSize-1, target); 
    }
    return 0;
}
    
