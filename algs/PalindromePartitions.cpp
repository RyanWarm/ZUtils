#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int isPalindrome(string s, int i, int j, vector<vector<int> > &dp) {
        if( i == j ) return 1;
        if( i > j ) return -1;
        if( s[i] == s[j] ) {
            if( i >= j-2 ) {
                dp[i][j] = 1;
            } else {
                dp[i][j] = isPalindrome(s, i+1, j-1, dp);
            }
        } else {
            dp[i][j] = -1;
        }
		cout << i << "," << j << ":" << dp[i][j] << endl;
        return dp[i][j];
    }
    void getPartitions(string s, int start, int end, vector<vector<string> > &result, vector<vector<int> > &dp, vector<string> tmp) {
        if( start == end ) {
            tmp.push_back(s.substr(start, 1));
            result.push_back(tmp);
			cout << "push result: " << endl;
			for( vector<string>::iterator it = tmp.begin(); it != tmp.end(); ++it ) cout << *it << endl;
            return;
        }
        if( start > end ) return;
        for( int i = start; i < end; i++ ) {
            if( isPalindrome(s, start, i, dp) == 1 ) {
				cout << "push tmp: " << endl;
				for( vector<string>::iterator it = tmp.begin(); it != tmp.end(); ++it ) cout << *it << endl;
                tmp.push_back(s.substr(start, i-start+1));
                getPartitions(s, i+1, end, result, dp, tmp);
                tmp.erase(tmp.end()-1);
				cout << "pop tmp: " << endl;
				for( vector<string>::iterator it = tmp.begin(); it != tmp.end(); ++it ) cout << *it << endl;
            }
        }
    }
    vector<vector<string> > partition(string s) {
        vector<vector<string> > result;
        int len = s.length();
        vector<vector<int> > dp;
        if( len == 0 ) return result;
        for( int i = 0; i < len; i++ ) {
            vector<int> t;
            for( int j = 0; j < len; j++ ) t.push_back(-1);
            dp.push_back(t);
        }
        for( int i = 0; i < len; i++ ) dp[i][i] = 1;
        for( int i = 0; i < len; i++ ) {
            if( isPalindrome(s, 0, i, dp) == 1 ) {
                vector<string> tmp;
                tmp.push_back(s.substr(0, i+1));
                getPartitions(s, i+1, len, result, dp, tmp);
            }
        }
        return result;
    }
};
int main() {
	string s ("ab");
	Solution solution;
	vector<vector<string> > result = solution.partition(s);
	cout << result.size() << endl;
	return 1;
}
