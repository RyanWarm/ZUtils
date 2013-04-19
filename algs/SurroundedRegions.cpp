#include <vector>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

class Solution {
public:
    void turn_round(vector<vector<char> > &board, long long h, long long w, long long x, long long y) {
        if( x > 0 && board[x-1][y] == 'O' ) {
            board[x-1][y] = 'K';
            turn_round(board, h, w, x-1, y);
        }
        if( y > 0 && board[x][y-1] == 'O' ) {
            board[x][y-1] = 'K';
            turn_round(board, h, w, x, y-1);
        }
        if( x < h-1 && board[x+1][y] == 'O' ) {
            board[x+1][y] = 'K';
            turn_round(board, h, w, x+1, y);
        }
        if( y < w-1 && board[x][y+1] == 'O' ) {
            board[x][y+1] = 'K';
            turn_round(board, h, w, x, y+1);
        }
    }
    void solve(vector<vector<char> > &board) {
        long long h = board.size();
        if( h == 0 ) return;
        long long w = board[0].size();
        if( w == 0 ) return;
        long long i = 0, j = 0;
        for( j = 0; j < w; j++ ) {
            if( board[i][j] == 'O' ) {
                board[i][j] = 'K';
                turn_round(board, h, w, i, j);
            }
        }
        i = h-1;
        for( j = 0; j < w; j++ ) {
            if( board[i][j] == 'O' ) {
                board[i][j] = 'K';
                turn_round(board, h, w, i, j);
            }
        }
        j = 0;
        for( i = 0; i < h; i++ ) {
            if( board[i][j] == 'O' ) {
                board[i][j] = 'K';
                turn_round(board, h, w, i, j);
            }
        }
        j = w-1;
        for( i = 0; i < h; i++ ) {
            if( board[i][j] == 'O' ) {
                board[i][j] = 'K';
                turn_round(board, h, w, i, j);
            }
        }
        
        for( i = 0; i < h; i++ ) {
            for( j = 0; j < w; j++ ) {
                if( board[i][j] == 'O' ) board[i][j] = 'X';
                else if( board[i][j] == 'K' ) board[i][j] = 'O';
            }
        }
    }
};
int main() {
	ifstream is("input.data");
	string s;
	getline(is,s);
	vector<vector<char> > input;
	vector<char> *tmp = new vector<char>();
	for( int i = 0; i < s.size(); i++ ) {
		if( s[i] == ',' ) {
			input.push_back(*tmp);
			tmp = new vector<char>();
			continue;
		}
		tmp->push_back(s[i]);
	}
	Solution solution;
	solution.solve(input);
	return 1;
}
