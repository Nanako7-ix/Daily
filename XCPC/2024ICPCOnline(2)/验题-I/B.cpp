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
	int n, x;
	cin >> n >> x;
	vector<vector<int>> adj(n + 1);
	for (int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	vector<int> dep(n + 1), Max(n + 1);
	[&](this auto&& dfs, int u, int fa) -> void {
		Max[u] = dep[u];
		for (auto& v : adj[u]) {
			if (v == fa) continue;
			dep[v] = dep[u] + 1;
			dfs(v, u);
			Max[u] = max(Max[u], Max[v]);
		}
	} (1, 0);

	cout << Max[x] * 2 << "\n";
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
