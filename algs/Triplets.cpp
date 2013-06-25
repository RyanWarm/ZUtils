#include <cmath>
#include <cstdio>
#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int m;
    cin >> m;
    if( m < 3 ) return 0;
    vector<int> nums;
    int n;
    for( int i = 0; i < m; i++ ) {
        cin >> n;
        nums.push_back(n);
    }
    int less[m], dp[m];
    less[0] = 0;
    dp[0] = 0;
    set<int> existed;
    int tmp = 0, tr = 0, result = 0;
    for( int i = 1; i < m; i++ ) {
        for( int j = i-1; j >= 0; j-- ) {
			if( nums[j] == nums[i] ) break;
            if( existed.count(nums[j]) == 0 && nums[j] < nums[i] ) {
                existed.insert(nums[j]);
                tmp++;
            }
            if( nums[j] < nums[i] ) tr += less[j];
        }
        less[i] = tmp;
		cout << i << ":" << less[i] << "," << tr << endl;
        result += tr;
        tmp = 0;
        tr = 0;
        existed.clear();
    }
    cout << result << endl;
    return 0;
}
