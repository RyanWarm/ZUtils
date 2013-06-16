#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
	void doPermute(int n, int i, string tmp) {
		if( n == 0 ) cout << tmp << endl;
		if( n < i ) return;
		tmp.push_back('0'+i);
		doPermute(n-i, i, tmp);
		tmp.erase(tmp.length()-1);
		doPermute(n, i+1, tmp);
	}
	void permute(int n) {
		string tmp;
		doPermute(n, 1, tmp);
	}
};
int main() {
	Solution solution;
	solution.permute(4);
	return 1;
}
