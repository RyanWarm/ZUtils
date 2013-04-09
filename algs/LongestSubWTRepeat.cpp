#include <string>
#include <iostream>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
		cout << s << endl;
        int tmp_l = 0;
        int len = s.length();
        int i = 0;
        int pos[26];
        for( int j = 0; j < 26; j++ ) pos[j] = -1;
        int tmp;
        int result = 0;
        int start = 0;
        while( i < len ) {
            tmp = s[i] - 'a';
            if( pos[tmp] == -1 ) {
                pos[tmp] = i;
                tmp_l = i - start + 1;
                if( tmp_l > result ) {
					result = tmp_l;
					cout << start << ":" << i << endl;
				}
            } else {
                int tmp_pos = pos[tmp];
				cout << "==" << start << ":" << tmp_pos << endl;
                for( int j = start; j <= tmp_pos; j++ ) pos[s[j]-'a'] = -1;
                start = tmp_pos + 1;
                pos[tmp] = i;
            }
            i++;
        }
        return result;
    }
};

int main() {
	Solution solution;
	string s = "inprobabilitytheoryandstatisticsamedianisdescribedasthenumericvalueseparating";
	int r = solution.lengthOfLongestSubstring(s);
	cout << r << endl;
	return 1;
}
