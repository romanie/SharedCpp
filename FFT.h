#include <iostream>
#include <algorithm>
#include <complex>
#include <vector>
#include <cassert>
#include "/Users/roman/Dev/SharedCpp/DebugOutput.h"

using namespace std;

#define pi 3.1415926535897932384626433832795028841971

const int N = 1 << 15;

complex<double> T[N];
template<class S> void fft(S *p, complex<double> *P, int n, int k = 1) {
    if (n > 1) { 
    	complex<double> q; 
    	n /= 2;
        fft(p, P, n, k * 2); 
        fft(p + k, P + n, n, k * 2);
        for(int i = 0, j = 0; i < n; ++i, j += k)
            P[i + n] = P[i] - (q = P[i + n] * T[j]), P[i] +=q;
    } else *P = *p;
}

inline vector<int> fftFastMultiply(vector<int> a, vector<int> b) {
    int n = a.size() + b.size();
    for(; n & n - 1; n++);
    a.resize(n);
	b.resize(n);
    vector<complex<double> > P(n), Q(n);
    for (int i = 0; i < n; i++) {
    	T[i] = polar((double)1.0, (double)(2 * i * pi / n));
    }
    fft(&a[0], &P[0], n); 
	fft(&b[0], &Q[0], n);
    for (int i = 0; i < n; i++) {
    	Q[i] *= P[i]; 
    	T[i] = complex<double>(real(T[i]), -imag(T[i]));
    }
    fft(&Q[0], &P[0], n);
    for (int i = 0; i < n; i++) {
    	a[i] = (long long)(real(P[i]) / n + 0.5);
    }
    while (!a.empty() && a.back() == 0) a.pop_back();
    return a; 
}
