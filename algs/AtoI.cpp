#include <iostream>
using namespace std;

class Solution {
public:
    int atoi(const char *str) {
        long long result = 0;
        int i = 0;
        while( str[i] == ' ' && str[i] != '\0' ) i++;
        if( str[i] == '\0' ) return 0;
        if( str[i] != '-' && str[i] != '+' && ((str[i]-'0') > 9 || (str[i]-'0') < 0 ) ) return 0;
        bool neg = false;
        if( str[i] == '-' || str[i] == '+' ) {
            if( str[i] == '-' ) neg = true;
            i++;
        }
		if( neg ) {
			cout << "neg" << endl;
		}
        int tmp;
        while( str[i] != '\0' ) {
            tmp = str[i] - '0';
            if( tmp > 9 || tmp < 0 ) break;
            result = result * 10 + tmp;
            i++;
        }
		cout << "result: " << result << endl;
        if( neg ) result *= -1;
		if( result > 2147483647 ) result = 2147483647;
		if( result < -2147483648 ) result = -2147483648;
        return result;
    }
};

int main() {
	Solution solution;
	char inp[] = "2147483648";
	int r = solution.atoi(inp);
	cout << r << endl;
}
