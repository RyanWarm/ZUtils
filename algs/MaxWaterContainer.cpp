class Solution {
public:
    static int maxArea(vector<int> &height) {
        map<int, int> vl, vr;
        int size = height.size();
        vl[0] = height[0];
        vr[size-1] = height[size-1];
        for( int i = 1; i < size-1; i++ ) {
            if( height[i-1] < height[i] ) vl[i] = height[i];
            if( height[i+1] < height[i] ) vr[i] = height[i];
        }
        int result = 0;
        int tmp = 0;
        for( map<int, int>::iterator it1 = vl.begin(); it1 != vl.end(); it1++ ) {
            for( map<int, int>::iterator it2 = vr.begin(); it2 != vr.end(); it2++ ) {
				if( it2->first <= it1->first ) continue;
                tmp = (it1->second < it2->second) ? it1->second : it2->second;
				tmp *= it2->first - it1->first;
				if( tmp > result ) result = tmp;
            }
        }
		return result;
    }
};

int main() {
	return 1;
}
