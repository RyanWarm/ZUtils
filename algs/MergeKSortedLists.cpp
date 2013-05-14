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

class Solution {
public:
	int parent(int i) {
		return (i-1)/2;
	}
	int left(int i) {
		return i*2+1;
	}
	int right(int i) {
		return i*2+2;
	}
	int swap(int heap[], int i, int j) {
		int tmp = heap[i];
		heap[i] = heap[j];
		heap[j] = tmp;
	}
	void siftDown(int heap[], int size) {
		int i = 0;
		int l = left(i);
		int r = right(i);
		int t;
		while( l < size && r < size ) {
			if( heap[i] > heap[l] && heap[i] > heap[r] ) {
				if( heap[l] > heap[r] ) {
					swap(i,r);
					i = r;
				} else {
					swap(i,l);
					i = l;
				}
			} else if( heap[i] > heap[l] ) {
				swap(i,l);
				i = l;
			} else if( heap[i] > heap[r] ) {
				swap(i,r);
				i = r;
			} else {
				break;
			}
			l = left(i);
			r = right(i);
		}
		if( l < size && heap[i] > heap[l] ) swap(i,l);
	}
	void heapUp(int heap[], int i) {
		int p = parent(i);
		while( p >= 0 ) {
			if( heap[i] < heap[p] ) {
				swap(i,p);
				i = p;
			} else {
				break;
			}
			p = parent(i);
		}
	}
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int k = lists.size();
		if( k == 0 ) return NULL;
		ListNode *result = NULL, *cur = NULL;
		int heap[k], size = 0;
		for( vector<ListNode *>::iterator it = lists.begin(); it != lists.end(); ++it ) {
			ListNode *tmp = *it;
			heap[size] = tmp->val;
			heapUp(heap, size);
			size++;
		}
		while( size > 0 ) {
			
		}
    }
};

int main() {

	return 1;
}
