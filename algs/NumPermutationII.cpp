#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
	void doPermute(int n, string &tmp) {
		if( n == 0 ) {
			cout << tmp << endl;
			return;
		}
		if( n < 0 ) return;
		for( int i = 1; i <= 3; i++ ) {
			tmp.push_back('0'+i);
			doPermute(n-i, tmp);
			tmp.erase(tmp.length()-1);
		}
	}
	void permute(int n) {
		string tmp;
		doPermute(n, tmp);
	}
};

int main() {
	Solution solution;
	solution.permute(5);
	return 1;
}
