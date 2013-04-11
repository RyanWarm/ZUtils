#include <vector>
#include <iostream>
#include <string>
#include <stdio.h>
#include <map>
using namespace std;

class Solution {
public:
	vector<string> anagrams(vector<string> &strs) {
		map<string, vector<string> > str_map;

		for( vector<string>::iterator it = strs.begin(); it != strs.end(); it++ ) {
			string key;
			int c_map[26];
			for( int i = 0; i < 26; i++ ) c_map[i] = 0;
			string tmp = *it;
			cout << tmp.length() << endl;
			for( int i = 0; i < tmp.length(); i++ ) {
				c_map[tmp[i]-'a']++;
			}
			key = "";
			char bufi[10];
			char bufc[10];
			for( int i = 0; i < 26; i++ ) {
				if( c_map[i] > 0 ) {
					sprintf(bufi, "%d", i);
					sprintf(bufc, "%d", c_map[i]);
					key.append(bufi).append(":").append(bufc).append(",");
				}
			}
			vector<string> tmp_r;
			if( str_map.find(key) != str_map.end() ) {
				cout << "create" << endl;
				tmp_r = str_map[key];
			}
			tmp_r.push_back(tmp);
			cout << "size: " << tmp_r.size() << endl;
			str_map[key] = tmp_r;
			cout << "size_m: " << str_map.size() << endl;
		}

		vector<string> result;
		for( map<string, vector<string> >::iterator it = str_map.begin(); it != str_map.end(); it++ ) {
			result = it->second;
			if( result.size() > 1 ) return result;
		}
		return result;
	}
};

int main() {
	vector<string> strs;
	strs.push_back("");
	Solution s;
	vector<string> result = s.anagrams(strs);
	for( vector<string>::iterator it = result.begin(); it != result.end(); it++ ) {
		cout << (string)*it << endl;
	}
	return 1;
}
