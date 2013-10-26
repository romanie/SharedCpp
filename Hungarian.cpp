#include "Hungarian.h"

int main() {
	const int n = 8;
	for (int iter = 0; iter < 1000; iter++) {
		Assignment<n> W;
		int a[n][n];
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				W.a[i][j] = a[i][j] = rand() % 10000;
		int mn = W.Maximize(), mx = W.Minimize();
		int A = -1000000000, B = 1000000000;
		vector<int> p(n);
		for (int i = 0; i < n; i++) p[i] = i;
		do {
			int sum = 0;
			for (int i = 0; i < n; i++) sum += a[i][p[i]];
			A = max(A, sum);
			B = min(B, sum);
		} while (next_permutation(p.begin(), p.end()));
		assert(A == mx);
		assert(B == mn);
	}
	cerr << "OK" << endl;
	return 0;
}



