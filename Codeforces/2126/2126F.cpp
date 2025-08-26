#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

void Thephix() {
	int n, q;
	cin >> n >> q;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	vector<vector<array<int, 2>>> adj(n + 1);
	for (int i = 1; i < n; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].push_back({v, w});
		adj[v].push_back({u, w});
	}

	i64 ans = 0;
	vector<int> fa(n + 1), b(n + 1);
	vector<map<int, i64>> col(n + 1);
	[&](this auto&& dfs, int u) -> void {
		if (u != 1) {
			array<int, 2> del;
			for (auto v : adj[u]) {
				if (v[0] == fa[u]) {
					del = v;
					break;
				}
			}
			adj[u].erase(ranges::find(adj[u], del));
		}
		for (auto [v, w] : adj[u]) {
			fa[v] = u, b[v] = w;
			col[u][a[v]] += w;
			if (a[u] != a[v]) {
				ans += w;
			}
			dfs(v);
		}
	} (1);

	while (q--) {
		int v, x;
		cin >> v >> x;
		if (x != a[v]) {
			if (col[v].contains(a[v])) {
				ans += col[v][a[v]];
			}
			if (col[v].contains(x)) {
				ans -= col[v][x];
			}
			if (fa[v] != 0) {
				int u = fa[v];
				if (a[u] == a[v]) {
					ans += b[v];
				}
				if (a[u] == x) {
					ans -= b[v];
				}
				col[u][a[v]] -= b[v];
				if (col[u][a[v]] == 0) {
					col[u].erase(a[v]);
				}
				col[u][x] += b[v];
			}
			a[v] = x;
		}
		cout << ans << "\n";
	}
}

signed main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	int T = 1;
	cin >> T;

	while (T--) {
		Thephix();
	}

	return 0;
}