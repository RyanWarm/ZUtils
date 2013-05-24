#include <iostream>
#include <stack>
#include <string>
using namespace std;

class Solution {
public:
    string simplifyPath(string path) {
        stack<string> dirs;
        int len = path.length();
        string result;
        if( len == 0 ) return result;
        int s = 1, e = 0;
        dirs.push("/");
        while( s < len && e < len ) {
            while( path[s] == '/' ) s++;
            e = s+1;
            while( path[e] != '/' ) e++;
            string tmp = path.substr(s, e-s);
            if( tmp == ".." ) {
				cout << dirs.size() << endl;
                if( !dirs.empty() && dirs.top() != "/" ) dirs.pop();
            } else if( tmp != "." ) {
                dirs.push(tmp);
            }
            s = e+1;
        }
        if( e == len && s < len ) dirs.push(path.substr(s, e-s));
        while( !dirs.empty() ) {
            string tmp = dirs.top();
            dirs.pop();
            if( tmp == "/" ) result = tmp + result;
            else if( result.length() != 0 ) result = tmp + "/" + result;
            else result = tmp;
        }
        return result;
    }
};
int main() {
	Solution solution;
	string input = "///";
	string output = solution.simplifyPath(input);
	cout << output << endl;
	return 1;
}
