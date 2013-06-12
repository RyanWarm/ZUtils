/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
#include <vector>
#include <iostream>
using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};
struct HeapNode {
    int val;
    int index;
    HeapNode(int x, int y) : val(x), index(y) {}
};
class Solution {
public:
    void heap_push(vector<HeapNode *> &heap, HeapNode *in) {
		cout << endl;
        int len = heap.size();
        heap.push_back(in);
        int c = len, p = (c-1)/2;
        while( p >= 0 ) {
            if( heap[c]->val < heap[p]->val ) {
                HeapNode *tmp = heap[c];
                heap[c] = heap[p];
                heap[p] = tmp;
                c = p;
                p = (c-1)/2;
            } else {
                break;
            }
        }
		cout << endl;
    }
    HeapNode *heap_pop(vector<HeapNode *> &heap) {
		bool print = false;
		if( heap[0]->val == -2 ) print = true;
		int len = heap.size();
        HeapNode *result = heap[0];
        heap[0] = heap[len-1];
        heap.pop_back();
        len--;
		if( print ) cout << len << endl;
        if( len > 1 ) {
            int p = 0, c1 = p*2+1, c2 = p*2+2;
			if( print ) cout << "c1: " << c1 << ",c2: " << c2 << endl;
            while( c1 < len || c2 < len ) {
                if( c2 < len ) {
                    if( heap[c1]->val > heap[c2]->val ) c1 = c2;
                }
                if( heap[p]->val > heap[c1]->val ) {
					if( print ) {
						cout << "========pop start=======" << endl;
						for( vector<HeapNode *>::iterator it = heap.begin(); it != heap.end(); ++it ) {
							cout << (*it)->val << "," << (*it)->index << ";";
						}
						cout << endl;
					}
					if( print ) cout << "c1: " << c1 << ",p: " << p << endl;
                    HeapNode *tmp = heap[c1];
                    heap[c1] = heap[p];
                    heap[p] = tmp;
                    p = c1;
                    c1 = p*2+1;
                    c2 = p*2+2;
					if( print ) {
						cout << "========pop after=======" << endl;
						for( vector<HeapNode *>::iterator it = heap.begin(); it != heap.end(); ++it ) {
							cout << (*it)->val << "," << (*it)->index << ";";
						}
						cout << endl;
					}
                } else {
                    break;
                }
            }
        }
        return result;
    }
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int len = lists.size();
        if( len == 0 ) return NULL;
        vector<HeapNode *> heap;
        for( int i = 0; i < len; i++ ) {
            if( lists[i] == NULL ) continue;
            HeapNode *cur = new HeapNode(lists[i]->val, i);
            heap_push(heap, cur);
            lists[i] = lists[i]->next;
        }
        ListNode *result = NULL, *tmp = NULL;
        while( !heap.empty() ) {
            HeapNode *cur = heap_pop(heap);
            int cur_val = cur->val;
            int cur_index = cur->index;
            ListNode *n = new ListNode(cur_val);
            if( result == NULL ) {
                result = n;
                tmp = n;
            } else {
                tmp->next = n;
                tmp = tmp->next;
            }
            if( lists[cur_index] != NULL ) {
                HeapNode *in = new HeapNode(lists[cur_index]->val, cur_index);
                heap_push(heap, in);
                lists[cur_index] = lists[cur_index]->next;
            }
        }
        return result;
    }
};
int main() {
	Solution solution;
	vector<ListNode *> input;
	ListNode *l1 = new ListNode(-1);
	input.push_back(l1);
	ListNode *tmp = new ListNode(1);
	l1->next = tmp;
	ListNode *l2 = new ListNode(-3);
	input.push_back(l2);
	tmp = new ListNode(1);
	l2->next = tmp;
	l2 = l2->next;
	tmp = new ListNode(4);
	l2->next = tmp;
	ListNode *l3 = new ListNode(-2);
	input.push_back(l3);
	tmp = new ListNode(-1);
	l3->next = tmp;
	l3 = l3->next;
	tmp = new ListNode(0);
	l3->next = tmp;
	l3 = l3->next;
	tmp = new ListNode(2);
	l3->next = tmp;

	ListNode *result = solution.mergeKLists(input);
	return 1;
}
