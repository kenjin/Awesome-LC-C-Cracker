/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

int list_len(struct ListNode *root)
{
	int len = 0;
	while (root) {
		len++;
		root = root->next;
	}
	return len;
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2)
{

	int len1 = list_len(l1);
	int len2 = list_len(l2);

	struct ListNode *root, *list1, *list2, *prev = NULL;
	if (len1 > len2) {
		list1 = l1;
		list2 = l2;
	} else {
		list1 = l2;
		list2 = l1;
	}
	root = list1;
	int sum = 0, carry = 0;
	while (list1 || list2) {
		int list2_val = 0;
		if (list2) {
			list2_val = list2->val;
			list2 = list2->next;
		}
		sum = list1->val + list2_val + carry;
		carry = sum / 10;
		list1->val = sum % 10;
		prev = list1;
		list1 = list1->next;
	}

	if (carry) {
		prev->next = malloc(sizeof(struct ListNode));
		prev->next->val = 1;
		prev->next->next = NULL;
	}
	return root;
}
