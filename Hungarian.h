#include "/Users/roman/Dev/SharedCpp/DebugOutput.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

template<int Left, int Right, int Edges>
class MaxMatching { 
  public:
  	int last[Left], prev[Edges], v[Edges], m;
  	int mark[Left + Right], L[Left], R[Right], n, total;
	void reset(int left, int right) {
		m = 0;
		n = left;
		total = left + right;
		memset(last, -1, sizeof(int) * left);
		memset(L, -1, sizeof(int) * left);
		memset(R, -1, sizeof(int) * right);
	}
	MaxMatching(int left, int right): m(0), n(left), total(left + right) {
		memset(last, -1, sizeof(int) * left);
		memset(L, -1, sizeof(int) * left);
		memset(R, -1, sizeof(int) * right);
		reset(left, right);
	}

	void add(int a, int b) { 
		prev[m] = last[a];
		v[m] = b;
		last[a] = m;
		m++;
	}
	bool dfs(int u) {
		mark[u] = true;
		for (int i = last[u]; i >= 0; i = prev[i]) {
			mark[n + v[i]] = true;
			if (R[v[i]] == -1 || (!mark[R[v[i]]] && dfs(R[v[i]]))) {
				L[u] = v[i];
				R[v[i]] = u;
				return true;
			}
		}
		return false;
	}
	int build(vector<pair<int, int> > *result = NULL) { 
		while (true) {
			memset(mark, 0, sizeof(int) * total);
			bool ok = false;
			for (int i = 0; i < n; i++) 
				if (L[i] == -1 && !mark[i])
					if (dfs(i))
						ok = true;
			if (!ok) break;
		}

		int res = 0;
		for (int i = 0; i < n; i++)
			if (L[i] != -1) {
				if (result)	result->push_back(make_pair(i, L[i]));
				res++;
			}
		return res; 
	}
};

template<int MX> 
class Assignment { 
  private:
  	int br[MX], bc[MX];
  	MaxMatching<MX, MX, MX * MX> mm;
  public:
  	static const int INF = 1000000000;
	int n, a[MX][MX];
	Assignment(): n(MX), mm(MX, MX) {
		memset(a, 0, sizeof(a));
	}
	Assignment(int n): n(n), mm(n, n) {
		memset(a, 0, sizeof(a)); 
	}
	int maximize(vector<pair<int, int> > *result = NULL) {
		for (int i = 0; i < n; i++) br[i] = bc[i] = INF;
		for (int i = 0; i < n; i++) 
			for (int j = 0; j < n; j++) 
				br[i] = min(br[i], a[i][j]);
		for (int j = 0; j < n; j++) 
			for (int i = 0; i < n; i++) 
				bc[j] = min(bc[j], a[i][j] - br[i]);
		while (true) {
			mm.reset(n, n);

			for (int i = 0; i < n; i++) 
				for (int j = 0; j < n; j++) 
					if (a[i][j] == br[i] + bc[j]) 
						mm.add(i, j);

			if (mm.build() == n) {
				if (result) mm.build(result);
				break;
			}

			int mn = INF;

			for (int i = 0; i < n; i++) 
				if (mm.mark[i]) 
					for (int j = 0; j < n; j++) 
						if (!mm.mark[j + n])
							mn = min(mn, a[i][j] - br[i] - bc[j]);

			for (int i = 0; i < n; i++) 
				if (mm.mark[i]) 
					br[i] += mn;

			for (int j = 0; j < n; j++) 
				if (mm.mark[j + n])	
					bc[j] -= mn;
		}
		int res = 0;
		for (int i = 0; i < n; i++) res += br[i], res += bc[i];
		return res;
	}
	int minimize(vector<pair<int, int> > *result = NULL) {
		for (int i = 0; i < n; i++) 
			for (int j = 0; j < n; j++) { 
				a[i][j] = -a[i][j];
			}
		int res = maximize(result);
		int mn = INF;
		for (int i = 0; i < n; i++) mn = min(mn, br[i] = -br[i]), bc[i] = -bc[i];
		for (int i = 0; i < n; i++) br[i] -= mn, bc[i] += mn;
		return -res; 
	}
};