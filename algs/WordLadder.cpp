#include <vector>
#include <iostream>
#include <tr1/unordered_set>
#include <string>
using namespace std;
using namespace std::tr1;

class Solution {
public:
	bool isValidPair(string s1, string s2) {
		int len = s1.length();
		int diff = 0;
		for( int i = 0; i < len; i++ ) {
			if( s1[i] == s2[i] ) continue;
			else {
				if( diff == 1 ) return false;
				else diff++;
			}
		}
		if( diff == 1 ) return true;
		else return false;
	}
    bool doProcess(string start, string end, unordered_set<string> &dict, vector<string> &v1, vector<string> &v2) {
		cout << "inside process" << endl;
		cout << "v1 size: " << v1.size() << ", v2 size: " << v2.size() << endl;
		vector<string>::iterator it = v1.begin();
		while( it != v1.end() ) {
			cout << "processing: " << *it << endl;
			if( isValidPair(*it, end) ) return true;
			for( unordered_set<string>::iterator it1 = dict.begin(); it1 != dict.end(); ++it1 ) {
				if( isValidPair(*it, *it1) ) {
					if( *it1 == end ) return true;
					v2.push_back(*it1);
					dict.erase(*it1);
				}
			}
			it++;
		}
		v1.clear();
		return false;
	}
    int ladderLength(string start, string end, unordered_set<string> &dict) {
		if( start == end ) return 1;
		if( dict.empty() ) return -1;
		vector<string> v1, v2;
		v1.push_back(start);
		bool sym = true, got = false;
		int result = 1;
		while( !v1.empty() || !v2.empty() || !dict.empty() ) {
			result++;
			cout << "v1 size: " << v1.size() << ", v2 size: " << v2.size() << endl;
			if( sym ) {
				if( doProcess(start, end, dict, v1, v2) ) {
					got = true;
					break;
				}
			} else {
				if( doProcess(start, end, dict, v2, v1) ) {
					got = true;
					break;
				}
			}
			sym = !sym;
		}
		if( !got ) return -1;
		return result;
	}
};
int main() {
	unordered_set<string> inp;
	inp.insert("hot");
	inp.insert("cog");
	inp.insert("dog");
	inp.insert("tot");
	inp.insert("hog");
	inp.insert("hop");
	inp.insert("pot");
	inp.insert("dot");
	Solution s;
	int result = s.ladderLength("hot", "dog", inp);
	cout << result << endl;
	return 1;
}
