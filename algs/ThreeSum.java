import java.util.ArrayList;
import java.util.Arrays;

public class ThreeSum {
    public int bsInt(int target, int start, int end, int[] num) {
		System.out.println("search: " + target + "," + start + "," + end);
        if( num[start] > target ) return -1;
        int mid = (start+end)/2;
        if( num[mid] == target ) {
            return mid;
        } else if( num[mid] < target ) {
            if( mid+1 > end ) return -1;
            else return bsInt(target, mid+1, end, num);
        } else {
            if( mid-1 < start ) return -1;
            else return bsInt(target, start, mid-1, num);
        }
    }
    
    public ArrayList<ArrayList<Integer>> threeSum(int[] num) {
        Arrays.sort(num);
        int len = num.length;
        int tmp = 0;
        ArrayList<ArrayList<Integer>> result = (ArrayList<ArrayList<Integer>>)new ArrayList();
        ArrayList<Integer> r;
        for( int i = 0; i < len-2; i++ ) {
            if( num[i] > 0 ) break;
            if( i > 0 && num[i] == num[i-1] ) continue;
            tmp = num[i];
            
            for( int j = i+1; j < len-1; j++ ) {
                if( tmp + num[j] > 0 ) break;
                if( j > i+1 && num[j] == num[j-1] ) continue;
                tmp += num[j];
                int index = bsInt(0-tmp, j+1, len-1, num);
				System.out.println( "Return: " + index );
                if( index != -1 ) {
                    r = new ArrayList<Integer>();
                    r.add(num[i]);
                    r.add(num[j]);
                    r.add(num[index]);
                    result.add(r);
					System.out.println( "Add result: " + num[i] + "," + num[j] + "," + num[index] );
                }
				tmp -= num[j];
            }
        }
        
        return result;
    }

	public static void main( String[] args ) {
		ThreeSum s = new ThreeSum();
		int[] num = new int[]{1,2,-2,-1};
		ArrayList<ArrayList<Integer>> result = s.threeSum(num);
	}
}
