import java.util.Stack;
public class HanoiTower {
	private int num;
	private Stack[] s = new Stack[3];
	public HanoiTower( int i ) {
		this.num = i;
	}

	public void move() {
		int f,t,b;
		f = 0;
		t = 2;
		b = 1;
		for( int i = this.num; i > 0; i-- ) {
			doMoving(i, f, t, b);
			t = f;
			f = b;
			b = t;
			t = 2;
			System.out.println( "Finished moving " + i );
		}
	}

	private void doMoving( int n, int from, int to, int buffer ) {
		if( n == 1 ) {
			System.out.println( "Move 1 from " + from + " to " + to );
			return;
		}

		doMoving(n-1, from, buffer, to);
		System.out.println( "Move " + n + " from " + from + " to " + to );
		doMoving(n-1, buffer, to, from);
	}

	public static void main( String[] args ) {
		int num = 7;
		HanoiTower h = new HanoiTower(num);
		h.move();
	}
}
