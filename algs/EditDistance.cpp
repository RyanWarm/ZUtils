class Solution {
public:
    int minDistance(string word1, string word2) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int len1 = word1.length();
        int len2 = word2.length();
        if( len1 == 0 ) return len2;
        if( len2 == 0 ) return len1;
        int dp[len1][len2];
        for( int i = 0; i < len1; i++ ) {
            for( int j = 0; j < len2; j++ ) {
                if( word1[i] == word2[j] ) {
                    int prei = i-1;
                    int prej = j-1;
                    if( prei < 0 && prej < 0 ) dp[i][j] = 0;
                    else if( prei < 0 ) dp[i][j] = j;
                    else if( prej < 0 ) dp[i][j] = i;
                    else dp[i][j] = dp[i-1][j-1];
                } else {
                    int prei = i-1;
                    int prej = j-1;
                    int a, b, c;
                    if( prei < 0 && prej < 0 ) a = 0;
                    else if( prei < 0 ) a = j;
                    else if( prej < 0 ) a = i;
                    else a = dp[prei][prej];
                    
                    prei = i-1;
                    prej = j;
                    if( prei < 0 && prej < 0 ) b = 0;
                    else if( prei < 0 ) b = j+1;
                    else if( prej < 0 ) b = i;
                    else b = dp[prei][prej];
                    
                    prei = i;
                    prej = j-1;
                    if( prei < 0 && prej < 0 ) c = 0;
                    else if( prei < 0 ) c = j;
                    else if( prej < 0 ) c = i+1;
                    else c = dp[prei][prej];
                    dp[i][j] = min(min(a,b),c) + 1;
                }
            }
        }
        return dp[len1-1][len2-1];
    }
};