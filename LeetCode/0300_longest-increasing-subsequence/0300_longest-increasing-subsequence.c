
static int binary_search(int *arr, int size, int target)
{
	int left = 0;
	int right = size - 1;

	while (left < right) {
		int mid = (right - left) / 2 + left;
		if (arr[mid] == target)
			return mid;
		else if (arr[mid] < target)
			left = mid + 1;
		else
			right = mid;
	}

	return left;
}

int lengthOfLIS(int* nums, int numsSize)
{
	int arr[numsSize];
	int cur = 0;
	arr[0] = nums[0];
	for (int i = 1; i < numsSize; i++) {
		if (nums[i] > arr[cur]) {
			cur++;
			arr[cur] = nums[i];
		} else if (nums[i] < arr[cur]) {
			int idx = binary_search(arr, cur + 1, nums[i]);
			arr[idx] = nums[i];
		}
	}
	return cur + 1;
}
