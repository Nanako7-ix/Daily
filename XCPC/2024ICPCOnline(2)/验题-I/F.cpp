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
	vector<string> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}

	using node = pair<array<int, 26>, int>;
	vector<node> tr(2);
	for (int i = 1; i <= n; ++i) {
		int u = 1;
		for (int j = 0; j < (int) a[i].size(); ++j) {
			int ch = a[i][j] - 'a';
			if (tr[u].first[ch] == 0) {
				tr[u].first[ch] = tr.size();
				tr.push_back({});
			}
			u = tr[u].first[ch];
		}
		tr[u].second++;
	}

	vector<vector<i64>> dp(tr.size());
	[&](this auto&& dfs, int u, i64 dep) -> void {
		dp[u].assign(tr[u].second + 1, 0);
		for (int i = 2; i <= tr[u].second; ++i) {
			dp[u][i] = dep * i * (i - 1) / 2;
		}
		for (int i = 0; i < 26; ++i) {
			int v = tr[u].first[i];
			if (v == 0) continue;
			dfs(v, dep + 1);
			int siz_u = dp[u].size() - 1;
			int siz_v = dp[v].size() - 1;
			vector<i64> ndp(siz_u + siz_v + 1);
			for (int x = 0; x <= siz_u; ++x) {
				for (int y = 0; y <= siz_v; ++y) {
					ndp[x + y] = max(ndp[x + y], dp[u][x] + dp[v][y] + dep * x * y);
				}
			}
			swap(ndp, dp[u]);
		}
	} (1, 0);

	cout << dp[1][k] << "\n";
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
