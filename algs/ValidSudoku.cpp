#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    bool checkRow(vector<vector<char> > &board, int i) {
		cout << "check row: " << i << endl;
        bool vals[9];
        for( int k = 0; k < 9; k++ ) vals[k] = false;
        int index = 0;
        for( vector<char>::iterator it = board[i].begin(); it != board[i].end(); ++it ) {
            if( *it == '.' ) continue;
            index = *it - '1';
			cout << "index: " << index << endl;
            if( vals[index] ) {
				cout << "row false: " << i << endl;
				return false;
			}
            vals[index] = true;
        }
		cout << "row true: " << i << endl;
        return true;
    }
    bool checkColumn(vector<vector<char> > &board, int i) {
		cout << "check column: " << i << endl;
        bool vals[9];
        for( int k = 0; k < 9; k++ ) vals[k] = false;
        int index = 0, n = board.size();
        for( int k = 0; k < n; k++ ) {
            if( board[k][i] == '.' ) continue;
            index = board[k][i] - '1';
            if( vals[index] ) {
				cout << "column false: " << i << endl;
				return false;
			}
            vals[index] = true;
        }
		cout << "column true: " << i << endl;
        return true;
    }
    bool checkSquare(vector<vector<char> > &board, int r, int c) {
		cout << "check square: " << r << "," << c << endl;
        bool vals[9];
        for( int k = 0; k < 9; k++ ) vals[k] = false;
        int index = 0;
        for( int i = 0; i < 3; i++ ) {
            for( int j = 0; j < 3; j++ ) {
                if( board[r+i][c+j] == '.' ) continue;
                index = board[r+i][c+j] - '1';
                if( vals[index] ) {
					cout << "square false: " << r << "," << c << endl;
					return false;
				}
                vals[index] = true;
            }
        }
		cout << "square true: " << r << "," << c << endl;
        return true;
    }
    bool isValidSudoku(vector<vector<char> > &board) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int len = board.size();
        for( int i = 0; i < len; i++ ) {
            if( !checkRow(board, i) || !checkColumn(board, i) ) return false;
        }
        int r = 0, c = 0;
        while( r < len ) {
			c = 0;
            while( c < len ) {
                if( !checkSquare(board, r, c) ) return false;
                c += 3;
            }
            r += 3;
        }
        return true;
    }
};
int main() {
	Solution solution;
	const char *inp[9] = {".265...9.","5...79..4","3...1....","6.....8.7",".75.2..1.",".1....4..","...3.89.2","7...6..4.",".3.28.1.."};
	vector<vector<char> > board;
	for( int i = 0; i < 9; i++ ) {
		vector<char> tmp;
		for( int j = 0; j < 9; j++ ) {
			tmp.push_back(*(inp[i]+j));
		}
		board.push_back(tmp);
	}
	bool result = solution.isValidSudoku(board);
	if( result ) cout << "valid" << endl;
	else cout << "invalid" << endl;
	return 1;
}
