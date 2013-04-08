public class LongestSubWTRepeat {
	public int lengthOfLongestSubstring(String s) {
		int result = 0;
		int len = s.length();
		int start = 0, e = 0;
		int[] tmp = new int[26];
		for( int i = 0; i < 26; i++ ) tmp[i] = -1;
		int tmp_l = 0;
		while( e < len ) {
			if( tmp[s.charAt(e)-'a'] == -1 ) {
				tmp_l++;
				tmp[s.charAt(e)-'a'] = e;
				if( tmp_l > result ) result = tmp_l;
			} else {
				for( int i = start; i < tmp[s.charAt(e)-'a']; i++ ) {
					tmp[s.charAt(i)-'a'] = -1;
				}
				start = tmp[s.charAt(e)-'a'] + 1;
				tmp_l = e - tmp[s.charAt(e)-'a'];
				tmp[s.charAt(e)-'a'] = e;
			}
			e++;
		}
		
		return result;
	}
}
