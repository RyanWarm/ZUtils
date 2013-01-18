#include <iostream>

using namespace std;

void doInterleave( char* a, char* b, char* result, int lena, int lenb, int ia, int ib );
void printStr( char* a, int length );

int main() {
	char a[] = "ABCD";
	char b[] = "1234";
	int lena = strlen(a);
	int lenb = strlen(b);
	char r[lena+lenb];
	doInterleave( a, b, r, lena, lenb, 0, 0 );
	return 0;
}

void doInterleave( char* a, char* b, char* result, int lena, int lenb, int ia, int ib ) {
	if( ia < lena ) {
		*(result+ia+ib) = a[ia];
		ia++;
		if( (ia+ib) == (lena+lenb) ) {
			printStr( result, ia+ib );
			return;
		}
		doInterleave( a, b, result, lena, lenb, ia, ib );
		ia--;
	}
	if( ib < lenb ) {
		*(result+ia+ib) = b[ib];
		ib++;
		if( (ia+ib) == (lena+lenb) ) {
			printStr( result, ia+ib );
			return;
		}
		doInterleave( a, b, result, lena, lenb, ia, ib );
		ib--;
	}
}

void printStr( char* a, int length ) {
	for( int i = 0; i < length; i++ ) {
		cout << *(a+i);
	}
	cout << endl;
}
