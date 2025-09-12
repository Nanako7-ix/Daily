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
	int n;
	cin >> n;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	vector<vector<int>> adj(n + 1);
	for (int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	vector<array<i64, 3>> dp(n + 1);
	[&](this auto&& dfs, int u, int fa) -> void {
		i64 sum = 0, U = -inf, D = -inf;
		for (auto v : adj[u]) {
			if (v == fa) continue;
			dfs(v, u);
			i64 w_U = a[v] >= a[u] ? a[v] - a[u] : -inf;
			i64 w_D = a[u] >= a[v] ? a[u] - a[v] : -inf;
			sum += dp[v][0];
			U = max(U, dp[v][1] - dp[v][0] + w_U);
			D = max(D, dp[v][2] - dp[v][0] + w_D);
		}
		dp[u] = {
			sum + max(0LL, U) + max(0LL, D),
			sum + max(0LL, U),
			sum + max(0LL, D)
		};
	} (1, 0);

	cout << *max_element(dp[1].begin(), dp[1].end()) << "\n";
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
