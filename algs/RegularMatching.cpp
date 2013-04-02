#include <iostream>
using namespace std;

class Solution {
public:
    static bool doMatching(const char *s, const char *p, int is, int ip) {
        if( s[is] == '\0' && p[ip] == '\0' ) return true;
        if( p[ip] != '\0' ) {
            if( p[ip] == '.' ) {
                return doMatching(s, p, is+1, ip+1);
            } else if( p[ip] == '*' ) {
                char pre = p[ip-1];
                int index = is;
                while( s[index] != '\0' && (pre == '.' || s[index] == pre) ) {
                    if( doMatching(s, p, index+1, ip+1) ) {
                        return true;
                    }
                    index++;
                }
                return doMatching(s, p, is, ip+1);
            } else if( p[ip] == s[is] ) {
                return doMatching(s, p, is+1, ip+1);
            } else if( p[ip+1] == '*' ) {
                return doMatching(s, p, is, ip+1);
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
    
    static bool isMatch(const char *s, const char *p) {
        if( s[0] == '\0' ) {
            if( p[0] == '\0' || p[1] == '*' ) {
                return true;
            } else {
                return false;
            }
        } else if( p[0] == '\0' ) {
            return false;
        } else if( p[0] == s[0] || p[0] == '.' ) {
            return doMatching(s, p, 1, 1);
        } else if( p[1] == '*' ) {
            return doMatching(s, p, 0, 2);
        } else {
            return false;
        }
    }
};

int main() {
	char as[] = "bbbba";
	char bs[] = ".*a*a";
	bool r = Solution::isMatch( as, bs );
	cout << r << endl;
	return 1;
}
