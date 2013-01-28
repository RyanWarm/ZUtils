import java.util.ArrayList;
import java.util.HashSet;
import java.util.Iterator;

public class NextPowers implements Iterator<Long> {
	private static class IntPair {
		public IntPair(int a, int b) {
			this.a = a;
			this.b = b;
		}
		public int a;
		public int b;

		@Override
		public String toString() {
			StringBuilder sb = new StringBuilder();
			sb.append('[').append(a).append(',').append(b).append(']');

			return sb.toString();
		}
	}
	private ArrayList<IntPair> elems = new ArrayList<IntPair>();
	private HashSet<Integer> preSet = new HashSet<Integer>();

	public NextPowers () {
		elems.add(new IntPair(2, 2));
	}

	public void reset() {
		elems.clear();
		preSet.clear();
		elems.add(new IntPair(2, 2));
	}

	@Override
	public boolean hasNext() {
		return true;
	}

	private long prev = -1;
	@Override
	public Long next() {
		long n = next_();
		while (n == prev) {
			prev = n;
			n = next_();
		}
		prev = n;
		return n;
	}
	public long next_() {
		long min = Long.MAX_VALUE;
		int minI = Integer.MAX_VALUE;
		for (int i = 0; i < elems.size(); ++i) {
			IntPair ip = elems.get(i);
			long v = (long)Math.pow(ip.a, ip.b);
			if (v < min) {
				min = v;
				minI = i;
			}
		}
		IntPair ip = elems.get(minI);
		preSet.add(ip.a);
		if (ip.b == 2) {
			ip.b = 3;
			elems.add(new IntPair(ip.a + 1, 2));
		} else {
			ip.b ++;
		}

		return min;
	}

	@Override
	public void remove() {
		// TODO Auto-generated method stub
	}

	public static void main(String[] args) {
		NextPowers np = new NextPowers();
		for (int i = 0; i < 10000; ++i) {
			System.out.println(np.next());
		}
	}
}
