#include "DebugOutput.h"
#include "Hash.h"
#include <map>
#include <string>

using namespace std;

string genRandom() {
	string s = "";
	for (int i = 0; i < 5; i++) {
		s += rand() % 3 + 'a';
	}
	return s;
}

void stressInt() {
	map<int, string> m;
	static HashTable<int, string, 100> ht;
	for (int iter = 0; iter < 100; iter++) {
		int key = rand() % 100000;
		string val = genRandom();
		if (rand() % 2) {
			m[key] = val;
			ht[key] = val;
		} else if (rand() % 2) {
			bool hasm = (m.find(key) != m.end());
			bool hasht = (ht.find(key) != ht.end());
			if (hasm != hasht) {
				cerr << "ERROR" << endl;
				exit(0);
			}
		} else {
			if (m[key] != ht[key]) {
				cerr << "ERROR" << endl;
				exit(0);
			}
		}
	}
	if (ht.size() != m.size()) {
		cerr << "ERROR" << endl;
		exit(0);
	}
	cerr >> ht.keys() << endl;
	cerr >> ht.values() << endl;
	cerr >> ht.array() << endl;
}

int main() {
	stressInt();
	return 0;
}