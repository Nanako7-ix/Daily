#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

void Thephix() {
	int n, m, k;
	cin >> n >> m >> k;

	string s;
	cin >> s;

	vector<vector<int>> adj(n + 1);
	for (int i = 1; i <= m; ++i) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
	}

	// dp[u][x] 表示当前先手为 0: Alice 1: Bob 的时候，处在 u 点能否获胜。
	vector<int> dp(n + 1);
	for (int i = 1; i <= n; ++i) {
		dp[i] = s[i - 1] == 'A';
	}

	for (int i = 1; i <= k; ++i) {
		vector<int> ndp(n + 1);
		for (int u = 1; u <= n; ++u) {
			for (int v : adj[u]) {
				ndp[u] |= dp[v] == 0;
				ndp[u] |= dp[v] == 0;
			}
		}
		dp.assign(n + 1, 0);
		for (int u = 1; u <= n; ++u) {
			for (int v : adj[u]) {
				dp[u] |= ndp[v] == 0;
				dp[u] |= ndp[v] == 0;
			}
		}
	}

	cout << (dp[1] ? "Alice\n" : "Bob\n");
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
