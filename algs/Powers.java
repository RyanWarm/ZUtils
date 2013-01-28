import java.util.Iterator;
import java.lang.Math;

public class Powers implements Iterator {
	private long current;
	private long m;
	private long n;

	public Powers() {
		m = 2;
		n = 2;
		current = 1;
	}

	public Long next() {
		if( current == 1 ) {
			current = 4;
			return new Long(current);
		}
		
		long tm = m+1, tn = n, tc;
		while( current++ < Long.MAX_VALUE ) {
//			System.out.println("current: " + current);
			boolean revert = false;
			while( true ) {
				tc = (long)Math.pow(tm,tn);
				if( tc == current ) {
					m = tm;
					n = tn;
					System.out.println("m: " + m + ", n: " + n);
					return new Long(current);
				}
/**
				if( tm == 2 && tn == 2 ) {
					break;
				}
*/
				// increase base and decrease exponent
				if( !revert ) {
					if( tn != 2 ) {
						if( tc < current ) tm++;
						else tn--;
						continue;
					}else{
						if( tc < current ) {
							tm++;
							continue;
						}else{
							revert = true;
//							System.out.println("Reverted: "+current);
							tn++;
							continue;
						}
					}
				}

				// increase exponent and decrease base
				if( revert ) {
//					System.out.println( "Inside revert: " + "m: " + tm + ",n: " + tn);
					if( tm != 2 ) {
						if( tc < current ) tn++;
						else tm--;
						continue;
					}else{
						if( tc < current ) {
							tn++;
							continue;
						}else{
							break;
						}
					}
				}
			}
		}
		return new Long(-1);
	}

	public boolean hasNext() {
		return true;
	}

	public void remove() {
	}

	public void reset() {
		m = 2;
		n = 2;
		current = 1;
	}

	public static void main( String[] argv ) {
		Powers pow = new Powers();
		for( int i = 0; i < 10000; i++ ) {
			System.out.println( pow.next().longValue() );
		}
	}
}
