#include<iostream>
#include<math.h>
using namespace std;

const long m = 6;
const long n = 12;
const long x = 60;
int *table;
int func(int remainingX, int remainingDices) {
	int result = 0;
	if (table[remainingX * n + remainingDices] != -1)
		return table[remainingX * n + remainingDices];
	if (remainingDices == 1) {
		if (remainingX >= 1 && remainingX <= m)
			result = 1;
		else
			result = 0;
	} else {
		for (int i = 1; i <= m; i++) {
			if ((remainingX - i) >= (remainingDices - 1))
				result += func(remainingX - i, remainingDices - 1);
		}
	}
	table[remainingX * n + remainingDices] = result;
	return result;
}
int main(int argc, char* argv[]) {
	long tableSize = n * m * n + n + 1;
	table = new int[tableSize];
	for (int i = 0; i < tableSize; i++)
		table[i] = -1;
	double cumProb = 0;
	for (int i = n; i <= x; i++) {
		double tmpf = func(i, n);
		double probI = tmpf / (long) pow(m, n);
		cumProb += probI;
	}
	printf("prob for x => %ld is:%11.10f\n", x, 1 - cumProb);
}
