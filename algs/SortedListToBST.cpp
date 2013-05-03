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
/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
    TreeNode *toBST(ListNode *head, ListNode *tail) {
		cout << "inside to bst" << endl;
        if( head == NULL ) return NULL;
        if( head->next == NULL || head->next == tail ) return new TreeNode(head->val);
		cout << "node size >= 2" << endl;
        ListNode *s = head, *e = head;
        while( e->next != NULL ) {
            s = s->next;
            e = e->next;
            if( tail != NULL && e == tail ) break;
            if( e->next != NULL ) e = e->next;
            if( tail != NULL && e == tail ) break;
        }
		cout << "s: " << s->val << endl;
		cout << "e: " << e << endl;
        TreeNode *root = new TreeNode(s->val);
        TreeNode *left = toBST(head, s);
        TreeNode *right = toBST(s->next, e->next);
        root->left = left;
        root->right = right;
        return root;
    }
    TreeNode *sortedListToBST(ListNode *head) {
        return toBST(head, NULL);
    }
};
int main() {
	ListNode *head = new ListNode(3);
	ListNode *tmp = new ListNode(5);
	head->next = tmp;
	tmp = new ListNode(8);
	head->next->next = tmp;
	Solution solution;
	TreeNode *root = solution.sortedListToBST(head);
	cout << "result: " << root->val << ",left: " << root->left->val << ",right: " << root->right->val << endl;
	return 1;
}
