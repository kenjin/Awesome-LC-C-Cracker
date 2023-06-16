/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2)
{
	if (!list1)
		return list2;
	if (!list2)
		return list1;

	struct ListNode *ret, *cur;
	if (list1->val < list2->val) {
		ret = list1;
		list1 = list1->next;
	} else {
		ret = list2;
		list2 = list2->next;
	}

	cur = ret;
	while (list1 && list2) {
		if (list1->val < list2->val) {
			cur->next = list1;
			cur = list1;
			list1 = list1->next;
		} else {
			cur->next = list2;
			cur = list2;
			list2 = list2->next;
		}
	}

	if (list1)
		cur->next = list1;
	if (list2)
		cur->next = list2;

	return ret;
}


struct ListNode* mergeKLists(struct ListNode** lists, int listsSize)
{
	if (!listsSize)
		return NULL;

	while (listsSize > 1) {
		int k = (listsSize + 1) / 2;
		for (int i = 0; i < listsSize / 2; i++) {
			lists[i] = mergeTwoLists(lists[i], lists[i + k]);
		}
		listsSize = k;
	}

	return lists[0];
}
