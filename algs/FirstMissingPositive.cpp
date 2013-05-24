class Solution {
public:
    int firstMissingPositive(int A[], int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if( n == 0 ) return 1;
        for( int i = 0; i < n; i++ ) {
            while( A[i] != i && A[i] < n && A[i] >= 0 ) {
                int tmp = A[i];
                if( A[i] == A[tmp] ) break;
                A[i] = A[tmp];
                A[tmp] = tmp;
            }
        }
        for( int i = 1; i < n; i++ ) {
            if( A[i] != i ) return i;
        }
        return n;
    }
};