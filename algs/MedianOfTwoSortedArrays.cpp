#include <iostream>
using namespace std;

class Solution {
public:
double doFinding(int a[], int sa, int ea, int b[], int sb, int eb) {
        int size_a = ea - sa + 1;
        int size_b = eb - sb + 1;
        if( size_a <= 2 ) return finalFind(a, sa, ea, b, sb, eb);
        if( size_b <= 2 ) return finalFind(b, sb, eb, a, sa, ea);
      
        int mid_a = a[(ea-sa)/2+sa];
        int mid_b = b[(eb-sb)/2+sb];
        int exc = 0;
        if( size_a > size_b ) {
            exc = size_b/2;
        } else {
            exc = size_a/2;
        }
       
        if( mid_a == mid_b ) {
           return mid_a;
        } else if( mid_a < mid_b ) {
           return doFinding(a, sa+exc, ea, b, sb, eb-exc);
        } else {
            return doFinding(a, sa, ea-exc, b, sb+exc, eb);
        }
    }

    double findMedianSortedArrays(int A[], int m, int B[], int n) {
        if( m == 0 ) {
            if( n % 2 == 0 ) return (B[n/2-1]+B[n/2])/(double)2;
            else return B[n/2];
        }
        if( n == 0 ) {
            if( m % 2 == 0 ) return (A[m/2-1]+A[m/2])/(double)2;
            else return A[m/2];
        }
      
        if( m >= n ) return doFinding(B, 0, n-1, A, 0, m-1);
        else return doFinding(A, 0, m-1, B, 0, n-1);
    }
  
    double finalFind(int a[], int sa, int ea, int b[], int sb, int eb) {
        int size_a = ea - sa + 1;
        int size_b = eb - sb + 1;
        int tmp_b1, tmp_b2;
        if( size_a == 2 ) {
            if( size_b % 2 == 0 ) {
                tmp_b1 = b[(sb+eb)/2];
                tmp_b2 = b[(sb+eb)/2+1];
                if( a[ea] < tmp_b1 ) return (a[ea]+tmp_b1)/(double)2;
                else if( a[ea] >= tmp_b1 && a[ea] <= tmp_b2 ) {
                    if( a[sa] < tmp_b1 ) return (a[ea]+tmp_b1)/(double)2;
                    else return (a[sa]+a[ea])/(double)2;
                } else {
                    // a[ea] > tmp_b2
                    if( a[sa] < tmp_b1 ) return (tmp_b1+tmp_b2)/(double)2;
                    else return (a[sa]+tmp_b2)/(double)2;
                }
            } else {
                // size_b is odd
                tmp_b1 = b[(sb+eb)/2];
                if( a[ea] < tmp_b1 ) return a[ea];
                else {
                    if( a[sa] < tmp_b1 ) return tmp_b1;
                    else return a[sa];
                }
            }
        } else {
            // size_a is 1
            if( size_b % 2 == 0 ) {
                tmp_b1 = b[(sb+eb)/2];
                tmp_b2 = b[(sb+eb)/2+1];
                if( a[sa] < tmp_b1 ) return tmp_b1;
                else if( a[sa] >= tmp_b1 && a[sa] <= tmp_b2 ) return a[sa];
                else return tmp_b2;
            } else {
                // size_b is odd
                int ib = (sb+eb)/2;
                tmp_b1 = b[ib];
                if( a[sa] < tmp_b1 ) {
                    if( ib == 0 ) return (a[sa]+tmp_b1)/(double)2;
                    else if( a[sa] < b[ib-1] ) return (tmp_b1+b[ib-1])/(double)2;
                    else return (a[sa]+tmp_b1)/(double)2;
                } else {
                    // a[sa] >= tmp_b1
                    if( ib == sizeof(b)/sizeof(b[0]) - 1 ) return (a[sa]+tmp_b1)/(double)2;
                    else if( a[sa] < b[ib+1] ) return (a[sa]+tmp_b1)/(double)2;
                    else return (tmp_b1+b[ib+1])/(double)2;
                }
            }
        }
    }
};

int main() {
	int a[] = {1,2,3,4};
	int b[] = {1,3,4,5};
	int sa = sizeof(a)/sizeof(a[0]);
	int sb = sizeof(b)/sizeof(b[0]);
	Solution s;
	double r = s.findMedianSortedArrays(a, sa, b, sb);
	cout << r << endl;

	return 1;
}
