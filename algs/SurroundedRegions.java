import java.util.ArrayList;
import java.util.Stack;

public class SurroundedRegions {
    public void solve(char[][] board) {
        if( board == null || board.length == 0 || board[0].length == 0 ) return;
        int h = board.length;
        int w = board[0].length;
        boolean[][] visited = new boolean[h][w];
        
        for( int i = 0; i < h; i++ ) {
            for( int j = 0; j < w; j++ ) {
                visited[i][j] = false;
            }
        }
        Stack<String> s = new Stack<String>();
        ArrayList<String> a = new ArrayList<String>();
        for( int i = 0; i < h; i++ ) {
            for( int j = 0; j < w; j++ ) {
                if( board[i][j] == 'X' || visited[i][j] ) continue;
                visited[i][j] = true;
                s.push(String.valueOf(i+","+j));
                a.add(String.valueOf(i+","+j));
                boolean passed = false;
                while(!s.empty()){
                    int[] tmp = new int[2];
                    String[] tmp_s = ((String)s.pop()).split(",");
                    tmp[0] = Integer.parseInt(tmp_s[0]);
                    tmp[1] = Integer.parseInt(tmp_s[1]);
                    if( !passed && (tmp[0] == 0 || tmp[1] == 0 || tmp[0] == h-1 || tmp[1] == w-1) ) {
                        passed = true;
                    }
                    if( tmp[0] > 0 && !visited[tmp[0]-1][tmp[1]] && board[tmp[0]-1][tmp[1]] == 'O' ) {
                        s.push(String.valueOf(tmp[0]-1)+","+String.valueOf(tmp[1]));
                        a.add(String.valueOf(tmp[0]-1)+","+String.valueOf(tmp[1]));
                        visited[tmp[0]-1][tmp[1]] = true;
                    }
                    if( tmp[1] > 0 && !visited[tmp[0]][tmp[1]-1] && board[tmp[0]][tmp[1]-1] == 'O' ) {
                        s.push(String.valueOf(tmp[0])+","+String.valueOf(tmp[1]-1));
                        a.add(String.valueOf(tmp[0])+","+String.valueOf(tmp[1]-1));
                        visited[tmp[0]][tmp[1]-1] = true;
                    }
                    if( tmp[0] < h-1 && !visited[tmp[0]+1][tmp[1]] && board[tmp[0]+1][tmp[1]] == 'O' ) {
                        s.push(String.valueOf(tmp[0]+1)+","+String.valueOf(tmp[1]));
                        a.add(String.valueOf(tmp[0]+1)+","+String.valueOf(tmp[1]));
                        visited[tmp[0]+1][tmp[1]] = true;
                    }
                    if( tmp[1] < w-1 && !visited[tmp[0]][tmp[1]+1] && board[tmp[0]][tmp[1]+1] == 'O' ) {
                        s.push(String.valueOf(tmp[0])+","+String.valueOf(tmp[1]+1));
                        a.add(String.valueOf(tmp[0])+","+String.valueOf(tmp[1]+1));
                        visited[tmp[0]][tmp[1]+1] = true;
                    }
                }
                if( passed ) {
                    a.clear();
                } else {
                    for( int m = 0; m < a.size(); m++ ) {
                        int[] tmp = new int[2];
                        String[] tmp_s = ((String)a.get(m)).split(",");
                        tmp[0] = Integer.parseInt(tmp_s[0]);
                        tmp[1] = Integer.parseInt(tmp_s[1]);
                        board[tmp[0]][tmp[1]] = 'X';
                    }
                }
            }
        }
        for( int i = 0; i < h; i++ ) {
            for( int j = 0; j < w-1; j++ ) {
                System.out.print(board[i][j]+" ");
            }
            System.out.println(board[i][w-1]);
        }
    }

    public static void main( String[] argv ) {
	char[][] input = new char[5][5];
	input[0][0] = 'X';
	input[0][1] = 'X';
	input[0][2] = 'X';
	input[0][3] = 'X';
	input[0][4] = 'O';
	input[1][0] = 'X';
	input[1][1] = 'O';
	input[1][2] = 'O';
	input[1][3] = 'X';
	input[1][4] = 'O';
	input[2][0] = 'X';
	input[2][1] = 'X';
	input[2][2] = 'O';
	input[2][3] = 'X';
	input[2][4] = 'O';
	input[3][0] = 'X';
	input[3][1] = 'X';
	input[3][2] = 'O';
	input[3][3] = 'O';
	input[3][4] = 'X';
	input[4][0] = 'X';
	input[4][1] = 'X';
	input[4][2] = 'X';
	input[4][3] = 'X';
	input[4][4] = 'O';
        for( int i = 0; i < 5; i++ ) {
            for( int j = 0; j < 5-1; j++ ) {
                System.out.print(input[i][j]+" ");
            }
            System.out.println(input[i][5-1]);
        }
        System.out.println("----------------");

	char[][] a = new char[1][1];
	a[0][0] = 'X';
	SurroundedRegions solution = new SurroundedRegions();
	solution.solve(a);
    }
}
