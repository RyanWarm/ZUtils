#include <iostream>
#include <math.h>
using namespace std;

void doFinding(int index, int num, int remain, int result[]) {
	int cur = index * index;
	if( num == 3 && cur == remain ) {
		cout << "Got result: " << result[0] << "^2 + " << result[1] << "^2 + " << result[2] << "^2 + " << index << "^2" << endl;
		return;
	}

	if( index == 1 || (num == 3 && cur < remain) ) return;

	if( cur <= remain ) {
		result[num] = index;
		doFinding(index-1, num+1, remain-cur, result);
	}

	if( index >= 4 - num ) {
		doFinding(index-1, num, remain, result);
	}
}

int main() {
	int n;
	cin >> n;

	int root = floor(sqrt(n));
	int r[4];
	doFinding(root, 0, n, r);
}

