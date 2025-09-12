#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr i64 inf = 1E12;

void Thephix() {
	int n, m, d;
	cin >> n >> m >> d;
	vector<vector<int>> adj(n + 1);
	for (int i = 1; i <= m; ++i) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	auto dis = [&]() -> vector<array<i64, 2>> {
		vector<array<i64, 2>>  dp(n + 1, { inf, inf });
		vector<array<int, 2>> vis(n + 1, {  0 ,  0  });

		queue<array<int, 2>> q;
		int k; cin >> k;
		for (int i = 1; i <= k; ++i) {
			int u; cin >> u;
			q.push({u, 0});
			dp[u][0] = 0, vis[u][0] = 1;
		}

		while (!q.empty()) {
			auto [u, x] = q.front();
			q.pop();
			for (auto v : adj[u]) {
				if (vis[v][x ^ 1]) continue;
				 dp[v][x ^ 1] = dp[u][x] + 1;
				vis[v][x ^ 1] = 1;
				q.push({v, x ^ 1});
			}
		}
		return dp;
	} ();

	vector<array<i64, 2>>  dp(n + 1, { inf, inf });
	vector<array<int, 2>> nxt(n + 1, {  0 ,  0  });
	queue<array<int, 2>> q;
	q.push({1, 0});
	dp[1][0] = 0, nxt[1][0] = 1;

	while (!q.empty()) {
		auto [u, x] = q.front();
		q.pop();
		for (auto v : adj[u]) {
			if (nxt[v][x ^ 1] || dis[v][x ^ 1] <= dp[u][x] + 1) continue;
			dp[v][x ^ 1] = dp[u][x] + 1;
			nxt[v][x ^ 1] = u;
			q.push({v, x ^ 1});
		}
	}

	int x = dp[n][0] >= dp[n][1];
	if (dp[n][x] == inf) {
		cout << "-1\n";
		return;
	}

	cout << dp[n][x] << "\n";

	vector<int> path;
	for (int u = n; nxt[u][x] != u; u = nxt[u][x], x ^= 1) {
		path.push_back(u);
	}
	path.push_back(1);
	
	for (; !path.empty(); path.pop_back()) {
		cout << path.back() << " \n"[path.size() == 1];
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
