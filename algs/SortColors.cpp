#include <iostream>
using namespace std;

class Solution {
public:
	void swap(int A[], int i, int j) {
		int tmp = A[i];
		A[i] = A[j];
		A[j] = tmp;
	}
	void sortColors(int A[], int n) {
		if( n == 0 ) return;
		int s1 = 0, s2 = 0, s3 = 0;
		while( s3 < n ) {
			if( A[s3] == 1 ) {
				swap(A, s2++, s3);
			} else if( A[s3] == 0 ) {
				swap(A, s2, s3);
				swap(A, s1++, s2++);
			}
			s3++;
		}
	}
};

int main() {
	Solution solution;
	int A[] = {2,1,1,0,2,0};
	solution.sortColors(A, 6);
	for( int i = 0; i < 6; i++ ) {
		cout << A[i] << " ";
	}
	cout << endl;
	return 1;
}
