#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string> &strs) {
        string result;
        int index = 0;
        char tmp = '\0';
        while( true ) {
            for( vector<string>::iterator it = strs.begin(); it != strs.end(); it++ ) {
				cout << (*it)[index] << endl;
                if( (*it)[index] == 0 ) return result;
                if( tmp == '\0' ) tmp = (*it)[index];
                else if( tmp != (*it)[index] ) {
                    return result;
                }
            }
			index++;
            result.push_back(tmp);
            tmp = '\0';
        }
        return result;
    }
};

int main() {
    vector<string> strs;
    string str = "abc";
    strs.push_back(str);
    str = "abcd";
    strs.push_back(str);
    str = "abcdesf";
    strs.push_back(str);
    Solution s;
    string r = s.longestCommonPrefix(strs);
    cout << r << endl;
    return 1;
}
