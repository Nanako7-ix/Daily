#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

void Thephix() {
	int n, m;
	cin >> n >> m;

	vector adj(n + 1, vector<int> (n + 1));
	for (int i = 1; i <= m; ++i) {
		int u, v;
		cin >> u >> v;
		adj[u][v] = adj[v][u] = 1;
	}

	int ans = m;
	for (int s = 0; s < (1 << n); ++s) {
		int res = 0;
		for (int u = 1; u <= n; ++u) {
			for (int v = u + 1; v <= n; ++v) {
				if ((s >> u & 1) == (s >> v & 1)) {
					res += adj[u][v];
				}
			}
		}
		ans = min(ans, res);
	}
	cout << ans << "\n";
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
