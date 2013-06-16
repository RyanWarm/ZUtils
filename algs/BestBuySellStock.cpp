#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int> &prices) {
        int len = prices.size();
        if( len < 2 ) return 0;
        int result = 0;
        int min = prices[0], max = prices[len-1];
        int left[len], right[len];
        left[0] = 0;
        right[len-1] = 0;
        int index = 1, tmp = 0;
        for( vector<int>::iterator it = prices.begin()+1; it != prices.end(); ++it ) {
            tmp = (*it-min) > tmp ? (*it-min) : tmp;
            left[index++] = tmp;
            min = min < *it ? min : *it;
        }
        tmp = 0;
        index = len-2;
        for( vector<int>::iterator it = prices.end()-2; it != prices.begin(); --it ) {
            tmp = (max-*it) > tmp ? (max-*it) : tmp;
            right[index--] = tmp;
            max = max > *it ? max : *it;
        }
        tmp = (max-prices[0]) > tmp ? (max-prices[0]) : tmp;
        right[0] = tmp;
        for( int i = 0; i < len; i++ ) {
			cout << left[i] << "," << right[i] << endl;
		}
        tmp = 0;
        for( int i = 0; i < len; i++ ) {
            tmp = left[i] + right[i];
            result = tmp > result ? tmp : result;
        }
        return result;
    }
};
int main() {
	Solution solution;
	vector<int> input;
	input.push_back(1);
	input.push_back(2);
	int result = solution.maxProfit(input);
	cout << result << endl;
	return 1;
}
