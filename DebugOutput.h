#ifndef DEBUG_OUTPUT_H
#define DEBUG_OUTPUT_H

#include "Colors.h"

#include <iostream>
#include <string>
#include <sstream>

#include <algorithm>

#include <map>
#include <set>
#include <bitset>
#include <vector>
#include <queue>
#include <list>
#include <deque>

using namespace std;

#ifndef DEBUG_COLOR
#define DEBUG_COLOR YELLOW
#endif

#ifndef COLORIZE
// This option may lead to significant performance drop
#define COLORIZE true
#endif

#ifndef DO_DOUBLE_PRECISION
#define DO_DOUBLE_PRECISION 5
#endif

#ifndef DEB
#define DEB basePrint
#endif

#ifndef DEBX
#define DEBX basePrintX
#endif

#ifndef CONV
#define CONV convert
#endif

#ifndef OUT
#define OUT(TYPE, obj) inline ostream& operator<<(ostream &o, const TYPE &obj)
#define NOUT(TYPE, stream, obj) inline ostream& operator<<(ostream &stream, const TYPE &obj)
#define WOUT(TYPE, obj) inline ostream& operator>>(ostream &o, const TYPE &obj)
#endif

namespace std {

template<class T> 
string toBinary(T x, int fixedLen = 32) {
	string res(fixedLen, '0');
	for (int i = 0; i < fixedLen; i++) res[i] += bool(x & (1 << i));
	return res;
}

//=============================convert==============================
// useful for bitset
template<unsigned long SIZE>
vector<int> convert(const bitset<SIZE> &b) {
	vector<int> v(b.size());
	for (int i = 0; i < b.size(); i++) v[i] = b[i];
	return v;
}

vector<char> convert(const string &b) {
	vector<char> v(b.size());
	for (int i = 0; i < v.size(); i++) v[i] = b[i];
	return v;
}

//=============================colorize=============================
string colorize(const string &s) {
	if (!COLORIZE) return s;
	string p = "";
	string reset = RESET;
	for (int i = 0; i < s.size(); i++) {
		bool has = true;
		for (int j = 0; j < reset.size(); j++)
			if (s[i + j] != reset[j])
				has = false;
		if (has) {
			i += reset.size() - 1;
		} else {
			p += s[i];
		}
	}
	return DEBUG_COLOR + p + RESET;
}

//=============================basePrint/DEB======================
// TODO(roman)
// string stlprintf(const char *, ...) {
// 	ostringstream oss;

// 	return oss.str();
// }


template<class E> 
string basePrint(const E &x) {
	stringstream os;
	os << x;
	return colorize(os.str());
}

template<>
string basePrint(const string &x) {
	stringstream os;
	os << "\"" << x << "\"";
	return colorize(os.str());
}

template<>
string basePrint(const double &x) {
	stringstream os;
	char buf[400];
	memset(buf, sizeof(buf), 0);
	stringstream format;
	format << "%." << DO_DOUBLE_PRECISION << "lf";
	sprintf(buf, format.str().c_str(), x);
	for (int i = 0; buf[i]; i++) os << buf[i];
	return colorize(os.str());
}

template<>
string basePrint(const char &x) {
	stringstream os;
	os << "\'" << x << "\'";
	return colorize(os.str());
}

template<class E, int SIZE_Y>
string basePrint(const E x[][SIZE_Y], int sizex, int sizey = SIZE_Y) {
	stringstream os;
	for (int i = 0; i < sizex; i++) {
		for (int j = 0; j < sizey; j++) {
			if (j) os << " ";
			os << basePrint(x[i][j]);
		}
		os << "\n";
	}
	return colorize(os.str());
}

template<class E>
string basePrint(E *x, const E *y) {
	E *xx = x;
	stringstream os;
	os << "{";
	while (xx != y) {
		if (xx != x) os << ", ";
		os << basePrint(*xx);
		xx++;
	}
	os << "}";
	return colorize(os.str());
}

template<class E>
string basePrint(const E *x, int size) {
	stringstream os;
	os << "{";
	for (int i = 0; i < size; i++) {
		if (i) os << ", ";
		os << basePrint(x[i]);
	}
	os << "}";
	return colorize(os.str());
}

template<class E>
string basePrintX(const E *x, int size) {
	stringstream os;
	os << "{";
	for (int i = 0; i < size; i++) {
		if (i) os << ",\n ";
		os << basePrint(x[i]);
	}
	os << "}";
	return colorize(os.str());
}

//=============================pair===============================
template<class A, class B> 
ostream& operator<<(ostream &oss, const pair<A, B> &p) {
	ostringstream os;
	os << "(" << basePrint(p.first) << ", " << basePrint(p.second) << ")";
	return oss << colorize(os.str());
}

template<class A, class B> 
ostream& operator>>(ostream &oss, const pair<A, B> &p) {
	ostringstream os;
	os << "(first:  " << basePrint(p.first) << 
	   ",\n second: " << basePrint(p.second) << ")";
	return oss << colorize(os.str());
}

//=============================vector=============================
template<class E> 
ostream& operator<<(ostream &oss, const vector<E> &v) { 
	ostringstream os;
	os << "{"; 
	for (typename vector<E>::const_iterator it = v.begin(); it != v.end(); it++) {
		if (it != v.begin()) os << ", ";
		os << basePrint(*it);
	}
	os << "}"; 
	return oss << colorize(os.str()); 
}

template<class E> 
ostream& operator>>(ostream &oss, const vector<E> &v) { 
	ostringstream os;
	os << "{";
	int idx = 0;
	for (typename vector<E>::const_iterator it = v.begin(); it != v.end(); it++) {
		if (it != v.begin()) os << ",\n ";
		os << "[" << idx << "] => " << basePrint(*it);
		idx++;
	}
	os << "}"; 
	return oss << colorize(os.str()); 
}

//=============================set================================
template<class E> 
ostream& operator<<(ostream &oss, const set<E> &v) { 
	ostringstream os;
	os << "{"; 
	for (typename set<E>::const_iterator it = v.begin(); it != v.end(); it++) {
		if (it != v.begin()) os << ", ";
		os << basePrint(*it);
	}
	os << "}"; 
	return oss << colorize(os.str()); 
}

template<class E> 
ostream& operator>>(ostream &oss, const set<E> &v) { 
	ostringstream os;
	os << "{"; 
	for (typename set<E>::const_iterator it = v.begin(); it != v.end(); it++) {
		if (it != v.begin()) os << ",\n ";
		os << basePrint(*it);
	}
	os << "}"; 
	return oss << colorize(os.str()); 
}

//=============================multiset===========================
template<class E> 
ostream& operator<<(ostream &oss, const multiset<E> &v) { 
	ostringstream os;
	os << "{"; 
	for (typename multiset<E>::const_iterator it = v.begin(); it != v.end(); it++) {
		if (it != v.begin()) os << ", ";
		os << basePrint(*it);
	}
	os << "}"; 
	return oss << colorize(os.str()); 
}

template<class E>
ostream& operator>>(ostream &oss, const multiset<E> &v) { 
	ostringstream os;
	os << "{"; 
	for (typename multiset<E>::const_iterator it = v.begin(); it != v.end(); it++) {
		if (it != v.begin()) os << ",\n ";
		os << basePrint(*it);
	}
	os << "}"; 
	return oss << colorize(os.str()); 
}

//=============================map=================================
template<class K, class V> 
ostream& operator<<(ostream &oss, const map<K, V> &v) { 
	ostringstream os;
	os << "{"; 
	for (typename map<K, V>::const_iterator it = v.begin(); it != v.end(); it++) {
		if (it != v.begin()) os << ", ";
		os << basePrint(*it);
	}
	os << "}";
	return oss << colorize(os.str()); 
}

template<class K, class V> 
ostream& operator>>(ostream &oss, const map<K, V> &v) { 
	ostringstream os;
	os << "{"; 
	for (typename map<K, V>::const_iterator it = v.begin(); it != v.end(); it++) {
		if (it != v.begin()) os << ",\n ";
		os << basePrint(it->first) << " => " << basePrint(it->second);
	}
	os << "}";
	return oss << colorize(os.str()); 
}


//=============================queue==============================
template<class E>
ostream& operator<<(ostream &oss, queue<E> v) {
	ostringstream os;
	os << "<";
	bool first = true;
	while (!v.empty()) {
		if (first) {
			first = false;
		} else {
			os << ", ";
		}
		os << basePrint(v.front());
		v.pop();
	}
	os << ">";
	return oss << colorize(os.str());
}

template<class E>
ostream& operator>>(ostream &oss, queue<E> v) {
	ostringstream os;
	os << "<";
	bool first = true;
	while (!v.empty()) {
		if (first) {
			first = false;
		} else {
			os << ",\n ";
		}
		os << basePrint(v.front());
		v.pop();
	}
	os << ">";
	return oss << colorize(os.str());
}

//=============================deque==============================
template<class E>
ostream& operator<<(ostream &oss, deque<E> v) {
	ostringstream os;
	os << "<";
	bool first = true;
	while (!v.empty()) {
		if (first) {
			first = false;
		} else {
			os << ", ";
		}
		os << basePrint(v.front());
		v.pop_front();
	}
	os << ">";
	return oss << colorize(os.str());
}

template<class E>
ostream& operator>>(ostream &oss, deque<E> v) {
	ostringstream os;
	os << "<";
	bool first = true;
	while (!v.empty()) {
		if (first) {
			first = false;
		} else {
			os << ",\n ";
		}
		os << basePrint(v.front());
		v.pop_front();
	}
	os << ">";
	return oss << colorize(os.str());
}

//=============================list=============================
template<class E> 
ostream& operator<<(ostream &oss, const list<E> &v) { 
	ostringstream os;
	os << "{"; 
	for (typename list<E>::const_iterator it = v.begin(); it != v.end(); it++) {
		if (it != v.begin()) os << ", ";
		os << basePrint(*it);
	}
	os << "}"; 
	return oss << colorize(os.str()); 
}

template<class E> 
ostream& operator>>(ostream &oss, const list<E> &v) { 
	ostringstream os;
	os << "{";
	int idx = 0;
	for (typename list<E>::const_iterator it = v.begin(); it != v.end(); it++) {
		if (it != v.begin()) os << ",\n ";
		os << "[" << idx << "] => " << basePrint(*it);
		idx++;
	}
	os << "}"; 
	return oss << colorize(os.str()); 
}

// //===============================meta===============================
// //template<class A, class B>
// string operator:(const int &a, const int &b) {
// 	stringstream ss;
// 	ss << a << " " << b << endl;
// 	return ss.str();
// 

};

#endif
