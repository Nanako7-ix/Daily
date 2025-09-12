#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr i64 inf = 4E18;

void Thephix() {
	int n, m;
	cin >> n >> m;
	vector<vector<array<i64, 2>>> adj(n + 1);
	for (int i = 1; i < n; ++i) {
		int u, v; i64 w;
		cin >> u >> v >> w;
		adj[u].push_back({v, w});
		adj[v].push_back({u, w});
	}

	vector<array<int, 2>> edges(m + 1);
	for (int i = 1; i <= m; ++i) {
		auto& [u, v] = edges[i];
		cin >> u >> v;
	}

	vector<i64> dp(n + 1, inf);
	dp[1] = 0;
	for (int i = 0; i <= n; ++i) {
		[&](this auto&& dfs, int u, int fa) -> void {
			for (auto& [v, w] : adj[u]) {
				if (v == fa) continue;
				dfs(v, u);
				dp[u] = min(dp[u], dp[v] + w);
			}
		} (1, 0);

		[&](this auto&& dfs, int u, int fa) -> void {
			for (auto& [v, w] : adj[u]) {
				if (v == fa) continue;
				dp[v] = min(dp[v], dp[u] + w);
				dfs(v, u);
			}
		} (1, 0);

		cout << accumulate(dp.begin() + 1, dp.end(), 0LL) << "\n";

		vector<i64> ndp = dp;
		for (int j = 1; j <= m; ++j) {
			auto [u, v] = edges[j];
			ndp[u] = min(ndp[u], dp[v]);
			ndp[v] = min(ndp[v], dp[u]);
		}
		swap(dp, ndp);
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
