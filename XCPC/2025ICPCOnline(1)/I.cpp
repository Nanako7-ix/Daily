#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr i64 inf = 1E18;

void Thephix() {
	int n, m, lim, s;
	cin >> n >> m >> lim >> s;
	vector<vector<array<i64, 2>>> adj(n + 1);
	for (int i = 1; i <= m; ++i) {
		int u, v; i64 w;
		cin >> u >> v >> w;
		adj[u].push_back({v, w});
		adj[v].push_back({u, w});
	}

	vector<array<i64, 2>>  dp(n + 1, {inf, inf});
	vector<int> vis(n + 1, 0);
	priority_queue<pair<array<i64, 2>, int>, vector<pair<array<i64, 2>, int>>, greater<pair<array<i64, 2>, int>>> q;
	q.push({ dp[s] = {1, 0}, s });
	while (!q.empty()) {
		auto [_, u] = q.top();
		q.pop();
		if (vis[u]) continue;
		vis[u] = 1;
		for (auto& [v, w] : adj[u]) {
			auto [bags, rest] = dp[u];
			if (rest + w > lim) {
				rest = 0, bags++;
			} rest += w;
			if (dp[v] > array { bags, rest }) {
				q.push({dp[v] = { bags, rest }, v});
			}
		}
	}
	for (int u = 1; u <= n; ++u) {
		if (dp[u][0] == inf) {
			cout << -1 << " \n"[u == n];
		} else {
			cout << dp[u][0] << " \n"[u == n];
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
