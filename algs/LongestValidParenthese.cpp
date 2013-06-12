#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    int longestValidParentheses(string s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int len = s.length();
        if( len == 0 ) return 0;
        stack<int> ts;
        int val[len];
        for( int i = 0; i < len; i++ ) {
            if( s[i] == '(' ) {
                ts.push(i);
                val[i] = 0;
            } else {
                if( ts.empty() ) {
                    val[i] = 0;
                    continue;
                }
                int pre = ts.top();
                ts.pop();
                val[i] = i - pre + 1;
            }
        }
        int result = 0;
        for( int i = 0; i < len; i++ ) {
            if( val[i] != 0 ) {
                int tmp = i - val[i];
                if( tmp >= 0 && val[tmp] != 0 ) val[i] += val[tmp];
                if( val[i] > result ) result = val[i];
            }
        }
        return result;
    }
};
int main() {
	Solution solution;
	string input = "(";
	int result = solution.longestValidParentheses(input);
	cout << result << endl;
	return 1;
}
