#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void genSubsets(vector<int> &S, int len, int index, vector<vector<int> > &result, vector<int> tmp, bool pre) {
        if( index < len-1 ) genSubsets(S, len, index+1, result, tmp, false);
        
        if( S[index] != S[index-1] || pre ) {
            tmp.push_back(S[index]);
            vector<int> wcur (tmp);
            result.push_back(wcur);
            if( index < len-1 ) genSubsets(S, len, index+1, result, tmp, true);
            tmp.pop_back();
        }
    }
    vector<vector<int> > subsetsWithDup(vector<int> &S) {
        int len = S.size();
        vector<vector<int> > result;
        vector<int> tmp;
        result.push_back(tmp);
        if( len == 0 ) return result;
        sort(S.begin(), S.end());
        genSubsets(S, len, 0, result, tmp, false);
        return result;
    }
};
int main() {
	Solution solution;
	vector<int> input (1,1);
	vector<vector<int> > result = solution.subsetsWithDup(input);
	cout << result.size() << endl;
	return 1;
}
