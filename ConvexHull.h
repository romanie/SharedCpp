#ifdef SHTRIX 
#include "DebugOutput.h"
#endif
#include <vector>
#include <algorithm>

using namespace std;

typedef long long scalar;
typedef int coor;

struct Point {
	coor x, y;
	Point() : x(0), y(0) {}
	Point(coor x, coor y) : x(x), y(y) {}
	int quad() const {
		if (y >= 0) {
			if (x >= 0) return 0;
			else        return 1;
		} else {
			if (x < 0) return 2;
			else       return 3;
		}
	}
};

OUT(Point, p) {
	return o << "(" << p.x << ", " << p.y << ")";
}

inline bool operator == (const Point &a, const Point &b) {
	return a.x == b.x && a.y == b.y;
}

inline Point operator + (const Point &a, const Point &b) {
	return Point(a.x + b.x, a.y + b.y);
}

inline Point operator - (const Point &a, const Point &b) {
	return Point(a.x - b.x, a.y - b.y);
}

inline scalar vec(const Point &a, const Point &b) {
	return (scalar)(a.x) * b.y - (scalar)(a.y) * b.x;
}

inline scalar S(const Point &a, const Point &b, const Point &c) {
	return vec(a, b) + vec(b, c) + vec(c, a);
}

inline bool by_xy(const Point &a, const Point &b) {
	if (a.x != b.x) return a.x < b.x;
	return a.y < b.y;
}

inline bool by_yx(const Point &a, const Point &b) {
	if (a.y != b.y) return a.y < b.y;
	return a.x < b.x;
}

inline bool by_vec(const Point &a, const Point &b) {
	return vec(a, b) > 0;
}

inline bool by_vec_with_quads(const Point &a, const Point &b) {
	if (a.quad() != b.quad()) return a.quad() < b.quad();
	return vec(a, b) > 0;
}

vector<Point> convexHull(vector<Point> v) {
	if (v.size() <= 2) return v;
	Point p0;
	int id = -1;
	for (int i = 0; i < (int)v.size(); i++)
		if (id == -1 || by_xy(v[i], p0)) {
			p0 = v[i];
			id = i;
		}
	swap(v[0], v[id]);
	for (int i = 0; i < (int)v.size(); i++) v[i] = v[i] - p0;
	sort(v.begin() + 1, v.end(), by_vec);
	vector<Point> st;
	st.push_back(v[0]);
	st.push_back(v[1]);
	for (int i = 2; i < (int)v.size(); i++) {
		while (st.size() >= 2 && S(st[(int)st.size() - 2], st.back(), v[i]) <= 0) st.pop_back();
		st.push_back(v[i]);
	}
	for (int i = 0; i < st.size(); i++) st[i] = st[i] + p0;
	return st;
}
