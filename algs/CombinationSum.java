import java.util.ArrayList;
import java.util.Arrays;
public class CombinationSum {
    public ArrayList<ArrayList<Integer>> combinationSum(int[] candidates, int target) {
        ArrayList<ArrayList<Integer>> result = new ArrayList<ArrayList<Integer>>();
        int len = candidates.length;
        Arrays.sort(candidates);
        ArrayList<String>[] dp = (ArrayList<String>[])new ArrayList[target];
        boolean[] st = new boolean[target];
        for( int i = 0; i < target; i++ ) {
            st[i] = false;
        }
        
        for( int i = 1; i < target; i++ ) {
            for( int j = 0; j < len; j++ ) {
                if( candidates[j] > i ) break;
                if( candidates[j] == i ) {
                    if( !st[i] ) {
                        dp[i] = new ArrayList<String>();
                        st[i] = true;
                    }
                    dp[i].add(String.valueOf(j));
                } else {
                    //candidates[j] < i
                    if( dp[i-candidates[j]] != null ) {
                        if( !st[i] ) {
                            dp[i] = new ArrayList<String>();
                            st[i] = true;
                        }
                        for( int m = 0; m < dp[i-candidates[j]].size(); m++ ) {
                            dp[i].add(dp[i-candidates[j]].get(m) + "," + String.valueOf(candidates[j]));
                        }
                    }
                }
            }
        }
        
        ArrayList<Integer> tmp;
        for( int i = 0; i < len; i++ ) {
            if( candidates[i] > target ) break;
            if( i > 0 && candidates[i] == candidates[i-1] ) continue;
            if( candidates[i] == target) {
                tmp = new ArrayList<Integer>();
                tmp.add(candidates[i]);
                result.add(tmp);
            } else {
                //candidates[i] < target
                if( !st[target-candidates[i]] ) {
                    for( int m = 0; m < dp[target-candidates[i]].size(); m++ ) {
                        String[] s = dp[target-candidates[i]].get(m).split(",");
                        tmp = new ArrayList<Integer>();
                        for( int k = 0; k < s.length; k++ ) {
                            tmp.add(Integer.parseInt(s[k]));
                        }
                        tmp.add(candidates[i]);
                        result.add(tmp);
                    }
                }
            }
        }
        return result;
    }

    public static void main( String[] args ) {
	int[] input = new int[1];
	input[0] = 1;
	CombinationSum solution = new CombinationSum();
	ArrayList<ArrayList<Integer>> result = solution.combinationSum(input,2);
    }
}
