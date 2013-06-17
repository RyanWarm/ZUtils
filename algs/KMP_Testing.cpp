#include <iostream>
using namespace std;

const char s[] = "abcabcabcabc";

int kmp1() {
	int n = strlen(s);
	cout << s << endl;
	int next[n];
	int i = 1, j = 0;
	next[0] = 0;
	while( i < n ) {
		if( s[i] == s[j] ) {
			j++;
			next[i] = j;
			i++;
		} else if( j > 0 ) {
			j = next[j-1];
		} else {
			next[i] = 0;
			i++;
		}
	}
	for( i = 0; i < n; i++ ) {
		cout << next[i];
	}
	cout << endl;
}

int kmp2() {
	int n = strlen(s);
	int next[n+1];
	int i = 0, j = -1;
	next[0] = -1;
	while( i < n ) {
		if( j == -1 || s[i] == s[j] ) {
			i++;
			j++;
			next[i] = j;
		} else {
			j = next[j];
		}
	}
	for( i = 0; i < n+1; i++ ) {
		cout << next[i];
	}
	cout << endl;
}

int main() {
	kmp1();
	kmp2();
	return 1;
}
