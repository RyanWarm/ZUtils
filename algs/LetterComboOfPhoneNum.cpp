#include <iostream>

class Solution {
public:
	void initMap(map<char, string> &m) {
		m['2'] = "abc";
		m['3'] = "def";
		m['4'] = "ghi";
		m['5'] = "jkl";
		m['6'] = "mno";
		m['7'] = "pqrs";
		m['8'] = "tuv";
		m['9'] = "wxyz";
	}
	void doCombination(string &digits, map<char, string> &m, int index, int len, string tmp, vector<string> &result) {
		if( index == len ) {
			result.push_back(tmp);
			return;
		}

		char cur = digits[index];
		if( cur == '0' || cur == '1' ) {
			doCombination(digits, m, index+1, len, tmp+cur, result);
		} else {
			string pc = m[cur];
			for( int i = 0; i < pc.length(); i++ ) {
				doCombination(digits, m, index+1, len, tmp+pc[i], result);
			}
		}
	}
	vector<string> letterCombinations(string digits) {
		map<char, string> m;
		initMap(m);

		vector<string> result;
		string tmp;
		doCombination(digits, m, 0, digits.length(), tmp, result);
		return result;
	}
};
