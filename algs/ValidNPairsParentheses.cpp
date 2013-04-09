#include <iostream>
using namespace std;
void doGeneration(int n, int left, int right, char *r) {
	//cout << "inside: " << left << "," << right << "," << r << endl;
	if( left + right == n*2 ) {
		cout << r << endl;
		return;
	}
	if( left < n ) {
		r[left+right] = '{';
		doGeneration(n, left+1, right, r);
	}
	if( right < n && right < left ) {
		r[left+right] = '}';
		doGeneration(n, left, right+1, r);
	}
}

int main() {
	char r[9];
	doGeneration(4, 0, 0, r);
	return 1;
}
