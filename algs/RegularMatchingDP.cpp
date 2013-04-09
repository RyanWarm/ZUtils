#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool isMatch(const char *s, const char *p) {
		cout << s << ":" << p << endl;
        if( p[0] == '\0' ) {
            if( s[0] == '\0' ) return true;
            else return false;
        }
		int lens = 0, lenp = 0;
		while( s[lens] != '\0' ) lens++;
		while( p[lenp] != '\0' ) lenp++;

		bool dp[lens][lenp];
        int si = 0;
        int pi = 0;
        while( s[si] != '\0' ) {
        	pi = 0;
            while( p[pi] != '\0' ) {
                if( p[pi] == '*' ) {
                    if( (pi > 1 && dp[si][pi-2]) || (((si > 0 && pi > 0 && dp[si-1][pi]) || si == 0 && pi > 0 ) && (s[si] == p[pi-1] || p[pi-1] == '.')) ) {
						cout << si << "," << pi << ":true" << endl;
                        dp[si][pi] = true;
                    } else {
						cout << si << "," << pi << ":false" << endl;
                        dp[si][pi] = false;
                    }
                } else {
                    if( ((si == 0 && pi == 0) || (pi != 0 && si != 0 && dp[si-1][pi-1])) && (p[pi] == '.' || p[pi] == s[si]) ) {
						cout << si << "," << pi << ":true" << endl;
                        dp[si][pi] = true;
                    } else {
						cout << si << "," << pi << ":false" << endl;
                        dp[si][pi] = false;
                    }
                }
                pi++;
            }
            si++;
        }
        return dp[si-1][pi-1];
    }
};

int main() {
	char s[] = "";
	char p[] = ".*";
	Solution solution;
	bool r = solution.isMatch(s,p);
	if( r ) cout << "true" << endl;
	else cout << "false" << endl;
	return 1;
}
