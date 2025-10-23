#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

void Thephix() {
	int n;
	cin >> n;
	vector<int> deg(n + 1);
	vector<vector<int>> adj(n + 1);
	for (int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
		deg[u]++, deg[v]++;
	}

	vector<int> dep(n + 1);
	[&](this auto&& dfs, int u, int fa) -> void {
		dep[u] = dep[fa] ^ 1;
		for (auto& v : adj[u]) {
			if (v == fa) continue;
			dfs(v, u);
		}
	} (1, 0);

	queue<int> que;
	for (int i = 1; i <= n; ++i) {
		if (deg[i] == 1) que.push(i);
	}

	int now = 1;
	vector<array<int, 2>> ans;
	while (!que.empty()) {
		int u = que.front();
		que.pop();
		if (u == n) continue;
		if (now == dep[u]) {
			ans.push_back({ 1, 0 });
			now ^= 1;
		} else {
			ans.push_back({ 1, 0 });
			ans.push_back({ 1, 0 });
		}
		ans.push_back({ 2, u });
		for (auto& v : adj[u]) {
			deg[v]--;
			if (deg[v] == 1) {
				que.push(v);
			}
		}
	}

	cout << ans.size() << "\n";
	for (auto& [x, y] : ans) {
		if (x == 1) {
			cout << x << "\n";
		} else {
			cout << x << ' ' << y << "\n";
		}
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
