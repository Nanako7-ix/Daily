#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

template<typename Flow, typename Cost, template<typename T> typename Cmp_Fn>
struct CostFlow {
	struct _Edge {
		int to;
		Flow cap;
		Cost cost;
		_Edge(int to, Flow cap, Cost cost) : to(to), cap(cap), cost(cost) {}
	};

	int n;
	vector<_Edge> e;
	vector<vector<int>> g;
	vector<Cost> h, dp;
	vector<int> pre;

	CostFlow(int n) : n(n), g(n + 1), h(n + 1) { }

	void add(int u, int v, Flow cap, Cost cost) {
		g[u].push_back(e.size());
		e.emplace_back(v, cap, cost);
		g[v].push_back(e.size());
		e.emplace_back(u, 0, -cost);
	}

	bool dijkstra (int s, int t) {
		dp.assign(n + 1, numeric_limits<Cost>::max());
		pre.assign(n + 1, -1);
		std::priority_queue<pair<Cost, int>, vector<pair<Cost, int>>, Cmp_Fn<pair<Cost, int>>> q;
		dp[s] = 0;
		q.emplace(dp[s], s);
		while(!q.empty()) {
			auto [d, u] = q.top();
			q.pop();
			if(dp[u] != d) continue;
			for(auto i : g[u]) {
				auto [v, cap, cost] = e[i];
				if(cap > 0 && dp[u] + h[u] - h[v] + cost < dp[v]) {
					dp[v] = dp[u] + h[u] - h[v] + cost;
					pre[v] = i;
					q.emplace(dp[v], v);
				}
			}
		}
		return dp[t] != numeric_limits<Cost>::max();
	}

	pair<Flow, Cost> flow(int s, int t) {
		Flow flow = 0;
		Cost cost = 0;

		for (int i = 0; i < 2; i++) {  
			for (auto e : edges()) {
				h[e.to] = std::min(h[e.to], h[e.from] + e.cost);
			}
		}

		while (dijkstra (s, t)) {
			for(int i = 1; i <= n; ++i) {
				h[i] += dp[i];
			}
			Flow aug = numeric_limits<Flow>::max();
			for(int u = t; u != s; u = e[pre[u] ^ 1].to) {
				aug = min(aug, e[pre[u]].cap);
			}
			for(int u = t; u != s; u = e[pre[u] ^ 1].to) {
				e[pre[u]].cap -= aug;
				e[pre[u] ^ 1].cap += aug;
			}
			flow += aug;
			cost += aug * h[t];
		}
		return {flow, cost};
	}

	struct Edge {
		int from, to;
		Flow cap, flow;
		Cost cost;
	};

	vector<Edge> edges() {
		vector<Edge> res;
		for(int i = 0; i < (int)e.size(); i += 2) {
			Edge x;
			x.from = e[i + 1].to;
			x.to = e[i].to;
			x.cap = e[i].cap + e[i + 1].cap;
			x.flow = e[i].cap;
			x.cost = e[i].cost;
			res.push_back(x);
		}
		return res;
	}
};

constexpr int inf = 300 * 300;

void Thephix() {
	int n, m;
	cin >> n >> m;
	vector<int> a(n + 1), d(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		d[i] = a[i] - a[i - 1];
	}
	
	int s = n + 2, t = n + 3;
	int sum = 0;
	CostFlow<int, int, greater> mcmf(n + 3);
	for (int u = 1; u <= n; ++u) {
		if (d[u] > 0) {
			mcmf.add(s, u, d[u], 0);
		}
		if (d[u] < 0) {
			mcmf.add(u, t, -d[u], 0);
			sum -= d[u];
		}
	}
	mcmf.add(s, n + 1, inf, 0);
	for (int i = 1; i <= m; ++i) {
		int l, r;
		cin >> l >> r;
		r++;
		mcmf.add(r, l, inf, 1);
	}

	auto [f, c] = mcmf.flow(s, t);
	if (f != sum) c = -1;
	cout << c << "\n";
}

int main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	int T = 1;
	// cin >> T;

	while (T--) {
		Thephix();
	}

	return 0;
}
