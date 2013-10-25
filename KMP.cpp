#include "KMP.h"
#include <string>
#include <vector>
using namespace std;


int main() {

	char sa[] = "ababababcabababcabc";
	char sb[] = "abc";
	string a = "ababababcabababcabc";
	string b = "abc";
	cout << findFirstOccurrence(a, b) << " == 6" << endl;
	cout << findFirstOccurrence(sa, sb) << " == 6" << endl;
	vector<int> x[6];
	x[0] = findAllOccurrences(sa, sb);
	x[1] = findAllOccurrences(sa, strlen(sa), sb, strlen(sb));
	findAllOccurrences(sa, sb, x[2]);
	x[3] = findAllOccurrences(a, b);
	findAllOccurrences(a, b, x[4]);
	findAllOccurrences(a, b, x[5]);
	for (int i = 0; i < 6; i++) {
		cout << x[i] << endl;
	}
	return 0;
}