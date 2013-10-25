#include "DebugOutput.h"
#include <iostream>
#include <algorithm>
#include <vector>

typedef pair<int, int> pii;
	
class Tarjan {
  public:
  	static const int MAX_N = 100000;
	static const int MAX_Q = 300000;

  	int p[MAX_N], root[MAX_N], h[MAX_N];
  	int who(int u) {
  		if (p[u] == -1) return u;
  		return p[u] = who(p[u]);
  	}

  	void unite(int u, int v) {
  		u = who(u);
  		v = who(v);
  		if (rand() & 1) p[u] = v;
  		else            p[v] = u;

  		if (h[root[u]] > h[root[v]]) root[who(u)] = root[v];
  		else                         root[who(u)] = root[u];
  	}

  	int n;
  	int lastE[MAX_N], prevE[2 * MAX_N], vE[2 * MAX_N], numE;
  	int lastQ[MAX_Q], prevQ[2 * MAX_Q], vQ[2 * MAX_Q], idQ[2 * MAX_Q], numQ;
  	int visited[MAX_N];
  	void add(int *last, int *prev, int *v, int &num, int a, int b, int *id = 0, int cur_id = 0) {
  		prev[num] = last[a];
  		v[num] = b;
  		if (id) id[num] = cur_id;
  		last[a] = num++;
  	}
  	Tarjan() {}
  	Tarjan(int n, const vector<pii> &edges) : n(n) {
  		numE = 0;
  		for (int i = 0; i < n; i++) {
  			lastE[i] = -1;
  		}

  		for (int i = 0; i < (int)edges.size(); i++) {
  			add(lastE, prevE, vE, numE, edges[i].first, edges[i].second);
  			add(lastE, prevE, vE, numE, edges[i].second, edges[i].first);
  		}
  	}


  	vector<int> result;
  	void dfs(int u, int ch = 0, int pr = -1) {
  		visited[u] = true;
  		h[u] = ch;
  		for (int idx = lastQ[u]; idx >= 0; idx = prevQ[idx]) {
  			int v = vQ[idx];
  			int id = idQ[idx];
  			if (visited[v]) {
  				result[id] = root[who(v)];
  			}
  		}

  		for (int idx = lastE[u]; idx >= 0; idx = prevE[idx]) {
  			int v = vE[idx];
  			if (v == pr) continue;
  			dfs(v, ch + 1, u);
  		}

  		if (pr != -1) unite(u, pr);
  	}

  	vector<int> solve(const vector<pii> &query, int croot = 0) {
  		// returns pairs lca's in the exact same order that they appeared in 'query'
  		numQ = 0;
  		for (int i = 0; i < n; i++) {
  			lastQ[i] = -1;
  			visited[i] = 0;
  			p[i] = -1;
  			root[i] = i;
  		}
  		for (int i = 0; i < (int)query.size(); i++) {
  			add(lastQ, prevQ, vQ, numQ, query[i].first, query[i].second, idQ, i);
  			add(lastQ, prevQ, vQ, numQ, query[i].second, query[i].first, idQ, i);
  		}
  		result.assign(query.size(), -1);
  		dfs(croot);
  		return result;
  	}
};