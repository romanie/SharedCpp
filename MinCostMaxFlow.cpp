#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

template <typename FlowType, typename CostType, int maxV, int maxE> class MinCostMaxFlow {
private:
	static const CostType inf = 1000000000;
	int pre[maxE], last[maxV], v[maxE], Edges;
	FlowType cap[maxE];
	CostType w[maxE];
	int s, t, V;
	CostType dist[maxV];
	int path[maxV];

	void addOrEdge(int a, int b, FlowType _cap, CostType _w)
	{
		pre[Edges] = last[a];
		last[a] = Edges;
		v[Edges] = b;
		w[Edges] = _w;
		cap[Edges] = _cap;
		Edges++;
	}
public:
	MinCostMaxFlow(int _s, int _t, int _V) : s(_s), t(_t), V(_V) {
		for (int i = 0; i < maxV; i++) last[i] = -1;
		Edges = 0;
	}
	MinCostMaxFlow() {
		for (int i = 0; i < maxV; i++) last[i] = -1;
		Edges = 0;
	}
	void assign(int _s, int _t, int _V) { s = _s; t = _t; V = _V;}
	void addEdge(int a, int b, FlowType _cap, CostType _w, FlowType _reverseCap = 0) {
		addOrEdge(a, b, _cap, _w);
		addOrEdge(b, a, 0,	 -_w);
	}

	bool FordBellman() {
		for (int i = 0; i < V; i++) dist[i] = inf, path[i] = -1;
		dist[s] = 0;
		for (int i = 0; i < V; i++) {
			bool con = false;
			for (int j = 0; j < V; j++)
			for (int k = last[j]; k >= 0; k = pre[k]) if (cap[k] > 0)
				if (dist[v[k]] > dist[j] + w[k])
					dist[v[k]] = dist[j] + w[k], path[v[k]] = k, con = true;
			if (!con) break;
		}
		return dist[t] != inf;
	}

	pair<FlowType, CostType> runFlow() {
		pair<FlowType, CostType> flow = make_pair(inf, 0);
		for (int i = t; path[i] >= 0; i = v[path[i] ^ 1]) 
			flow.first = min(flow.first, cap[path[i]]);
		for (int i = t; path[i] >= 0; i = v[path[i] ^ 1]) {
			cap[path[i]] -= flow.first;
			cap[path[i] ^ 1] += flow.first;
			flow.second += w[path[i]] * flow.first;
		}
		return flow;
	}

	pair<FlowType, CostType> getResult() {
		pair<FlowType, CostType> res = make_pair(0, 0);
		while (FordBellman()) {
			pair<FlowType, CostType> h = runFlow();
			res.first += h.first;
			res.second += h.second;
		}
		return res;
	}
};



int main() {
	int n;
	scanf("%d", &n);
	static MinCostMaxFlow<int, int, 450, 450 * 450 * 3> Flow(0, 2 * n + 1, 2 * n + 2);
	int res = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			int cost;
			scanf("%d", &cost);
			res += cost;
			Flow.addEdge(i + 1, n + 1 + j, 1, -cost);
		}
	for (int i = 0; i < n; i++)
		Flow.addEdge(0, i + 1, 1, 0);
	for (int i = 0; i < n; i++)
		Flow.addEdge(n + 1 + i, 2 * n + 1, 1, 0);
	cout << res + Flow.getResult().second << endl;
	return 0;
}
