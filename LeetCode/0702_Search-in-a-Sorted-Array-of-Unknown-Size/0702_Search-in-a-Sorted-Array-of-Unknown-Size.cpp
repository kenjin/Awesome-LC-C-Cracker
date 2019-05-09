/**

702. Search in a Sorted Array of Unknown Size [M]

Ref: https://leetcode.com/problems/search-in-a-sorted-array-of-unknown-size/

 */

// Forward declaration of ArrayReader class.
class ArrayReader;

class Solution {
	public:
		int search(const ArrayReader& reader, int target) {
			/* Find the limitation of array size */
			int sizeLimit= 1;
			while (reader.get(sizeLimit) < target) 
			{   
				sizeLimit *= 2;
			}
			/* Binary Search */
			int head = sizeLimit/2;
			int tail = sizeLimit;
			while (head <= tail) 
			{
				int mid = head + (tail-head)/2;
				if (reader.get(mid) > target) 
				{
					tail = mid-1;
				} else if (reader.get(mid) < target)
				{
					head = mid+1;
				} else 
				{
					return mid;
				}
			}
			return -1;
		}
};
