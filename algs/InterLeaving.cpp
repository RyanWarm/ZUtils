/*
 * InterLeave.cpp
 *
 *  Created on: 2013-1-14
 *      Author: apple
 */
#include <iostream>
using namespace std;

bool isInterLeave(char* A, char* B, char* C) {
  int lena = strlen(A);
	int lenb = strlen(B);
	int lenc = strlen(C);

	if( lenc != (lena + lenb) ) return false;

	int indexa = 0, indexb = 0, indexc = 0;
	int prea = -1, preb = -1;

	while( indexc < lenc ) {
		if( A[indexa] != B[indexb] ) {
			if( A[indexa] == C[indexc] ) {
				indexa++;
				indexc++;
				if( preb != -1 ) {
					indexb = preb;
					prea = -1;
					preb = -1;
				}
				continue;
			}
			if( B[indexb] == C[indexc] ) {
				indexb++;
				indexc++;
				if (prea != -1) {
					indexa = prea;
					prea = -1;
					preb = -1;
				}
				continue;
			}
			return false;
		} else {
			if( A[indexa] != C[indexc] ) return false;
			if( prea == -1 ){
				prea = indexa;
				preb = indexb;
			}
			indexa++;
			indexb++;
			indexc++;
		}
	}
	return true;
}

int main() {
	char a1[] = "axybcd";
	char b1[] = "xyz";
	char c1[] = "axyxybczd";
	bool result = isInterLeave(a1, b1, c1);

	if( result ) {
		cout << "Matching" << endl;
	} else {
		cout << "Not Matching" << endl;
	}
	return 0;
}



