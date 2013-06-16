#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<int> getValidVals(vector<vector<char> > &board, int n, int i, int j) {
		cout << "inside get val: " << i << "," << j << endl;
		cout << "board_0_0: " << board[0][0] << endl;
        bool vals[9] = {false};
        for( int k = 0; k < n; k++ ) {
            if( board[i][k] != '.' ) vals[board[i][k] - '1'] = true;
            if( board[k][j] != '.' ) vals[board[k][j] - '1'] = true;
        }
        int r = i/3*3, c = j/3*3;
        for( int row = 0; row < 3; row++ ) {
            for( int col = 0; col < 3; col++ ) {
				cout << "cords: " << r+row << "," << c+col << endl;
                if( board[r+row][c+col] != '.' ) {
					cout << "index: " << board[r+row][c+col] << endl;
					int index = board[r+row][c+col] - '1';
					if( index < 0 || index > 9 ) cout << "================" << index << endl;
					//vals[index] = true;
				}
				cout << "post: " << col << endl;
            }
        }
        vector<int> result;
        for( int k = 0; k < 9; k++ ) {
            if( !vals[k] ) result.push_back(k+1);
        }
		cout << "outside get val: " << i << "," << j << endl;
		return result;
    }
    bool doSolving(vector<vector<char> > &board, int n, int i, int j) {
		cout << "inside sloving: " << i << "," << j << endl;
        if( board[i][j] != '.' ) {
            //already assigned
            if( i == n-1 && j == n-1 ) return true;
            if( j == n-1 ) {
                i++;
                j = 0;
            } else j++;
            return doSolving(board, n, i, j);
        } else {
            vector<int> vals = getValidVals(board, n, i, j);
            int len = vals.size();
			for( int k = 0; k < len; k++ ) cout << vals[k] << ",";
			cout << endl;
            if( len == 0 ) return false;
            for( int k = 0; k < len; k++ ) {
				cout << "board:" << i << "," << j << "=" << vals[k] << endl;
                board[i][j] = vals[k];
                if( i == n-1 && j == n-1 ) return true;
                if( j == n-1 ) {
                    if( doSolving(board, n, i+1, 0) ) return true;
                } else {
                    if( doSolving(board, n, i, j+1) ) return true;
                }
            }
			cout << "outside sloving: " << i << "," << j << endl;
            return false;
        }
    }
    void solveSudoku(vector<vector<char> > &board) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int len = board.size();
        doSolving(board, len, 0, 0);
    }
};
int main() {
    Solution solution;
    const char *inp[9] = {"..9748...","7........",".2.1.9...","..7...24.",".64.1.59.",".98...3..","...8.3.2.","........6","...2759.."};
    vector<vector<char> > board;
    for( int i = 0; i < 9; i++ ) {
        vector<char> tmp;
        for( int j = 0; j < 9; j++ ) {
            tmp.push_back(*(inp[i]+j));
        }
        board.push_back(tmp);
    }
    for( int i = 0; i < 9; i++ ) {
        for( int j = 0; j < 9; j++ ) {
			cout << board[i][j];
		}
		cout << endl;
	}
    solution.solveSudoku(board);
    return 1;
}
