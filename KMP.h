#include "DebugOutput.h"
#include <iostream>
#include <cstring>
#include <string>
#include <vector>

// Builds prefix-function for string s in O(|S|) time
inline void kmp(const char *s, int *p, int n) {
	p[0] = -1;
	for (int i = 1; i < n; i++) {
		int x = p[i - 1];
		while (x != -1 && s[x + 1] != s[i]) {
			x = p[x];
		}
		if (s[x + 1] == s[i]) {
			p[i] = x + 1;
		} else {
			p[i] = -1;
		}
	}
	for (int i = 0; i < n; i++) p[i]++;
}

inline void kmp(const char *s, int *p) {
	kmp(s, p, strlen(s));
}

inline std::vector<int> kmp(const std::string &s) {
	std::vector<int> res(s.size(), 0);
	kmp(s.data(), res.data(), s.size());
	return res;
}

inline void kmp(const std::string &s, std::vector<int> &p) {
	p.assign(s.size(), 0);
	kmp(s.data(), p.data(), s.size());
}

// Searches for the first occurrence of string 'what' in the string 'where'
// in time O(|what| + |where|)
inline int findFirstOccurrence(const char *where, int size_where, 
							   const char *what, int size_what) {

	int total_size = size_what + size_where + 1;
	char *s = new char[total_size];
	int *p = new int[total_size];
	for (int i = 0; i < size_what; i++) s[i] = what[i];
	s[size_what] = '$';
	for (int i = 0; i < size_where; i++) s[i + 1 + size_what] = where[i];
	kmp(s, p);
	for (int i = size_what + 1; i < total_size; i++) {
		if (p[i] == size_what) {
			delete(s);
			delete(p);
			return i - 2 * size_what;
		}
	}
	delete(s);
	delete(p);
	return -1;
}

// Searches for the first occurrence of string 'what' in the string 'where'
// in time O(|what| + |where|)
inline int findFirstOccurrence(const char *where, const char *what) {
	return findFirstOccurrence(where, strlen(where), what, strlen(what));
}

inline int findFirstOccurrence(const std::string &where, const std::string &what) {
	return findFirstOccurrence(where.data(), where.size(), what.data(), what.size());
}



// Searches for the all occurrences of string 'what' in the string 'where'
// in time O(|what| + |where|)
inline void findAllOccurrences(const char *where, int size_where, 
							   const char *what, int size_what,
							   std::vector<int> &result) {
	int total_size = size_what + size_where + 1;
	char *s = new char[total_size];
	int *p = new int[total_size];
	for (int i = 0; i < size_what; i++) s[i] = what[i];
	s[size_what] = '$';
	for (int i = 0; i < size_where; i++) s[i + 1 + size_what] = where[i];
	kmp(s, p);
	for (int i = size_what + 1; i < total_size; i++) {
		if (p[i] == size_what) {
			result.push_back(i - 2 * size_what);
		}
	}
	delete(s);
	delete(p);
}

inline std::vector<int> findAllOccurrences(const char *where, int size_where, 
				    			     	   const char *what, int size_what) {
	vector<int> result;
	findAllOccurrences(where, size_where, what, size_what, result);
	return result;
}


inline std::vector<int> findAllOccurrences(const char *where, const char *what) {
	std::vector<int> result;
	findAllOccurrences(where, strlen(where), what, strlen(what), result);
	return result;
}

inline std::vector<int> findAllOccurrences(const std::string &where, const std::string &what) {
	std::vector<int> result;
	findAllOccurrences(where.data(), where.size(), what.data(), what.size(), result);
	return result;
}

inline void findAllOccurrences(const char *where, const char *what, 
							   std::vector<int> &result) {
	findAllOccurrences(where, strlen(where), what, strlen(what), result);
}

inline void findAllOccurrences(const std::string &where, const std::string &what, 
							   std::vector<int> &result) {
	findAllOccurrences(where.data(), where.size(), what.data(), what.size(), result);
}