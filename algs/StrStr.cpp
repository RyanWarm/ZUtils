#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    char *strStr(char *haystack, char *needle) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if( haystack == NULL ) return NULL;
        if( !*(needle) ) return haystack;
        vector<int> fa;
        fa.push_back(0);
        int i = 1, j = 0;
        while( *(needle+i) ) {
            if( *(needle+i) == *(needle+j) ) {
                i++;
                j++;
                fa.push_back(j);
            } else if( fa[j] > 0 && fa[j] != j ) {
                j = fa[j];
            } else {
                fa.push_back(0);
                i++;
				j = 0;
            }
        }
		for( vector<int>::iterator it = fa.begin(); it != fa.end(); ++it ) {
			cout << *it << endl;
		}
        i = 0;
        j = 0;
        while( *(haystack+i) ) {
			cout << i << "," << j << endl;
            if( *(haystack+i) == *(needle+j) ) {
                if( !*(needle+j+1) ) return (haystack+i-j);
                i++;
                j++;
            } else if( j > 0 && fa[j-1] > 0 ) {
                j = fa[j-1];
            } else {
				if( j > 0 ) j = 0;
                else i++;
            }
        }
        return NULL;
    }
};
int main() {
	Solution solution;
	char s1[] = "bbbbababbbaabbba";
	char s2[] = "abb";
	cout << s1 << "," << s2 << endl;
	char* result = solution.strStr(s1, s2);
	cout << result << endl;
	return 1;
}
