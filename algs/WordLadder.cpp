#include <iostream>
#include <queue>
#include <set>
#include <string>
using namespace std;

class Solution {
public:
    bool validString(string s1, string s2) {
        int diff = 0, len = s1.length();
        for( int i = 0; i < len; i++ ) {
            if( s1[i] != s2[i] ) {
                if( diff == 1 ) return false;
                diff++;
            }
        }
        if( diff == 1 ) return true;
        return false;
    }
    int ladderLength(string start, string end, unordered_set<string> &dict) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int result = 1;
        queue<string> dp1, *dp2 = new queue<string>();
        unordered_set<string> used;
        dp1.push(start);
        while( !dp1.empty() ) {
            string tmp = dp1.front();
            dp1.pop();
            if( validString(tmp, end) ) return result+1;
            for( unordered_set<string>::iterator it = dict.begin(); it != dict.end(); ++it ) {
                if( used.find(*it) == used.end() && validString(tmp, *it) ) {
                    dp2->push(*it);
                    used.insert(*it);
                }
            }
            if( dp1.empty() ) {
                dp1 = *dp2;
                dp2 = new queue<string>();
                result++;
            }
        }
        return 0;
    }
};
int main() {
	set<string> dict;
	dict.insert("hot");
	dict.insert("hit");
	dict.insert("cog");
	dict.insert("dot");
	dict.insert("dog");
	string start = "hit";
	string end = "cog";
	Solution solution;
	int result = solution.ladderLength(start, end, dict);
	cout << result << endl;
	return 1;
}
