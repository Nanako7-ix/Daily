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
	int n, k;
	cin >> n >> k;
	vector<vector<int>> adj(n + 1);
	vector<int> deg(n + 1);
	for (int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
		deg[u]++, deg[v]++;
	}
	
	queue<int> que;
	vector<int> dp(n + 1);
	for (int i = 1; i <= n; ++i) {
		if (deg[i] == 1) {
			que.push(i);
			dp[i] = 1;
		}
	}

	k = n - k;
	while (!que.empty()) {
		int u = que.front();
		que.pop(), k--;
		if (k == 0) {
			cout << dp[u] << "\n";
			return;
		}
		for (auto& v : adj[u]) {
			deg[u]--, deg[v]--;
			dp[v] = max(dp[v], dp[u] + 1);
			if (deg[v] == 1) que.push(v);
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
