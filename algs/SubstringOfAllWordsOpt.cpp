class Solution {
public:
    bool checkValid(string &S, string &l, int index, int len) {
        for( int i = 0; i < len; i++ ) {
            if( S[index+i] != l[i] ) return false;
        }
        return true;
    }
    vector<int> findSubstring(string S, vector<string> &L) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int lens = S.length();
        int size = L.size();
        int lenl = L[0].length();
        
        string match[lens];
        for( int i = 0; i < lens; i++ ) {
            match[i] = "";
            if( lens-i < lenl ) continue;
            for( int j = 0; j < size; j++ ) {
                if( checkValid(S, L[j], i, lenl) ) {
                    match[i] = L[j];
                    break;
                }
            }
        }
        vector<int> result;
        map<string, int> dp;
        for( int i = 0; i < size; i++ ) {
            if( dp.count(L[i]) != 0 ) dp[L[i]]++;
            else dp[L[i]] = 1;
        }
        int end = lens-lenl*2 > 0 ? lens-lenl*2 : 0;
        for( int i = lens-lenl; i > end; i-- ) {
            map<string, int> tmp = dp;
            int j = i, c = 0;
            while( j >= 0 ) {
                if( match[j].length() == 0 || tmp.count(match[j]) == 0 ) {
                    tmp = dp;
                    c = 0;
                } else {
                    tmp[match[j]]--;
                    if( tmp[match[j]] == 0 ) tmp.erase(match[j]);
                    c++;
                    if( c == size ) {
                        result.push_back(j);
                        tmp[match[j+(size-1)*lenl]] = 1;
                        c--;
                    }
                }
                j -= lenl;
            }
        }
        return result;
    }
};