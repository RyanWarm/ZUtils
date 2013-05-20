#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    string add(string num1, string num2) {
		cout << "inside add: " << num1 << " + " << num2 << endl;
        int i = num1.length()-1;
        int j = num2.length()-1;
        string result;
        if( i > j ) result = num1;
        else result = num2;
		cout << "ini result: " << result << endl;
        int k = result.length()-1;
        int tmp, carry = 0;
        while( i >= 0 && j >= 0 ) {
            tmp = (num1[i--]-'0') + (num2[j--]-'0') + carry;
            if( tmp > 9 ) {
                result[k--] = '0' + (tmp - 10);
                carry = 1;
            } else {
                result[k--] = '0' + tmp;
                carry = 0;
            }
        }
		cout << "mid: " << result << "," << k << "," << carry << endl;
        while( k >= 0 && carry == 1 ) {
            tmp = result[k] - '0' + 1;
			cout << "tmp: " << tmp << endl;
            if( tmp == 10 ) {
                result[k--] = '0';
                carry = 1;
            } else {
                result[k--] = '0' + tmp;
                carry = 0;
            }
			cout << "result: " << result << endl;
        }
        if( carry == 1 ) return "1" + result;
        else return result;
    }
    string mulOne(string num1, char num2 ) {
        string result = num1;
        if( num2 == '1' ) return result;
        int tmp, i = num1.length()-1, carry = 0;
        int n2 = num2 - '0';
        while( i >= 0 ) {
            tmp = (num1[i] - '0') * n2 + carry;
            if( tmp > 9 ) {
                result[i--] = '0' + (tmp % 10);
                carry = tmp / 10;
            } else {
                result[i--] = '0' + tmp;
                carry = 0;
            }
        }
        if( carry > 0 ) {
            result = "0" + result;
            result[0] = '0' + carry;
        }
		cout << "mulOne result: " << result << endl;
        return result;
    }
    string multiply(string num1, string num2) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if( num1 == "0" || num2 == "0" ) return "0";
        string result;
        int len1 = num1.length();
        int len2 = num2.length();
        if( len1 == 1 || len2 == 1 ) {
            if( len1 == 1 ) {
                result = mulOne(num2, num1[0]);
            } else {
                result = mulOne(num1, num2[0]);
            }
        } else {
            string add_s, tmp_s;
            if( len2 > len1 ) {
                add_s = num1;
                num1 = num2;
                num2 = add_s;
                len1 = num1.length();
                len2 = num2.length();
                add_s = "";
            }
            for( int i = len2-1; i >= 0; i-- ) {
                if( result.length() == 0 ) result = mulOne(num1, num2[i]);
                else {
                    add_s += "0";
                    tmp_s = mulOne(num1, num2[i]);
                    result = add(result, tmp_s + add_s);
					cout << "r: " << result << endl;
                }
            }
        }
        return result;
    }
};
int main() {
	string num1 = "123";
	string num2 = "456";
	Solution solution;
	cout << "input: " << num1 << " * " << num2 << endl;
	string result = solution.multiply(num1, num2);
	cout << result << endl;
	return 1;
}
