#include <string>
#include <iostream>
using namespace std;

void doParenthize(int s, int e, int l, string &r) {
	if( s != l ) {
		r.push_back('(');
		if( s + 1 + e < 2 * l ) doParenthize( s+1, e, l, r );
		else cout << r << endl;
		r = r.substr(0, r.length()-1);
	}
	if( e != l && s > e ) {
		r.push_back(')');
		if( s + e + 1 < 2 * l ) doParenthize( s, e+1, l, r );
		else cout << r << endl;
		r = r.substr(0, r.length()-1);
	}
}

int main() {
	int i = 8;
	string r;
	doParenthize(0, 0, i/2, r);
	return 0;
}
