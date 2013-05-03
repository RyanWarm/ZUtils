/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *reverseBetween(ListNode *head, int m, int n) {
        ListNode *result = NULL, *cur = head, *pre = NULL;
        while( m > 1 ) {
            pre = cur;
            cur = cur->next;
            m--;
            n--;
        }
        ListNode *h = pre, *t = cur;
        ListNode *next = cur->next, *tmp = next;
        while( n > 1 ) {
            tmp = next->next;
            next->next = cur;
            cur = next;
            next = tmp;
            n--;
        }
        if( h != NULL ) {
            h->next = cur;
            result = head;
        } else {
            result = cur;
        }
        t->next = tmp;
        return result;
    }
};