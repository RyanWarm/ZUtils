#include <iostream>
using namespace std;

class Solution {
public:
    bool isNumber(const char *s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if( !*s ) return false;
        bool dot = false, ce = false, sign = false;
        int started = 0;
        while( *s != '\0' ) {
            if( *s == ' ' ) {
                if( started == 1 ) started = 2;
            } else if( started == 2 ) {
                return false;
            } else if( *s == 'e' ) {
                if( ce || dot ) return false;
                else ce = true;
            } else if( *s == '.' ) {
                if( dot || ce ) return false;
                else dot = true;
            } else if( *s == '+' || *s == '-' ) {
                if( sign ) return false;
                sign = true;
            } else {
                if( *s < '0' || *s > '9' ) return false;
                else started = 1;
            }
            s++;
        }
        if( started > 0 ) return true;
        else return false;
    }
};

int main() {
    const char* s = "    ";
    Solution solution;
    bool result = solution.isNumber(s);
    return 1;
}
