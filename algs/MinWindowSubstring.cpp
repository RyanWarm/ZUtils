#include <map>
#include <set>
#include <string>
#include <iostream>
using namespace std;

class Solution {
public:
    bool validWindow(map<char, int> &need, map<char, int> &exist) {
        for( map<char, int>::iterator it = need.begin(); it != need.end(); ++it ) {
            if( exist.find(it->first) == exist.end() || exist[it->first] < it->second ) return false;
        }
        return true;
    }
    string minWindow(string S, string T) {
        int lens = S.length(), lent = T.length();
        string result;
        if( lens == 0 ) return result;
        int s = 0, e = 0, min = lens+1, rs = -1, re = -1;
        map<char, int> need, exist;
        set<char> contain;
        for( int i = 0; i < lent; i++ ) {
            if( need.find(T[i]) == need.end() ) need[T[i]] = 1;
            else need[T[i]]++;
            contain.insert(T[i]);
            exist[T[i]] = 0;
        }
        while( s < lens ) {
            if( contain.find(S[s]) != contain.end() ) {
                e = s;
                break;
            }
            s++;
        }
        while( e < lens ) {
            if( contain.find(S[e]) != contain.end() ) {
                exist[S[e]]++;
                if( validWindow(need, exist) ) {
                    if( (e-s+1) < min ) {
                        min = e-s+1;
                        rs = s;
                        re = e;
                    }
                    exist[S[s]]--;
                    s++;
                    while( s <= e ) {
                        if( contain.find(S[s]) != contain.end() ) {
                            if( validWindow(need, exist) ) {
                                if( (e-s+1) < min ) {
                                    min = e-s+1;
                                    rs = s;
                                    re = e;
                                }
                                exist[S[s]]--;
                            } else {
                                break;
                            }
                        }
                        s++;
                    }
                }
            }
            e++;
        }
        if( rs == -1 || re == -1 ) return result;
        return S.substr(rs, re-rs+1);
    }
};

int main() {
    string S = "abc";
    string T = "b";
    Solution solution;
    string result = solution.minWindow(S, T);
    cout << result << endl;
    return 1;
}
