#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <set>
#include <map>

#define all(v) (v).begin(),(v).end()
#define DEB(v) deb(all(v))
using namespace std;

template<class A, class B> 
ostream& operator<<(ostream &oss, const pair<A, B> &p) {
	stringstream os;
	os << "(" << p.first << ", " << p.second << ")";
	return oss << os.str();
}

template<class T>
string deb(T a, T b) {
	ostringstream oss;
	oss << "{";
	while (a != b) {
		oss << *a;
		T x = a; x++;
		if (x != b) oss << ", ";
		a++;
	}
	oss << "}";
	return oss.str() + "\n";
}

int main() {
	vector<int> v;
	v.push_back(0);
	v.push_back(1);
	v.push_back(2);
	cout << DEB(v) << endl;
	int a[] = {0, 4, 5};
	cout << deb(a, a + 3) << endl;
	set<int> s;
	s.insert(2);
	s.insert(6);
	s.insert(10);
	cout << DEB(s) << endl;
	map<int, int> m;
	m[5] = 12;
	m[17] = 6;
	cout << DEB(m) << endl;
	return 0;
}