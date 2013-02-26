import java.io.*;
import java.util.Arrays;

public class TopFour {
    public static void main(String args[] ) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String line = br.readLine();
        int N = Integer.parseInt(line);
        int min = Integer.MAX_VALUE;
        int vals[] = new int[4];
        int num;
        
        for( int i = 0; i < 4; i++ ) {
            line = br.readLine();
            num = Integer.parseInt(line);
            vals[i] = num;
            if( num < min ) min = num;
        }
        
        for (int i = 4; i < N; i++) {
            line = br.readLine();
            num = Integer.parseInt(line);
            if( num > min ) {
                min = replaceMin(vals, min, num);
            }
        }
        
        Arrays.sort(vals);
        for( int i = 3; i >= 0; i-- ) {
            System.out.println(vals[i]);
        }
    }
    
    public static int replaceMin(int vals[], int oldMin, int newVal) {
    	System.out.println("Replace: " + oldMin + " with " + newVal);
        int min = newVal;
        for( int i = 0; i < 4; i++ ) {
            if( vals[i] == oldMin ) {
                vals[i] = newVal;
            } else {
                if( vals[i] < min ) min = vals[i];
            }
        }
	System.out.println("New min: " + min);
        return min;
    }
}
