#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

struct EDCC {
	int n;
	vector<vector<array<int, 2>>> adj;
	vector<array<int, 2>> bridge;
	vector<int> stk;
	vector<int> dfn, low, bel;
	int cur, cnt, edges;

	EDCC () = default;

	EDCC (int n) { init(n); }

	void init (int n) {
		this -> n = n;
		adj.assign(n + 1, {});
		dfn.assign(n + 1, 0);
		low.assign(n + 1, 0);
		bel.assign(n + 1, 0);
		stk.clear();
		cur = cnt = edges = 0;
	}

	void add (int u, int v) {
		adj[u].push_back({v, edges++});
		adj[v].push_back({u, edges++});
	}

	void tarjan (int u, int fa) {
		dfn[u] = low[u] = ++cur;
		stk.push_back(u);
		for (auto [v, id] : adj[u]) {
			if ((id ^ fa) == 1) continue;
			if (dfn[v] == 0) {
				tarjan(v, id);
				low[u] = min(low[u], low[v]);
				if (dfn[u] < low[v]) {
					bridge.push_back({u, v});
				}
			} else {
				low[u] = min(low[u], dfn[v]);
			}
		}
		if (low[u] == dfn[u]) {
			int x = ++cnt;
			do {
				bel[x = stk.back()] = cnt;
				stk.pop_back();
			} while (x != u);
		}
	}

	vector<int> work() {
		for (int i = 1; i <= n; ++i) {
			if (dfn[i] == 0) tarjan(1, -1);
		}
		return bel;
	}

	auto getTree() -> pair<int, vector<vector<int>>> {
		int _n = *max_element(bel.begin() + 1, bel.end());
		vector<vector<int>> _adj(_n + 1);
		for (auto [u, v] : bridge) {
			_adj[bel[u]].push_back(bel[v]);
			_adj[bel[v]].push_back(bel[u]);
		}
		return pair {_n, _adj};
	}
};

void Thephix() {
	int n, m;
	cin >> n >> m;

	EDCC edcc(n);
	vector<vector<int>> adj(n + 1);
	map<array<int, 2>, int> id;
	for (int i = 1; i <= m; ++i) {
		int u, v;
		cin >> u >> v;
		edcc.add(u, v);
		adj[u].push_back(v);
		adj[v].push_back(u);
		id[{u, v}] = id[{v, u}] = i;
	}
	edcc.work();

	int q; cin >> q;
	vector<int> querys(q + 1);
	for (int i = 1; i <= q; ++i) {
		cin >> querys[i];
	}

	auto [_n, _adj] = edcc.getTree();
	auto& bridge = edcc.bridge;
	auto& bel = edcc.bel;
	
	int tot = 0;
	vector<int> dep(_n + 1), dfn(_n + 1), siz(_n + 1);
	[&](this auto&& dfs, int u, int fa) -> void {
		dfn[u] = ++tot;
		dep[u] = dep[fa] + 1;
		siz[u] = 1;
		for (auto v : _adj[u]) {
			if (v == fa) continue;
			dfs(v, u);
			siz[u] += siz[v];
		}
	} (bel[1], 0);

	vector<int> ans(n + 1, m + 1), vis(n + 1);
	for (auto [u, v] : bridge) {
		int U = bel[u], V = bel[v];
		if (dep[U] > dep[V]) {
			swap(U, V);
		}
		if (dfn[V] <= dfn[bel[n]] && dfn[bel[n]] <= dfn[V] + siz[V] - 1) {
			ans[u] = min(ans[u], id[{u, v}]);
			ans[v] = min(ans[v], id[{u, v}]);
			vis[u] = vis[v] = 1;
		}
	}

	vector<int> nmsl;
	for (int i = 1; i <= n; ++i) {
		if (vis[i]) {
			nmsl.push_back(i);
		}
	}

	sort(nmsl.begin(), nmsl.end(), [&](int i, int j) {
		return ans[i] < ans[j];
	});
	
	queue<int> que;
	for (auto sb : nmsl) {
		que.push(sb);
	}
	while(!que.empty()) {
		int u = que.front();
		que.pop();
		for (auto v : adj[u]) {
			if (!vis[v]) {
				vis[v] = 1, ans[v] = ans[u];
				que.push(v);
			}
		}
	}

	for (int i = 1; i <= q; ++i) {
		int x = ans[querys[i]];
		if (x > m) x = -1;
		cout << x << " \n"[i == q];
	}
}

int main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	int T = 1;
	cin >> T;

	while (T--) {
		Thephix();
	}

	return 0;
}