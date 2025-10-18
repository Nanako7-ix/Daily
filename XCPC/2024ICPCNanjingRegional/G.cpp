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
	for (int u = 1; u <= n; ++u) {
		int ls, rs;
		cin >> ls >> rs;
		if (ls != 0) {
			adj[u].push_back(ls);
			adj[ls].push_back(u);
		}
		if (rs != 0) {
			adj[u].push_back(rs);
			adj[rs].push_back(u);
		}
	}

	int rt = 1;
	vector<int> siz(n + 1);
	while (true) {
		assert(rt != 0);
		[&](this auto&& dfs, int u, int fa) -> void {
			siz[u] = 1;
			for (auto& v : adj[u]) {
				if (v == fa) continue;
				dfs(v, u);
				siz[u] += siz[v];
			}
		} (rt, 0);
		
		int Min = siz[rt], x = 0;
		[&](this auto&& dfs, int u, int fa) -> void {
			int Max = 1;
			for (auto& v : adj[u]) {
				if (v == fa) continue;
				dfs(v, u);
				Max = max(Max, siz[v]);
			}
			Max = max(Max, siz[rt] - siz[u]);
			if (Max <= Min) {
				Min = Max;
				x = u;
			}
		} (rt, 0);

		if (adj[x].size() == 0) {
			cout << "! " << x << endl;
			return;
		} else if (adj[x].size() == 1) {
			cout << "? " << x << ' ' << adj[x][0] << endl;
			int t; cin >> t;
			assert(t != 1);
			if (t == 0) cout << "! " << x << endl;
			if (t == 2) cout << "! " << adj[x][0] << endl;
			return;
		} else if (adj[x].size() == 2) {
			int u = adj[x][0], v = adj[x][1];
			cout << "? " << u << ' ' << v << endl;
			int t; cin >> t;
			if (t == 1) {
				cout << "! " << x << endl;
				return;
			}
			if (t == 0) {
				adj[u].erase(find(adj[u].begin(), adj[u].end(), x));
				rt = u;
			}
			if (t == 2) {
				adj[v].erase(find(adj[v].begin(), adj[v].end(), x));
				rt = v;
			}
		} else if (adj[x].size() == 3) {
			[&](this auto&& dfs, int u, int fa) -> void {
				siz[u] = 1;
				for (auto v : adj[u]) {
					if (v == fa) continue;
					dfs(v, u);
					siz[u] += siz[v];
				}
			} (x, 0);

			sort(adj[x].begin(), adj[x].end(), [&](int u, int v) {
				return siz[u] > siz[v];
			});

			int u = adj[x][0], v = adj[x][1];
			cout << "? " << u << ' ' << v << endl;
			int t; cin >> t;
			if (t == 1) {
				adj[x] = { adj[x][2] };
				rt = x;
			}
			if (t == 0) {
				adj[u].erase(find(adj[u].begin(), adj[u].end(), x));
				rt = u;
			}
			if (t == 2) {
				adj[v].erase(find(adj[v].begin(), adj[v].end(), x));
				rt = v;
			}
		} else {
			__builtin_unreachable();
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
