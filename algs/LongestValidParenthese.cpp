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
        int ps = 0, pe = 0, tmp = 0, result = 0;
        while( ps < len ) {
			cout << s << ", ps: " << ps << endl;
            if( s[ps] == ')' ) {
                ps++;
                tmp = 0;
                len = s.length();
            } else {
                pe = ps + 1;
                if( pe < len ) {
					if( s[pe] == ')' ) {
                    	tmp++;
                    	s.erase(ps,2);
                    	len = s.length();
                    	if( ps > 0 ) ps--;
                	} else if( s[pe] == '(' ) {
                    	ps++;
                	}
				} else break;
                if( tmp != 0 ) {
                    int t = tmp * 2;
                    result = t > result ? t : result;
                }
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
