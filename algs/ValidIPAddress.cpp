#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    void checkValidAdd(string s, int start, int num, vector<string> &result, int len, string tmp) {
		if( len - start > num * 3 ) return;
        if( num == 0 ) {
            if( start == len ) {
                string in = tmp;
                result.push_back(in);
            }
            return;
        }
        if( start != 0 ) {
            tmp.push_back('.');
        }
		if( s[start] == '0' ) {
			tmp.push_back(s[start]);
			checkValidAdd(s, start+1, num-1, result, len, tmp);
			tmp.erase(tmp.end()-1);
		} else if( start < len-2 ) {
            tmp.push_back(s[start]);
            checkValidAdd(s, start+1, num-1, result, len, tmp);
            tmp.push_back(s[start+1]);
            checkValidAdd(s, start+2, num-1, result, len, tmp);
            if( s[start] < '3' ) {
                tmp.push_back(s[start+2]);
                checkValidAdd(s, start+3, num-1, result, len, tmp);
                tmp.erase(tmp.end()-1);
                tmp.erase(tmp.end()-1);
                tmp.erase(tmp.end()-1);
            } else {
                tmp.erase(tmp.end()-1);
                tmp.erase(tmp.end()-1);
            }
        } else if( start < len-1 ) {
			tmp.push_back(s[start]);
            checkValidAdd(s, start+1, num-1, result, len, tmp);
            tmp.push_back(s[start+1]);
            checkValidAdd(s, start+2, num-1, result, len, tmp);
            tmp.erase(tmp.end()-1);
            tmp.erase(tmp.end()-1);
		} else {
            tmp.push_back(s[start]);
            checkValidAdd(s, start+1, num-1, result, len, tmp);
            tmp.erase(tmp.end()-1);
		}
        if( start != 0 ) {
            tmp.erase(tmp.end()-1);
        }
    }
    
    vector<string> restoreIpAddresses(string s) {
        vector<string> result;
        int len = s.length();
        if( len < 4 ) return result;
        string tmp;
        checkValidAdd(s, 0, 4, result, len, tmp);
        return result;
    }
};
int main() {
	Solution solution;
	string s ("25525511135");
	cout << "input: " << s << endl;
	vector<string> result = solution.restoreIpAddresses(s);
	cout << result[0] << endl;
	cout << result[1] << endl;
}
