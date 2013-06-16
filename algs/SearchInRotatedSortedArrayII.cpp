#include <iostream>
using namespace std;

class Solution {
public:
    bool rangeSearch(int A[], int start, int end, int target, int last) {
		cout << "range search: " << start << "," << end << endl;
        if( start > end ) return false;
        if( start == end ) return A[start] == target;
        int mid = (start+end)/2;
        if( target == A[mid] ) return true;
        if( target > A[mid] ) {
            if( A[mid] == A[last] ) {
                int t = mid+1;
                while( t <= end ) {
                    if( A[t] != A[mid] ) break;
					t++;
                }
                if( t > end ) return rangeSearch(A, start, mid-1, target, last);
                else return rangeSearch(A, t, end, target, last);
            } else if( A[mid] < A[last] ) {
                if( target == A[last] ) return true;
                else if( target > A[last] ) return rangeSearch(A, start, mid-1, target, last);
                else return rangeSearch(A, mid+1, end, target, last);
            } else {
                return rangeSearch(A, mid+1, end, target, last);
            }
        } else {
            if( A[mid] == A[last] ) {
                int t = mid+1;
                while( t <= end ) {
                    if( A[t] != A[mid] ) break;
					t++;
                }
                if( t > end ) return rangeSearch(A, start, mid-1, target, last);
                else return rangeSearch(A, t, end, target, last);
            } else if( A[mid] < A[last] ) {
                return rangeSearch(A, start, mid-1, target, last);
            } else {
                if( target == A[last] ) return true;
                else if( target > A[last] ) return rangeSearch(A, start, mid-1, target, last);
                else return rangeSearch(A, mid+1, end, target, last);
            }
        }
    }
    bool search(int A[], int n, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        return rangeSearch(A, 0, n-1, target, n-1);
    }
};
int main() {
	Solution solution;
	int A[4] = {1,1,3,1};
	bool result = solution.search(A, 4, 0);
	if( result ) cout << "found" << endl;
	else cout << "not found" << endl;
	return 1;
}
