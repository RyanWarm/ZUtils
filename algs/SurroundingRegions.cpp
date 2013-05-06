#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Solution {
public:
    void check(vector<vector<char> > &board, int row, int col, int x, int y, vector<int> &vx, vector<int> &vy) {
        if( x >= 0 && x < col && y >= 0 && y < row && board[y][x] == 'O' ) {
            vx.push_back(x);
            vy.push_back(y);
        }
    }
    void remark_surroundings(vector<vector<char> > &board, int row, int col, int x, int y) {
        vector<int> vx, vy;
        if( x >= 0 && x < col && y >= 0 && y < row && board[y][x] == 'O' ) {
            vx.push_back(x);
            vy.push_back(y);
        } else return;
        int index = 0;
        while( index < vx.size() ) {
            x = vx[index];
            y = vy[index];
            board[y][x] = 'Y';
            check(board, row, col, x-1, y, vx, vy);
            check(board, row, col, x, y-1, vx, vy);
            check(board, row, col, x+1, y, vx, vy);
            check(board, row, col, x, y+1, vx, vy);
            index++;
        }
    }
    void solve(vector<vector<char> > &board) {
        int row = board.size();
        if( row == 0 ) return;
        int col = board[0].size();
        if( col == 0 ) return;
        int x = 0, y = 0;
        for( x = 0; x < col; x++ ) {
        	remark_surroundings(board, row, col, x, y);
        }
        y = row - 1;
        for( x = 0; x < col; x++ ) {
			remark_surroundings(board, row, col, x, y);
        }
        x = 0;
        for( y = 0; y < row; y++ ) {
			remark_surroundings(board, row, col, x, y);
        }
        x = col - 1;
        for( y = 0; y < row; y++ ) {
			remark_surroundings(board, row, col, x, y);
        }
        for( x = 0; x < col; x++ ) {
            for( y = 0; y < row; y++ ) {
                if( board[y][x] == 'Y' ) board[y][x] = 'O';
                else if( board[y][x] == 'O' ) board[y][x] = 'X';
            }
        }
    }
};
int main() {
	Solution solution;
	vector<vector<char> > input;
	vector<char> *tmp = new vector<char>();
	char str;
	ifstream is;
	is.open("input.data");
	while( !is.eof() ) {
		str = is.get();
		if( str == '[' ) {
			vector<char> *tmp = new vector<char>();
			continue;
		}
		if( str == ']' ) {
			input.push_back(*tmp);
			continue;
		}
		if( str != ',' ) tmp->push_back(str);
	}
	input.push_back(*tmp);
	solution.solve(input);
	for( int i = 0; i < input.size(); i++ ) {
		for( int j = 0; j < input[0].size(); j++ ) {
			cout << input[i][j];
		}
		cout << endl;
	}
	return 1;
}
