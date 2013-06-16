#include <vector>
#include <stack>
#include <iostream>
using namespace std;

class Solution {
public:
    static int maxArea(vector<int> &height) {
		int result = 0;
		stack<int> s;
		int size = height.size();
		s.push(0);
		for( int i = 1; i < size; i++ ) {
			if( i == size-1 || height[i+1] < height[i] ) {
				cout << "processing: " << i << endl;
				int tmp = -1;
				cout << "stack size: " << s.size() << endl;
				while( !s.empty() && height[s.top()] > height[i] ) {
					tmp = s.top();
					s.pop();
					cout << "pop: " << tmp << endl;
				}
				if( tmp != -1 ) {
					tmp = (i-tmp)*height[i];
					if( tmp > result ) {
						result = tmp;
						cout << "got one: " << tmp << endl;
					}
				}
			}
			if( i != size-1 && height[i-1] < height[i] ) {
				s.push(i);
				cout << "push: " << i << endl;
			}
		}
		while( !s.empty() ) {
			int tmp = s.top();
			s.pop();
			cout << "last pop: " << tmp << endl;
			tmp = (size-1-tmp)*height[tmp];
			cout << "last calc: " << tmp << endl;
			if( tmp > result ) result = tmp;
		}
		return result;
    }
};

int main() {
	vector<int> inp;
	inp.push_back(2);
	inp.push_back(3);
	inp.push_back(10);
	inp.push_back(5);
	inp.push_back(7);
	inp.push_back(8);
	inp.push_back(9);
	int r = Solution::maxArea(inp);
	cout << r << endl;
	return 1;
}
