#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    bool validRange(bool **dp, int i, int j) {
        for( int m = i+1; m < j; m++ ) {
            if( dp[i][m] && dp[m+1][j] ) return true;
        }
        return false;
    }
    int longestValidParentheses(string s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int len = s.length();
        if( len == 0 ) return 0;
        int ps = 0, pe = 0, tmp = 0, result = 0;
        bool **dp = new bool*[len];
        int l[len];
        for( int i = 0; i < len; i++ ) dp[i] = new bool[len];
        for( int i = 0; i < len; i++ ) {
            l[i] = 0;
            for( int j = 0; j < len; j++ ) dp[i][j] = false;
        }
        for( int i = 0; i < len; i++ ) {
            int tmp = 0;
            if( s[i] == '(' ) continue;
            for( int j = i-1; j >= 0; j-- ) {
                if( s[j] == ')' ) continue;
                if( i-j == 2 ) continue;
                if( i-j == 1 || dp[j+1][i-1] || validRange(dp, j, i) ) {
                    dp[j][i] = true;
                    int t = i - j + 1;
                    tmp = t > tmp ? t : tmp;
                }
            }
            l[i] = tmp;
        }
        for( int i = 0; i < len; i++ ) {
            int tmp = l[i];
            if( tmp == 0 ) continue;
            result = tmp > result ? tmp : result;
            int j = i - tmp;
            while( j >= 0 && l[j] > 0 ) {
                tmp += l[j];
                result = tmp > result ? tmp : result;
                j = j - l[j];
            } 
        }
        return result;
    }
};
int main() {
	Solution solution;
	string input = "())()()(())((()(()()(((()))((((())((()(())()())(()((((()))()(()))(())()(())(()(((((())((((((()())())(()(()((())()))(()))))))()(()))((((())()()()))()()()(((()(()())(()()(()(()()(((()))))))()()))())())((()()))))))((()))(((()((())()(()()))((())))()()())))))))()))))(()))))()))()))()((())))((()))(()))))))(((()))))))))()(()()()(())((())()))()()(())))()()))(()())()))(((()())()))((())((((()))(()(()(()()()(((())()(((((()))((()(((((())(()()))((((((((()(()(()(()(())))(())(()())())(()((((()(())((()(())))(())))()(((((()(()()(())))))))())(())(())(()()(((())))((()))(((((()))))())))()((()))()))))())))))((())(((((()()))((((())))(((()(()(())())(((()(()(()()()())))())()))((()((())())()()()(((())(((((()((((((()((()())))((((())((()(((((((()(()((()()()(()(()())(()(()()((((())))()(((()())))(()()))()(()()()()(((((())(()))))((()))())))()((((((()))())))()(()))(())))((((()())(((((()()())(((((())(()())(()))))()(()()))()))))))())))(((())(()(()()))(()))()(((())))())((((()(((()))))))()(()(()))()()(()()))))))))((()))))))(())((()((()))()))((((((()())))))(()((())((((()))))(()(()()()()(()))()()(()(()))(()()(((((((()())(())(()())((())())()(()())((())()())())(()())))())))(())())())(())((()())(((()()))()))()()))()(()(())((((((((())))()((())((()((((((((((()))))(()(((((())(()(()())())))((())())))))()))(()((()()))((()((())()()()((()(())())((())())(()()(((())))))())()()(()))()())(()(()((())))((((()()(())))())(())(()(()(())())())(()()())()(())())))(()()(((())))((()()(((())()()(()())((((()()(()())(()((((()(()()(()(()(((()((()())(()()))(()((((()(((((()))))()()))(((()((((((()(()()()()())()))(()(())))))((()(((()())())))(((()()))(()(()(((((((()()))(()(())))())()(())())(())(()))(())(()))()()(()()())))))()))()((())(((()((((((((())()()))())))((()())(";
	cout << input << endl;
	int result = solution.longestValidParentheses(input);
	cout << result << endl;
	return 1;
}
