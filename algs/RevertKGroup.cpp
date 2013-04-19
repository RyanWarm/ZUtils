#include <cstddef>
#include <iostream>
using namespace std;
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
public:
    ListNode *doRevert(ListNode **head, ListNode *pre, ListNode *post, int k) {
		cout << "r: " << (*head)->val << "," << (pre == NULL ? -1 : pre->val) << "," << (post == NULL ? -1 : post->val) << endl;
        ListNode *n1, *result;
        if( pre == NULL ) {
            n1 = *head;        
        } else {
            n1 = pre->next;
        }
        ListNode *n2 = n1->next;
        ListNode *n3 = n2->next;
        int i = 0;
		cout << 1 << endl;
        while( i < k-1 ) {
            n2->next = n1;
            n1 = n2;
            n2 = n3;
            if( n3 != NULL ) n3 = n3->next;
            i++;
        }
		cout << 2 << endl;
        if( pre == NULL ) {
            (*head)->next = post;
            result = (*head);
            *head = n1;
        } else {
            pre->next->next = post;
            result = pre->next;
            pre->next = n1;
        }
		cout << 3 << endl;
        return result;
    }
    ListNode *reverseKGroup(ListNode *head, int k) {
		cout << "inside" << endl;
        if( k == 0 || k == 1 ) return head;
        ListNode *cur = head;
        int i = 0;
        ListNode *pre = NULL, *post;
        while( cur != NULL ) {
            i++;
			cout << "val: " << cur->val << endl;
			cout << "i: " << i << endl;
            if( i == k ) {
                post = cur->next;
                pre = doRevert(&head, pre, post, k);
				cur = pre;
                i = 0;
            }
            cur = cur->next;
        }
		cout << "head: " << head->val << endl;
        return head;
    }
};
int main() {
	ListNode *head;
	ListNode *tmp = new ListNode(1);
	cout << "0" << endl;
	head = tmp;
	ListNode *tmp1 = new ListNode(2);
	cout << "1" << endl;
	tmp1->val = 2;
	tmp->next = tmp1;
	tmp = new ListNode(3);
	tmp1->next = tmp;
	Solution s;
	ListNode *r = s.reverseKGroup(head, 2);
	return 1;
}
