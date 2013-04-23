#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
	void doPermutation( vector<char> set, int index, string &result) {
		if( index == set.size() ) {
			if( result.length() == 0 ) return;
			cout << result << endl;
			return;
		}
		doPermutation(set, index+1, result);
		result.push_back(set[index]);
		doPermutation(set, index+1, result);
		result.erase(result.length()-1);
	}

	void printPowerSets( vector<char> set ) {
		string r;
		doPermutation(set, 0, r);
	}
};
int main() {
	Solution solution;
	vector<char> input;
	input.push_back('A');
	input.push_back('B');
	input.push_back('C');
	input.push_back('D');
	input.push_back('E');
	solution.printPowerSets(input);
	return 1;
}
