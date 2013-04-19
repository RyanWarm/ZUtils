import java.lang.StringBuffer;

public class StringInterleave {
	public static void doInterleave(String a, String b, int ia, int ib, StringBuffer result) {
		if( (ia+ib) == (a.length() + b.length()) ) {
			System.out.println(result.toString());
			return;
		}

		if( ia < a.length() ) {
			result.append(a.charAt(ia++));
			doInterleave(a, b, ia, ib, result);
			ia--;
			result.setLength(result.length()-1);
		}

		if( ib < b.length() ) {
			result.append(b.charAt(ib++));
			doInterleave(a, b, ia, ib, result);
			ib--;
			result.setLength(result.length()-1);
		}
	}

	public static void main(String[] args) {
		String a = "ACB";
		String b = "CD*";
		StringBuffer sb = new StringBuffer();
		doInterleave(a, b, 0, 0, sb);
	}
}
