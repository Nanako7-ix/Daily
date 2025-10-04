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
	int n;
	cin >> n;
	vector<vector<int>> adj(n + 1);
	for (int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	vector<int> d(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> d[i];
	}
	
	vector<int> dep(n + 1), ans(n + 1);
	vector<int> f(n + 1);
	auto dfs = [&](auto&& dfs, int u, int fa) -> void {
		dep[u] = dep[fa] + 1;
		f[dep[u]] = u;
		ans[u]++, ans[f[max(dep[u] - d[u] - 1, 0)]]--;
		for (auto v : adj[u]) {
			if (v == fa) continue;
			dfs(dfs, v, u);
			ans[u] += ans[v];
		}
	}; dfs(dfs, 1, 0);

	for (int i = 1; i <= n; ++i) {
		cout << ans[i] << " \n"[i == n];
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
