#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

void Thephix() {
	int n, m, q;
	cin >> n >> m >> q;

	auto get = [&](i64 x) {
		i64 k = x / n;
		i64 r = x % n;
		if (r < 0) r += n, k--;
		return pair(k, r);
	};
	
	vector<vector<array<i64, 2>>> adj(n + 1);
	for (int i = 1; i <= m; ++i) {
		i64 u, v;
		cin >> u >> v;
		auto [k1, r1] = get(u);
		auto [k2, r2] = get(u + v);
		adj[r1 + 1].push_back({ r2 + 1, k2 - k1 });
	}

	int cur = 0, cnt = 0;
	vector<i64> dp(n + 1), ok(n + 1);
	vector<int> dfn(n + 1), low(n + 1), bel(n + 1), stk;

	auto dfs = [&](auto&& dfs, int u) -> void {
		dfn[u] = low[u] = ++cur;
		stk.push_back(u);

		for (auto [v, w] : adj[u]) {
			if (dfn[v] == 0) {
				dp[v] = dp[u] + w;
				dfs(dfs, v);
				low[u] = min(low[u], low[v]);
			} else if (bel[v] == 0) {
				low[u] = min(low[u], dfn[v]);
				ok[u] |= (dp[u] - dp[v] + w) != 0;
			}
		}

		if (dfn[u] == low[u]) {
			int x = cnt++;
			do {
				bel[x = stk.back()] = cnt;
				stk.pop_back();
			} while (x != u);
		}
	};

	for (int i = 1; i <= n; ++i) {
		if (dfn[i] == 0) dfs(dfs, i);
	}

	vector<int> ans(cnt + 1);
	for (int i = 1; i <= n; ++i) {
		ans[bel[i]] |= ok[i];
	}

	vector<int> in(cnt + 1);
	vector<vector<int>> g(cnt + 1);
	for (int u = 1; u <= n; ++u) {
		for (auto [v, w] : adj[u]) {
			if (bel[u] == bel[v]) {
				continue;
			}
			g[bel[v]].push_back(bel[u]);
			in[bel[u]]++;
		}
	}

	queue<int> que;
	for (int i = 1; i <= cnt; ++i) {
		if (in[i] == 0) que.push(i);
	}

	while (!que.empty()) {
		int u = que.front();
		que.pop();
		for (auto v : g[u]) {
			ans[v] |= ans[u];
			if (--in[v] == 0) {
				que.push(v);
			}
		}
	}

	for (int i = 1; i <= q; ++i) {
		i64 x;
		cin >> x;
		auto [k, r] = get(x);
		cout << (ans[bel[r + 1]] ? "Yes\n" : "No\n");
	}
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int T = 1;
	// cin >> T;

	while (T--) {
		Thephix();
	}

	return 0;
}
