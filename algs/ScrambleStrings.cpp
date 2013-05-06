#include <stdio.h>
#include <iostream>
#include <map>
#include <string>
using namespace std;

class Solution {
public:
    bool check(string s1, string s2, int len, int b1, int e1, int b2, int e2, map<string,bool> &dp) {
        char tmp[] = "";
        sprintf(tmp, "%d,%d,%d,%d", b1, e1, b2, e2);
		string key (tmp);
		cout << "key: " << key << endl;
		for( map<string,bool>::iterator it = dp.begin(); it != dp.end(); ++it ) {
			cout << "map: " << it->first << ":" << it->second << endl;
		}
        if( dp.find(key) != dp.end() ) return dp[key];
		bool result = false;
        strint ts1 = s1.substr(b1, e1-b1+1), ts2 = s2.substr(b2, e2-b2+1);
        if( ts1 == ts2 ) {
            result = true;
        } else {
            sort(ts1.begin(), ts1.end());
            sort(ts2.begin(), ts2.end());
            if( ts1 == ts2 ) {
                for( int i = b1; i < e1; i++ ) {
                    if( check(s1, s2, len, b1, i, b2, b2+i-b1, dp) && check(s1, s2, len, i+1, e1, b2+i-b1+1, e2, dp) ) {
                        result = true;
                        break;
                    }
                    if( check(s1, s2, len, b1, i, e2-i+b1, e2, dp) && check(s1, s2, len, i+1, e1, b2, b2+e1-i-1, dp) ) {
                        result = true;
                        break;
                    }
                }
            }
        }
		dp[key] = result;
		cout << key << ":" << result << endl;
        return result;
    }
    bool isScramble(string s1, string s2) {
        map<string,bool> dp;
        int len = s1.length();
        if( len == 0 ) return true;
        if( len == 1 ) {
            if( s1 == s2 ) return true;
            else return false;
        }
        strint ts1 = s1, ts2 = s2;
        sort(ts1.begin(), ts1.end());
        sort(ts2.begin(), ts2.end());
        if( ts1 != ts2 ) return false;
        for( int i = 0; i < len-1; i++ ) {
            if( (check(s1, s2, len, 0, i, 0, i, dp) && check(s1, s2, len, i+1, len-1, i+1, len-1, dp))
                || (check(s1, s2, len, 0, i, len-1-i, len-1, dp) && check(s1, s2, len, i+1, len-1, 0, len-i-2, dp)) ) {
                return true;
            }
        }   
		return false;
    }
};
int main() {
	Solution solution;
	string s1 = "aa";
	string s2 = "ab";
	cout << "input: " << s1 << ":" << s2 << endl;
	bool result = solution.isScramble(s1, s2);
	if( result ) cout << "True" << endl;
	else cout << "False" << endl;
	return 1;
}
