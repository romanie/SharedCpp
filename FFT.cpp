#include "FFT.h"

vector<int> conv(long long x) {
	vector<int> res;
	while (x > 0) {
		res.push_back(x % 10);
		x /= 10;
	}
	return res;
}

long long conv(vector<int> v) {
	long long x = 0;
	for (int i = v.size() - 1; i >= 0; i--) {
		x *= 10;
		x += v[i];
	}
	return x;
}

int main() {
	for (int iter = 0; iter < 1000; iter++) {
		int a = rand() % 100000;
		int b = rand() % 100000;
		assert((long long) a * b == conv(fastmul(conv(a), conv(b))));
	}
    cerr << "OK" << endl;
	return 0;
}