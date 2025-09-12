#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

template<typename T>
tuple<int, int, T> Diameter(vector<vector<pair<int, T>>> adj) {
	int n = adj.size() - 1;
	vector<T> dep(n + 1);
	auto dfs = [&](this auto&& dfs, int u, int fa) -> void {
		for (auto [v, w] : adj[u]) {
			if (v == fa) continue;
			dep[v] = dep[u] + w;
			dfs(v, u);
		}
	};

	dep[1] = 0, dfs(1, 0);
	int u = max_element(dep.begin() + 1, dep.end()) - dep.begin();
	dep[u] = 0, dfs(u, 0);
	int v = max_element(dep.begin() + 1, dep.end()) - dep.begin();
	return { u, v, dep[v] };
}

void Thephix() {
	int n;
	cin >> n;
	vector<int> deg(n + 1);
	vector<vector<pair<int, int>>> adj(n + 1);
	for (int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		deg[u]++, deg[v]++;
		adj[u].push_back({v, 1});
		adj[v].push_back({u, 1});
	}

	auto [u, v, len] = Diameter(adj);
	if (len == n - 1) {
		cout << "-1\n";
		return;
	}

	int idx = 0;
	vector<int> dfn(n + 1), siz(n + 1);
	[&](this auto&& dfs, int u, int fa) -> void {
		dfn[u] = ++idx;
		siz[u] = 1;
		for (auto [v, w] : adj[u]) {
			if (v == fa) continue;
			dfs(v, u);
			siz[u] += siz[v];
		}
	} (u, 0);
	vector<int> path;
	for (int i = 1; i <= n; ++i) {
		if (dfn[i] <= dfn[v] && dfn[v] <= dfn[i] + siz[i] - 1) {
			path.push_back(i);
		}
	}
	sort(path.begin(), path.end(), [&](int i, int j) {
		return dfn[i] < dfn[j];
	});

	for (int i = 1; i + 1 < (int) path.size(); ++i) {
		if (deg[path[i]] >= 3) {
			int x = path[i - 1], y = path[i], z = path[i + 1];
			for (auto [v, w] : adj[y]) {
				if (v == x || v == z) continue;
				cout << x << ' ' << y << ' ' << v << "\n";
				return;
			}
		}
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