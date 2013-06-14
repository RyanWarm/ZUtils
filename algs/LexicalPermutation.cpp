#include <iostream>
using namespace std;
void doPermute(char *s, int index, char *result, bool *used, int len) {
	if( index == len ) {
		cout << result << endl;
		return;
	}

	for( int i = 0; i < len; i++ ) {
		if( !used[i] ) {
			result[index] = s[i];
			used[i] = true;
			doPermute(s, index+1, result, used, len);
			used[i] = false;
		}
	}
}

int main() {
	char s[] = "ABCD";
	int len = strlen(s);
	char result[len];
	bool used[len];
	for( int i = 0; i < len; i++ ) used[i] = false;
	doPermute(s, 0, result, used, len);
	return 1;
}
