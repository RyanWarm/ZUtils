import java.io.*;

public class MulExp {
    public static void main(String args[] ) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String line = br.readLine();
        int N = Integer.parseInt(line);
        
        int input[] = new int[N];
        int zero_count = 0;
        
        line = br.readLine();
        int num = Integer.parseInt(line);
        input[0] = num;
        if( num == 0 ) zero_count++;
        
        int tmp_pro = 1;
        for (int i = 1; i < N; i++) {
            line = br.readLine();
            num = Integer.parseInt(line);
            input[i] = num;
            if( num == 0 ) {
                zero_count++;
            } else {
                tmp_pro *= num;
            }
        }
        
        if( zero_count >1 ) {
            for( int i = 0; i < N; i++ ) {
                System.out.println(0);
            }
        } else if( zero_count == 1 ) {
            for( int i = 0; i < N; i++ ) {
                if( input[i] == 0 ) {
		    if( i == 0 ) {
			System.out.println(tmp_pro);
		    } else {
                        System.out.println(tmp_pro*input[0]);
		    }
                } else {
                    System.out.println(0);
                }
            }
        } else {
            int pre_pro = 1;
            for( int i = 0; i < N-1; i++ ) {
                System.out.println(pre_pro*tmp_pro);
                pre_pro *= input[i];
                tmp_pro /= input[i+1];
            }
            System.out.println(pre_pro);
        }
    }
}
