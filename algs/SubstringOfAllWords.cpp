#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    bool checkValid(string &S, string &l, int index, int len) {
        for( int i = 0; i < len; i++ ) {
            if( S[index+i] != l[i] ) return false;
        }
        return true;
    }
    vector<int> findSubstring(string S, vector<string> &L) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int lens = S.length();
        int size = L.size();
        int lenl = L[0].length();
        
        string match[lens];
        for( int i = 0; i < lens; i++ ) {
            match[i] = "";
            if( lens-i < lenl ) continue;
            for( int j = 0; j < size; j++ ) {
                if( checkValid(S, L[j], i, lenl) ) {
                    match[i] = L[j];
                    break;
                }
            }
        }
        vector<int> result;
        map<string, int> dp;
        for( int i = 0; i < size; i++ ) {
            if( dp.count(L[i]) != 0 ) dp[L[i]]++;
            else {
				dp[L[i]] = 1;
			}
        }
        for( int i = 0; i < lens; i++ ) {
            map<string, int> tmp = dp;
            int j = i;
            while( j < lens ) {
                if( match[j].length() == 0 || tmp.count(match[j]) == 0 ) break;
                tmp[match[j]]--;
                if( tmp[match[j]] == 0 ) tmp.erase(match[j]);
                if( tmp.size() == 0 ) {
                    result.push_back(i);
                    break;
                }
                j += lenl;
            }
        }
        return result;
    }
};
int main() {
	Solution solution;
	string S = "barfoothefoobarman";
	vector<string> L;
	L.push_back("foo");
	L.push_back("bar");
	vector<int> result = solution.findSubstring(S, L);
	return 1;
}
