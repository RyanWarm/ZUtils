#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    int maximalRectangle(vector<vector<char> > &matrix) {
        int h = matrix.size();
        if( h == 0 ) return 0;
        int w = matrix[0].size();
        if( w == 0 ) return 0;
        int dp_h[h][w];
        int dp_w[h][w];
        dp_h[0][0] = (matrix[0][0] == '1') ? 1 : 0;
        dp_w[0][0] = dp_h[0][0];
        for( int j = 1; j < w; j++ ) {
            if( matrix[0][j] == '1' ) {
                dp_w[0][j] = dp_w[0][j-1] + 1;
                dp_h[0][j] = 1;
            } else {
                dp_w[0][j] = 0;
                dp_h[0][j] = 0;
            }
        }
        for( int i = 1; i < h; i++ ) {
            if( matrix[i][0] == '1' ) {
                dp_h[i][0] = dp_h[i-1][0] + 1;
                dp_w[i][0] = 1;
            } else {
                dp_h[i][0] = 0;
                dp_w[i][0] = 0;
            }
        }
        for( int i = 1; i < h; i++ ) {
            for( int j = 1; j < w; j++ ) {
                if( matrix[i][j] == '0' ) {
                    dp_h[i][j] = 0;
                    dp_w[i][j] = 0;
                } else {
                    int min_h = min(min(dp_h[i-1][j], dp_h[i][j-1]), dp_h[i-1][j-1]);
                    int min_w = min(min(dp_w[i][j-1], dp_w[i-1][j]), dp_w[i-1][j-1]);
                    int a = (min_h + 1) * (dp_w[i][j-1] + 1);
                    int b = (min_w + 1) * (dp_h[i-1][j] + 1);
                    int c = (min_h + 1) * (min_w + 1);
                    if( a > b ) {
                        if( a > c ) {
                            // a is max
                            dp_h[i][j] = min_h + 1;
                            dp_w[i][j] = dp_w[i][j-1] + 1;
                        } else {
                            // c is max
                            dp_h[i][j] = min_h + 1;
                            dp_w[i][j] = min_w + 1;
                        }
                    } else {
                        if( b > c ) {
                            // b is max
                            dp_h[i][j] = dp_h[i-1][j] + 1;
                            dp_w[i][j] = min_w + 1;
                        } else {
                            // c is max
                            dp_h[i][j] = min_h + 1;
                            dp_w[i][j] = min_w + 1;
                        }
                    }
                }
            }
        }
        int result = 0;
        for( int i = 0; i < h; i++ ) {
            for( int j = 0; j < w; j++ ) {
				cout << dp_h[i][j] << "," << dp_w[i][j] << " ";
                int tmp = dp_h[i][j] * dp_w[i][j];
                if( tmp > result ) result = tmp;
            }
			cout << endl;
        }
        return result;
    }
};
int main() {
	vector<vector<char> > input; // {"01101","11010","01110","11110","11111","00000"};
	string s = "01101";
	char *tmp = new char[5];
	strcpy(tmp, s.c_str());
	vector<char> *tmp_v = new vector<char>(tmp, tmp+5);
	input.push_back(*tmp_v);
	s = "11010";
	strcpy(tmp, s.c_str());
	tmp_v = new vector<char>(tmp, tmp+5);
	input.push_back(*tmp_v);
	s = "01110";
	strcpy(tmp, s.c_str());
	tmp_v = new vector<char>(tmp, tmp+5);
	input.push_back(*tmp_v);
	s = "11110";
	strcpy(tmp, s.c_str());
	tmp_v = new vector<char>(tmp, tmp+5);
	input.push_back(*tmp_v);
	s = "11111";
	strcpy(tmp, s.c_str());
	tmp_v = new vector<char>(tmp, tmp+5);
	input.push_back(*tmp_v);
	s = "00000";
	strcpy(tmp, s.c_str());
	tmp_v = new vector<char>(tmp, tmp+5);
	input.push_back(*tmp_v);
	Solution solution;
	int result = solution.maximalRectangle(input);
	cout << result << endl;
	return 1;
}
