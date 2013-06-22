#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    void reset_used_matrix(int **used, int n) {
        for( int i = 0; i < n; i++ ) {
            for( int j = 0; j < n; j++ ) used[i][j] = 0;
        }
    }
    int mark_cells(int **used, int i, int j, int n, bool symbol) {
		if( symbol ) {
        	used[i][j] = 2;
		} else {
			for( int m = 0; m < n; m++ ) {
				if( used[m][j] == 2 ) {
					i = m;
					used[i][j] = 0;
					break;
				}
			}
		}

        int val = symbol ? 1 : 0;
        for( int m = 0; m < n; m++ ) {
            if( m != i ) used[m][j] = val;
        }
        for( int m = j+1; m < n; m++ ) used[i][m] = val;
        int m = 1;
		cout << "inside mark: " << i << "," << j << endl;
        while( i-m >= 0 || i+m < n ) {
            if( i-m >= 0 ) used[i-m][j+m] = val;
            if( i+m < n ) used[i+m][j+m] = val;
			m++;
        }
		cout << "outside mark" << endl;
		return i;
    }
    vector<string> construct_result(int **used, int n) {
        vector<string> result;
        for( int i = 0; i < n; i++ ) {
            string tmp;
            for( int j = 0; j < n; j++ ) {
                if( used[i][j] == 2 ) tmp.push_back('Q');
                else tmp.push_back('.');
            }
            result.push_back(tmp);
        }
        return result;
    }
    vector<vector<string> > solveNQueens(int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<vector<string> > result;
        if( n == 1 ) {
            vector<string> t;
            t.push_back("Q");
            result.push_back(t);
            return result;
        }
        if( n < 4 ) return result;
        int **used = new int*[n];
        for( int i = 0; i < n; i++ ) used[i] = new int[n];
		reset_used_matrix(used, n);
		int i = 0, j = 0;
		while( i < n && j < n ) {
			cout << "i: " << i << ",j: " << j << endl;
                if( !used[j][i] ) {
                    if( i == n-1 ) {
						cout << "got result" << endl;
                        vector<string> tmp = construct_result(used, n);
                        result.push_back(tmp);
						if( j < n-1 ) j++;
						else if( i > 0 ) {
							while( i >= 0 ) {
								i--;
								j = mark_cells(used, j, i, n, false);
								if( j < n-1 ) {
									j++;
									break;
								}
							}
							if( i < 0 ) break;
						}
						else break;
                    } else {
                        mark_cells(used, j, i, n, true);
                        i++;
						j = 0;
                    }
                } else {
					if( j < n-1 ) j++;
					else if( i > 0 ) {
						while( i >= 0 ) {
							i--;
							j = mark_cells(used, j, i, n, false);
							if( j < n-1 ) {
								j++;
								break;
							}
						}
						if( i < 0 ) break;
					}
					else break;
				}
        }
        return result;
    }
};
int main() {
	Solution solution;
	vector<vector<string> > result = solution.solveNQueens(4);
	return 1;
}
