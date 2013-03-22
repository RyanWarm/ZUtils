import java.util.ArrayList;

public class PalindromePartition {
    public ArrayList<ArrayList<String>> partition(String s) {
        ArrayList<ArrayList<String>> result = new ArrayList<ArrayList<String>>();
        int len = s.length();
        ArrayList<ArrayList<Integer>>[] dp = new ArrayList[len];
        int[][] isPalin = new int[len][len];
        for( int i = 0; i < len; i++ ) {
            for( int j = 0; j < len; j++ ) {
                isPalin[i][j] = -1;
            }
        }
        for( int i = 0; i < len; i++ ){
            isPalin[i][i] = 1;
        }
        
        ArrayList<Integer> tmp = new ArrayList<Integer>();
        tmp.add(0);
        ArrayList<ArrayList<Integer>> tmp1 = new ArrayList<ArrayList<Integer>>();
        tmp1.add(tmp);
        dp[0] = tmp1;
        for( int i = 1; i < len; i++ ) {
            for( int j = i; j >= 0; j-- ) {
                if( isPalin[j][i] == -1 ) {
                    if( s.charAt(i) == s.charAt(j) ) {
                        if( j < i - 2 ) {
                            isPalin[j][i] = isPalin[j+1][i-1];
                        } else {
                            isPalin[j][i] = 1;
                        }
                        
                    } else {
                        isPalin[j][i] = 0;
                    }
                }
                
                if( isPalin[j][i] == 0 ) continue;
                
                //got it
                ArrayList<ArrayList<Integer>> append;
                if( j > 0 ) {
                    append = (ArrayList<ArrayList<Integer>>)((ArrayList<ArrayList<Integer>>)dp[j-1]).clone();
                    
                    for( int m = 0; m < append.size(); m++ ) {
                        ((ArrayList<Integer>)append.get(m)).add(j);
                    }
                } else {
                    append = new ArrayList<ArrayList<Integer>>();
                    tmp = new ArrayList<Integer>();
                    tmp.add(i);
                    append.add(tmp);
                }
                if( dp[i] == null ) {
                    dp[i] = append;
                } else {
                    ((ArrayList<ArrayList<Integer>>)dp[i]).addAll(append);
                }
            }
        }
        
        tmp1 = (ArrayList<ArrayList<Integer>>)dp[len-1];
        ArrayList<String> tmp_s;
        for( int i = 0; i < tmp1.size(); i++ ) {
            tmp = (ArrayList<Integer>)tmp1.get(i);
            tmp_s = new ArrayList<String>();
            int pre = -1;
            int nex = -1;
            for( int j = 0; j < tmp.size(); j++ ) {
                nex = ((Integer)tmp.get(j)).intValue();
                if( pre == -1 ) {
                    pre = nex;
                    continue;
                }
                tmp_s.add(s.substring(pre,nex));
            }
            tmp_s.add(s.substring(pre));
            result.add(tmp_s);
        }
        
        return result;
    }
}
