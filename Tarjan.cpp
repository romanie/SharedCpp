#include "Tarjan.h"
#include <iostream>
#include <algorithm>
#include <vector>

void add(vector<pii> &v, int x, int y) {
	v.push_back(make_pair(x, y));
}

int main() {
	vector<pii> s;
	add(s, 0, 1);
	add(s, 1, 2);
	add(s, 1, 3);
	add(s, 1, 4);
	add(s, 0, 5);
	add(s, 3, 6);
	add(s, 3, 7);
	Tarjan T(8, s);
	vector<pii> q;
	add(q, 2, 3);
	add(q, 2, 4);
	add(q, 4, 5);
	add(q, 3, 1);
	add(q, 1, 3);
	add(q, 6, 7);
	add(q, 7, 6);
	add(q, 5, 6);
	add(q, 4, 7);

	vector<int> res = T.solve(q);
	for (int i = 0; i < q.size(); i++) {
		printf("%d %d -> %d\n", q[i].first, q[i].second, res[i]);
	}
}