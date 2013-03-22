import java.io.*;
import java.util.HashSet;

public class Triplet {
	public static void main( String[] args ) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String line = br.readLine();
		int N = Integer.parseInt(line);
		int result = 0;
		line = br.readLine();
		String[] vals = line.split(" ");
		HashSet<Integer> used = new HashSet<Integer>();
		int[] dp = new int[N];
		
		dp[0] = 0;
		boolean passed = false;
		for( int i = 1; i < N; i++ ) {
			for( int j = i - 1; j >= 0; j-- ) {
				if( Integer.parseInt(vals[j]) == Integer.parseInt(vals[i]) ) {
					passed = true;
				} else if( Integer.parseInt(vals[j]) > Integer.parseInt(vals[i]) ) {
					continue;
				} else {
					//vals[j] < vals[i]
					if( !used.contains(Integer.valueOf(vals[j])) ) {
						if( !passed ) {
							result += dp[j];
							System.out.println("add: " + j + "," + i + ":" + dp[j]);
						}
						used.add(Integer.valueOf(vals[j]));
						dp[i]++;
					}
				}
			}
			passed = false;
			used.clear();
		}

		System.out.println(result);
	}
}
