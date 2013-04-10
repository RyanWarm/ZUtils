import java.util.ArrayList;
import java.util.Arrays;

public class FourSum {
    public ArrayList<Integer> find2Sum(int[] num, int s, int e, int target) {
		System.out.println( s + "," + e + "," + target );
        ArrayList<Integer> r = new ArrayList<Integer>();
        int tmp;
        while( s < e ) {
            tmp = num[s] + num[e];
            if( tmp == target ) {
                r.add(s);
                r.add(e);
				s++;
				e--;
                while( e > s && num[e] == num[e+1] ) {
					e--;
					System.out.println( "ea: " + e );
				}
                while( s < e && num[s] == num[s-1] ) {
					s++;
					System.out.println( "sa: " + s );
				}
            } else if( tmp > target ) {
                e--;
				System.out.println( "eb: " + e );
                while( e > s && num[e] == num[e+1] ) {
					e--;
					System.out.println( "ea: " + e );
				}
            } else {
                s++;
				System.out.println( "sb: " + s );
                while( s < e && num[s] == num[s-1] ) {
					s++;
					System.out.println( "sa: " + s );
				}
            }
        }
        return r;
    }
    public ArrayList<ArrayList<Integer>> fourSum(int[] num, int target) {
        Arrays.sort(num);
        int len = num.length;
        ArrayList<ArrayList<Integer>> result = (ArrayList<ArrayList<Integer>>)new ArrayList();
        int tmp = 0, tmp1 = 0;
        ArrayList<Integer> a;
        for( int i = 0; i < len-3; i++ ) {
            tmp = num[i];
            if( tmp > 0 && tmp > target ) break;
            if( i > 0 && num[i] == num[i-1] ) continue;
            for( int j = i+1; j < len-2; j++ ) {
                tmp1 = num[j];
                if( tmp + tmp1 > 0 && tmp + tmp1 > target ) break;
                if( j > i+1 && num[j] == num[j-1] ) continue;
                ArrayList<Integer> r = find2Sum(num, j+1, len-1, target-tmp-tmp1);
                for(int k = 0; k < r.size(); k+=2) {
                    a = new ArrayList<Integer>();
                    a.add(num[i]);
                    a.add(num[j]);
                    a.add(num[((Integer)r.get(k)).intValue()]);
                    a.add(num[((Integer)r.get(k+1)).intValue()]);
					System.out.println( "=====" + a.get(0) + "," + a.get(1) + "," + a.get(2) + "," + a.get(3) );
                    result.add(a);
                }
            }
        }
        return result;
    }

	public static void main( String[] args ) {
		int[] num = new int[]{1,0,-1,0,-2,2};
		FourSum s = new FourSum();
		ArrayList<ArrayList<Integer>> r = s.fourSum(num,0);
	}
}
