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
	vector<vector<int>> adj(n + 1);
	for (int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	vector<array<int, 2>> ans;
	auto dfs = [&](auto&& dfs, int u, int fa) -> int {
		vector<int> x;
		vector<int> y;
		for (auto& v : adj[u]) {
			if (v == fa) continue;
			int w = dfs(dfs, v, u);
			(w == v ? x : y).push_back(w);
		}

		if (u != 1 && (x.size() + y.size()) % 2 == 0) {
			if (!y.empty()) {
				ans.push_back({ y.back(), u });
				y.pop_back();
			}
		}

		vector<int> all;
		for (auto x : x) all.push_back(x);
		for (auto y : y) all.push_back(y);

		int len = all.size();
		for (int i = 1; i < len; i += 2) {
			ans.push_back({ all[i], all[i - 1] });
		}
		if (all.size() % 2 == 1) {
			return all.back();
		} return u;
	};
	
	int w = dfs(dfs, 1, 0);
	
	for (auto& v : adj[1]) {
		if (v == w) {
			cout << "-1\n";
			return;
		}
	}

	if (w != 1) {
		ans.push_back({ 1, w });
	}
	
	cout << ans.size() << "\n";
	for (auto& [x, y] : ans) {
		cout << x << ' ' << y << "\n";
	}
}

int main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	int T = 1;
	cin >> T;

	int cnt = 1;
	while (T--) {
		Thephix();
		cnt++;
	}

	return 0;
}
