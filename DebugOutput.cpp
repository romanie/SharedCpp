#include "DebugOutput.h"
#include "Colors.h"

#define HEADER_COLOR RED

void testPair() {
	cerr << HEADER_COLOR << "Pair test" << RESET << endl;
	pair<int, int> p;
	p = make_pair(20, 45);
	cerr << p << endl;
	pair<int, string> b;
	b = make_pair(20, "abab");
	cerr << b << endl;
	pair<int, pair<string, int> > c;
	c = make_pair(11, make_pair("sdf", 34));
	cerr << c << endl;
	cerr >> c << endl;
}

void testVector() {
	cerr << HEADER_COLOR << "Vector test" << RESET << endl;
	vector<int> v;
	v.push_back(1);
	cerr << v << endl;
	v.push_back(2);
	cerr << v << endl;

	vector<string> vs;
	vs.push_back("abcd");
	cerr << vs << endl;
	vs.push_back("453sfd");
	cerr << vs << endl;

	vector<vector<string> > r(3);
	r[0].push_back("123");
	r[0].push_back("234");
	r[1].push_back("672");
	r[1].push_back("987");
	r[2].push_back("dsfjk");
	r[2].push_back("nxcmvns");
	cerr >> r << endl;

	vector<double> w;
	w.push_back(0.0);
	w.push_back(1.1);
	w.push_back(1.5);
	w.push_back(2.0);
	w.push_back(1e380);
	w.push_back(0.0 / 0.0);
	cerr << w << endl;
}

void testSet() {
	cerr << HEADER_COLOR << "Set test" << RESET << endl;
	set<int> v;
	v.insert(1);
	cerr << v << endl;
	v.insert(2);
	cerr << v << endl;
	set<string> vs;
	vs.insert("sgdf");
	cerr << vs << endl;
	vs.insert("dfghfghfgh");
	cerr << vs << endl;
	vs.insert("3274rsd");
	vs.insert("uhcb");
	cerr >> vs << endl;
}

void testMultiset() {
	cerr << HEADER_COLOR << "Multiset test" << RESET << endl;
	multiset<int> m;
	m.insert(1);
	cerr << m << endl;
	m.insert(1);
	m.insert(2);
	cerr << m << endl;

	multiset<pair<string, string> > mm;
	mm.insert(pair<string, string> ("afg", "bdf"));
	mm.insert(pair<string, string> ("cdfhjn", "weqd"));
	cerr >> mm << endl;
}

void testMap() {
	cerr << HEADER_COLOR << "Map test" << RESET << endl;
	map<string, int> v;
	v["sdfdf"] = 6;
	v["dfg"] = 7;
	v["uuasd"] = 9;
	cerr << v << endl;
	cerr >> v << endl;
}

void testConvert() {
	cerr << HEADER_COLOR << "Convert test" << RESET << endl;
	bitset<15> b;
	b[0] = 1;
	b[6] = 1;
	b[14] = 1;
	vector<int> q = CONV(b);
	cerr << YELLOW << "Bitset: " << RESET;
	cerr << q << endl;

	string s = "hdsijfn";
	vector<char> v = CONV(s);
	cerr << YELLOW << "String: " << RESET;
	cerr << v << endl;
}

void testStatic() {
	cerr << HEADER_COLOR << "Static test" << RESET << endl;
	
	int a[10];
	memset(a, 0, sizeof(a));
	for (int i = 0; i < 10; i++) {
		a[i] = i;
	}
	cerr << DEB(a, 10) << endl << endl;

	int b[5][5];
	memset(b, 0, sizeof(b));
	for (int i = 0; i < 5; i++) b[i][i] = i + 1;
	cerr << DEB(b, 5) << endl;
	cerr << DEB(b, 5, 5) << endl;

	string w[] = {"asb", "er", "urw", "juie"};
	cerr << DEB(w, 2) << endl << endl;
	cerr << DEBX(w, 4) << endl << endl;

	string t[][3] = {{"a", "b", "c"}, {"d", "e", "f"}};
	cerr << DEB(t, 2) << endl;
}

void testQueue() {
	cerr << HEADER_COLOR << "Queue test" << RESET << endl;

	queue<string> q;
	q.push("a");
	q.push("abab");
	q.push("cbabdsb");
	q.push("uuwoxkj");
	cerr << q << endl;


	queue<vector<int> > v;
	int a[] = {1, 2, 3, 4, 5, 6};
	v.push(vector<int>(a, a + 2));
	v.push(vector<int>(a + 3, a + 4));
	v.push(vector<int>(a + 2, a + 5));
	v.push(vector<int>(a + 1, a + 2));

	cerr >> v << endl;
}

void testDeque() {
	cerr << HEADER_COLOR << "Deque test" << RESET << endl;

	deque<string> q;
	q.push_back("zxcs");
	q.push_back("rws");
	q.push_back("cdsc");
	q.push_back("oxkj");
	cerr >> q << endl;

	
	deque<vector<int> > v;
	int a[] = {9, 8, 7, 6, 5, 4};
	v.push_back(vector<int>(a, a + 2));
	v.push_back(vector<int>(a + 3, a + 4));
	v.push_back(vector<int>(a + 2, a + 5));
	v.push_back(vector<int>(a + 1, a + 2));

	cerr << v << endl;
}

void testList() {
	cerr << HEADER_COLOR << "List test" << RESET << endl;
	list<int> v;
	v.push_back(1);
	cerr << v << endl;
	v.push_back(2);
	cerr << v << endl;

	list<string> vs;
	vs.push_back("abcd");
	cerr << vs << endl;
	vs.push_back("453sfd");
	cerr << vs << endl;

	list<list<string> > r(3);
	list<string> l0, l1, l2;
	l0.push_back("123");
	l0.push_back("234");
	l1.push_back("672");
	l1.push_back("987");
	l2.push_back("dsfjk");
	l2.push_back("nxcmvns");
	r.push_back(l0);
	r.push_back(l1);
	r.push_back(l2);

	cerr >> r << endl;
}

struct point {
	int x, y, z;
	point(int x, int y, int z) : x(x), y(y), z(z) {}
};

OUT(point, w) {
	return o << "(" << w.x << ", " << w.y << ", " << w.z << ")";
}

void testCustom() {
//	cerr << stlprintf("svscv");
	cerr << HEADER_COLOR << "Custom test" << RESET << endl;
	vector<point> v;
	v.push_back(point(0, 0, 0));
	v.push_back(point(2, 5, 7));
	v.push_back(point(3, 1, 2));
	cout << v << endl;
}

int main() {
    testPair();
    testVector();
    testSet();
    testMultiset();
    testMap();
    testConvert();
    testStatic();
    testQueue();
    testDeque();
    testList();
    testCustom();
	return 0;
}
