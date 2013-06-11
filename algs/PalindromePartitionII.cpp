#include <string>
#include <iostream>
using namespace std;

class Solution {
public:
    int minCut(string s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int len = s.length();
        if( len == 0 ) return 0;
        int cut[len];
        bool dp[len][len];
        for( int i = 0; i < len; i++ ) {
            cut[i] = i;
        }
		for( int i = 0; i < len; i++ ) {
			for( int j = 0; j < len; j++ ) {
				dp[i][j] = false;
			}
		}
        for( int i = 1; i < len; i++ ) {
            for( int j = i; j >= 0; j-- ) {
                if( s[i] == s[j] && ( (i-j) < 3 || dp[j+1][i-1]) ) {
                    //s[j,i] is palindrome
                    dp[j][i] = true;
                    if( j == 0 ) cut[i] = 0;
                    else if( cut[j-1] + 1 < cut[i] ) cut[i] = cut[j-1] + 1;
                }
            }
        }
		for( int i = 0; i < len; i++ ) {
			cout << cut[i] << endl;
		}
		cout << "dp: " << endl;
		for( int i = 0; i < len; i++ ) {
			for( int j = 0; j <= i; j++ ) {
				cout << dp[j][i] << ", ";
			}
			cout << endl;
		}
        return cut[len-1];
    }
};
int main() {
	Solution solution;
	string input = "cabababcbc";
	int result = solution.minCut(input);
	cout << result << endl;
	return 1;
}
