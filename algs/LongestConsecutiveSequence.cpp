#include <vector>
#include <iostream>
#include <map>
using namespace std;

class Solution {
public:
    int getValue(int num, map<int, bool> exist) {
        int start = num-1, end = num+1;
		while( exist.find(start) != exist.end() ) {
			exist.erase(start);
			start--;
		}
		while( exist.find(end) != exist.end() ) {
			exist.erase(end);
			end++;
		}
        return end - start - 1;
    }
    int longestConsecutive(vector<int> &num) {
        map<int, bool> exist;
        for( vector<int>::iterator it = num.begin(); it != num.end(); ++ it ) {
            exist[*it] = true;
        }
        int result = 0, tmp = 0;
        for( vector<int>::iterator it = num.begin(); it != num.end(); ++ it ) {
			if( exist.find(*it) == exist.end() ) continue;
            tmp = getValue(*it, exist);
            if( tmp > result ) result = tmp;
        }
        return result;
    }
};

int main() {
	Solution solution;
	vector<int> input;
	input.push_back(-1);
	input.push_back(0);
	int result = solution.longestConsecutive(input);
	cout << result << endl;
	return 1;
}
