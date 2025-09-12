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
	int n, m, q;
	cin >> n >> m >> q;
	vector<vector<array<int, 2>>> adj(n + 1);
	for (int i = 1; i <= m; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].push_back({v,  w});
		adj[v].push_back({u, -w});
	}
	
	vector<int> bel(n + 1), f(n + 1);
	vector<i64> dp(n + 1);
	for (int i = 1; i <= n; ++i) {
		if (bel[i]) continue;
		auto dfs = [&](auto&& dfs, int u) -> void {
			bel[u] = i;
			for (auto [v, w] : adj[u])  {
				if (bel[v] == 0) {
					dp[v] = dp[u] + w;
					dfs(dfs, v);
				} else {
					f[i] |= (dp[u] - dp[v] + w) != 0;
				}
			}
		}; dfs(dfs, i);
	}

	for (int i = 1; i <= q; ++i) {
		int u, v;
		cin >> u >> v;
		if (bel[u] != bel[v]) {
			cout << "nan\n";
		} else if (f[bel[u]]) {
			cout << "inf\n";
		} else {
			cout << dp[v] - dp[u] << "\n";
		}
	}
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
