#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

constexpr int n = 16;
constexpr int N = 1 << 16;
constexpr i64 inf = 4E18;

array<i64, N> f;

void init() {
	array<int, 4> a;
	cin >> a[0] >> a[1] >> a[2] >> a[3];
	
	vector<vector<array<int, 2>>> adj(n);
	for (int u = 0; u < n; ++u) {
		// 点修改
		adj[u].push_back({ u ^  1, a[0] });
		adj[u].push_back({ u ^  2, a[0] });
		adj[u].push_back({ u ^  4, a[0] });
		adj[u].push_back({ u ^  8, a[0] });
		// 行修改
		adj[u].push_back({ u ^  3, a[1] });
		adj[u].push_back({ u ^ 12, a[1] });
		// 列修改
		adj[u].push_back({ u ^  5, a[2] });
		adj[u].push_back({ u ^ 10, a[2] });
		// 全修改
		adj[u].push_back({ u ^ 15, a[3] });
	}
	
	vector dp(n, vector<i64> (N, inf));
	for (auto [v, w] : adj[0]) {
		dp[v][1 << v] = w;
	}
	for (int s = 0; s < N; ++s) {
		// 很他妈烦，这个地方会遇到 s 相同的转移/松弛，不会处理只能做一遍 dijkstra 了
		vector<int> vis(n + 1);
		priority_queue<array<i64, 2>, vector<array<i64, 2>>, greater<array<i64, 2>>> q;
		for (int u = 0; u < n; ++u) {
			if (dp[u][s] != inf) {
				q.push({ dp[u][s], u });
			}
		}
		while (!q.empty()) {
			auto [_, u] = q.top();
			q.pop();
			if (vis[u]) continue;
			vis[u] = 1;
			for (auto [v, w] : adj[u]) {
				if ((s >> v & 1) == 0) continue;
				if (dp[u][s] + w < dp[v][s]) {
					dp[v][s] = dp[u][s] + w;
					q.push({ dp[v][s], v });
				}
			}
		}

		for (int u = 0; u < n; ++u) {
			if (dp[u][s] >= inf) continue;
			for (auto [v, w] : adj[u]) {
				int t = s | (1 << v);
				dp[v][t] = min(dp[v][t], dp[u][s] + w);
			}
			f[s] = min(f[s], dp[u][s]);
		}
	}

	for (int s = 0; s < N; ++s) {
		f[s] = inf;
		for (int u = 0; u < n; ++u) {
			f[s] = min(f[s], dp[u][s]);
		}
	}

	// sosdp 对 f[s] 求超集 min
	for (int i = 0; i < n; ++i) {
		for (int s = 0; s < N; ++s) {
			if ((s >> i & 1) == 0) {
				f[s] = min(f[s], f[s | (1 << i)]);
			}
		}
	}
}

void Thephix() {
	int n;
	cin >> n;
	
	int s = 0;
	for (int i = 1; i <= n; ++i) {
		int x, y;
		cin >> x >> y;
		int get = 0;
		get |= !(x / 10) << 0;
		get |= !(x % 10) << 1;
		get |= !(y / 10) << 2;
		get |= !(y % 10) << 3;
		s |= 1 << get;
	}

	cout << f[s] << '\n';
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int T = 1;
	cin >> T;

	init();

	while (T--) {
		Thephix();
	}

	return 0;
}
